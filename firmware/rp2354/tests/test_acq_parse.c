// Host test for the acq header parser / rate formatter (plain C, no pico-sdk).
#include <assert.h>
#include <stdio.h>
#include <string.h>
#include "acq_parse.h"

static void test_parses_ok_header(void) {
    acq_hdr_t h;
    assert(acq_parse_header("ACQ 4095 1024 100 ok", &h) == 1);
    assert(h.n == 4095);
    assert(h.ticks == 1024);
    assert(h.tick_ns == 100);
    assert(strcmp(h.status, "ok") == 0);
}
static void test_parses_timeout_header(void) {
    acq_hdr_t h;
    assert(acq_parse_header("ACQ 4095 0 100 timeout", &h) == 1);
    assert(strcmp(h.status, "timeout") == 0);
}
static void test_rejects_err_line(void) {
    acq_hdr_t h;
    assert(acq_parse_header("ERR acq notready", &h) == 0);
}
static void test_rejects_pong(void) {
    acq_hdr_t h;
    assert(acq_parse_header("PONG 3", &h) == 0);
}
static void test_rejects_truncated_header(void) {
    acq_hdr_t h;
    assert(acq_parse_header("ACQ 4095 1024", &h) == 0);
}
static void test_formats_rate(void) {
    acq_hdr_t h = { 4095, 1024, 100, "ok" };
    char buf[64];
    int n = acq_format_rate(&h, buf, sizeof buf);
    assert(n > 0);
    assert(strstr(buf, "fill=102.4us") != NULL);     // 1024 x 100 ns
    assert(strstr(buf, "fs=39.99Msps") != NULL);     // 4095 / 102.4 us
}
static void test_formats_rate_zero_ticks(void) {
    acq_hdr_t h = { 4095, 0, 100, "ok" };
    char buf[64];
    assert(acq_format_rate(&h, buf, sizeof buf) > 0);
    assert(strstr(buf, "fill=0.0us") != NULL);
    assert(strstr(buf, "fs=?") != NULL);             // no division by zero
}
int main(void) {
    test_parses_ok_header();
    test_parses_timeout_header();
    test_rejects_err_line();
    test_rejects_pong();
    test_rejects_truncated_header();
    test_formats_rate();
    test_formats_rate_zero_ticks();
    puts("PASS test_acq_parse (7 tests)");
    return 0;
}
