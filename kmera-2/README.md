The steps described here, consider that you have an ESP32CAM. For an easy installation, I recommend you using an ESP32CAM board with an usb to serial conversor like [this](https://produto.mercadolivre.com.br/MLB-2044954813-modulo-esp32-cam-com-cmera-ov2640-e-conversor-usb-serial-_JM#position=6&search_layout=grid&type=item&tracking_id=a89affb6-a55b-40af-9fda-994511a9edcf) or [this](https://www.amazon.com/Aideepen-ESP32-CAM-Bluetooth-ESP32-CAM-MB-Arduino/dp/B08P2578LV/ref=sr_1_12?keywords=esp32+cam+converter+usb&qid=1636929420&sr=8-12) one. **It's way easier than using an arduino uno as a programmer!**

## Before you start

Change the following code and put your WIFI SSID and you password.
```
const char* WIFI_SSID = "WIFI_SSID";
const char* WIFI_PASS = "PASSWORD";
```


## How to install it?

Open the Arduino IDE and the source code and configure as following:

![image](https://user-images.githubusercontent.com/5191469/141701478-9691c20c-7552-415a-841f-ccdf2ce3ac58.png)

The port may vary.

Click on Sketch menu and Upload, it may take a few minutes to finish it!

You should be good!
