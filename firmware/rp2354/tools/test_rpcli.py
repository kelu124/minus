#!/usr/bin/env python3
"""Host test for rpcli.py: --out=FILE saves the last reply. Uses a pty pair as a fake USB console."""
import os, pty, subprocess, sys, tempfile, threading, time, unittest

HERE = os.path.dirname(os.path.abspath(__file__))
RPCLI = os.path.join(HERE, "rpcli.py")
REPLY = "# acq n=3 fill=0.1us fs=30.00Msps\n1\n2\n3\n"

def run_rpcli(extra_args, reply=REPLY):
    master, slave = pty.openpty()
    slave_path = os.ttyname(slave)
    def responder():
        # wait for the "acq\n" command, then answer
        buf = b""
        end = time.time() + 5
        while b"\n" not in buf and time.time() < end:
            try: buf += os.read(master, 64)
            except OSError: break
        os.write(master, reply.encode())
    t = threading.Thread(target=responder, daemon=True); t.start()
    p = subprocess.run([sys.executable, "-I", RPCLI, slave_path, "acq", "--wait=0.5"] + extra_args,
                       capture_output=True, text=True, timeout=20)
    t.join(timeout=5)
    os.close(master); os.close(slave)
    return p

class TestRpcliOut(unittest.TestCase):
    def test_out_file_gets_last_reply(self):
        with tempfile.TemporaryDirectory() as d:
            out = os.path.join(d, "capture.csv")
            p = run_rpcli([f"--out={out}"])
            self.assertEqual(p.returncode, 0, p.stderr)
            self.assertIn("> acq", p.stdout)
            with open(out) as f: self.assertEqual(f.read(), REPLY)

    def test_unwritable_out_path_keeps_console_reply(self):
        p = run_rpcli(["--out=/nonexistent-dir-xyz/capture.csv"])
        self.assertEqual(p.returncode, 1)
        self.assertIn("1\n2\n3", p.stdout)
        self.assertIn("capture.csv", p.stderr)

if __name__ == "__main__":
    unittest.main()
