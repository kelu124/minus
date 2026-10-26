#!/usr/bin/env python3
"""Send CLI lines to the RP2354 USB console and print replies.  usage: rpcli.py PORT 'cmd1' 'cmd2' ... [--wait S]"""
import sys, time, os, termios, tty
port = sys.argv[1]; cmds = [a for a in sys.argv[2:] if not a.startswith('--')]
wait = 1.0
for a in sys.argv[2:]:
    if a.startswith('--wait='): wait = float(a.split('=')[1])
fd = os.open(port, os.O_RDWR | os.O_NOCTTY | os.O_NONBLOCK)
attrs = termios.tcgetattr(fd); tty.setraw(fd); termios.tcsetattr(fd, termios.TCSANOW, attrs[:4] + [attrs[4], attrs[5], attrs[6]])
tty.setraw(fd)
def drain(t):
    out = b''; end = time.time() + t
    while time.time() < end:
        try: chunk = os.read(fd, 4096)
        except BlockingIOError: chunk = b''
        if chunk: out += chunk; end = max(end, time.time() + 0.3)
        else: time.sleep(0.02)
    return out.decode(errors='replace')
drain(0.3)
for c in cmds:
    os.write(fd, (c + '\n').encode()); print(f"> {c}"); print(drain(wait).rstrip())
os.close(fd)
