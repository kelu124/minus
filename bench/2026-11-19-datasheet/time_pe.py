#!/usr/bin/env python3
"""Time `pe` end to end on the USB console (command sent -> '# pulse' line received). usage: time_pe.py PORT N [cmd]"""
import os, sys, time, termios, tty
port, n = sys.argv[1], int(sys.argv[2]); cmd = sys.argv[3] if len(sys.argv) > 3 else "pe"
fd = os.open(port, os.O_RDWR | os.O_NOCTTY | os.O_NONBLOCK); tty.setraw(fd)
def drain(t):
    end = time.time() + t
    while time.time() < end:
        try: os.read(fd, 65536)
        except BlockingIOError: time.sleep(0.01)
drain(0.3)
for i in range(n):
    buf = b""; t0 = time.time(); os.write(fd, (cmd + "\n").encode())
    while b"# pulse" not in buf or not buf.endswith(b"\n"):
        try: buf += os.read(fd, 65536)
        except BlockingIOError: time.sleep(0.001)
        if time.time() - t0 > 20: break
    dt = time.time() - t0
    shots = buf.split(b"# pulse")[1].split(b"\n")[0].decode().strip()
    print(f"{dt:.3f} {shots}")
os.close(fd)
