# Host-side unit tests for pure-C helpers of the RP2354 firmware (no pico-sdk needed).
CC ?= cc
CFLAGS ?= -std=c11 -Wall -Wextra -Werror -I..
all: test_acq_parse test_link_frame
	./test_acq_parse
	./test_link_frame
test_acq_parse: test_acq_parse.c ../acq_parse.c ../acq_parse.h
	$(CC) $(CFLAGS) -o $@ test_acq_parse.c ../acq_parse.c
test_link_frame: test_link_frame.c ../link_frame.c ../link_frame.h
	$(CC) $(CFLAGS) -o $@ test_link_frame.c ../link_frame.c
clean:
	rm -f test_acq_parse test_link_frame
.PHONY: all clean
