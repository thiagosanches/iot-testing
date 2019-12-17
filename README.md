# iot-testing
My little adventure in the IoT world, the idea is to maintain a unique central that controls everything through my Raspberry Pi A+. I'm using the serial communication to fetch the data that I need.

All the data is managed by Prometheus and its exporters and displayed by Grafana. Right now, there is a Arduino Uno plugged into the Raspberry Pi with a DTH11 sensor.

## Hardware
* 1 Raspberry Pi A+
* 1 Arduino Uno
* 1 DTH11 Humidity and Temperature Sensor

## Source code
[read-temperature-humidity-serial-protocol.ino](read-temperature-humidity-serial-protocol.ino)

[read.py](read.py)
