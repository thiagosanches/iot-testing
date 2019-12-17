#!/usr/bin/python

import serial
import time
from prometheus_client import start_http_server, Summary, Gauge

IOT_REQUEST_TIME = Summary('iot_request_processing_seconds', 'Time spent processing request')
IOT_TEMPERATURE = Gauge('iot_temperature', 'Temperature in celsius')
IOT_HUMIDITY = Gauge('iot_humidity', 'Humidity in percentage')

# Decorate function with metric.
@IOT_REQUEST_TIME.time()
def process_request():
    ser = serial.Serial('/dev/ttyACM0', 9600)
    time.sleep(2)
    
    ser.write('T')
    IOT_TEMPERATURE.set(float(ser.readline().strip()))

    ser.write('H')
    IOT_HUMIDITY.set(float(ser.readline().strip()))

    ser.close()

if __name__ == '__main__':
    start_http_server(8000)
    while True:
        process_request()
