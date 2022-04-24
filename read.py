#!/usr/bin/python

import serial
import time
from prometheus_client import start_http_server, Summary, Gauge

IOT_REQUEST_TIME = Summary('iot_request_processing_seconds', 'Time spent processing request')
IOT_TEMPERATURE = Gauge('iot_temperature', 'Temperature in celsius')

@IOT_REQUEST_TIME.time()
def process_request():
    ser = serial.Serial('/dev/ttyACM0', 115200)
    ser.flushInput()
    ser.write(bytes('T', "UTF-8"))
    time.sleep(2)
    data = float(ser.read(5).strip()) # reading 5 bytes like: XX.XX = 5 bytes
    IOT_TEMPERATURE.set(data)
    ser.flushOutput()
    ser.close()

if __name__ == '__main__':
    start_http_server(8000)
    while True:
        process_request()
