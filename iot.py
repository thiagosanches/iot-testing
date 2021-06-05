#!/usr/bin/env python
import serial
import time
if __name__ == '__main__':
    ser = serial.Serial('/dev/ttyACM0', 9600, timeout=1)
    ser.flush()
    ser.write(b"T!\n")
    ser.write(b"B!\n")
    ser.write(b"#OI\n")
