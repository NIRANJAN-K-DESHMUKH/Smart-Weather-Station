# Smart-Weather-Station
### An IoT based Smart Weather Station that is capable of detecting the Temperature, Atmospheric Pressure, Humidity, Light Intensity using various Sensors and NodeMCU board.
#### The project is created using NodeMCU with WiFi Module ESP8266 -12E, Temperature and humidity sensor DHT11, Atmospheric pressure sensor BMP180, Digital Light Sensor BH1750FVI, Mini Breadboards, OLED Display, Jumper wires, USB Cable. It is able to correctly detect the values of weather conditions present in the surroundings, like – Temperature (deg. Celcius), Atmospheric Pressure (pascals), Light Intensity (Lux (lx)) and Humidity (%). The detected parameter values were updated to a channel server created on thingspeak (a matlab tool) to visualize the graphs of the collected data. A local Web Page was created for the simulation view of the results, which fetched the data back from thingspeak server API.
### Using this project one can monitor the weather conditions of a remotely located place from anywhere through the internet.

## 
### Hardware:
- NodeMCU with WiFi Module ESP8266 -12E
- Temperature and humidity sensor DHT11
- Atmospheric pressure sensor BMP180
- Digital Light Sensor BH1750FVI
- Mini Breadboards
- OLED Display
- Jumper wires
- USB Cable

### Software:
- Arduino IDE
- Web Browser for Simulation (Chrome or any other)
- MATLAB's ThingSpeak for IoT

### Description:
1) ESP8266: is a wifi SOC (system on a chip) produced by Espressif Systems. It is an highly integrated chip designed to provide full internet connectivity in a small package.
2) DHT11: is a commonly used Temperature and Humidity sensor that comes with a dedicated NTC to measure temperature and an 8-bit microcontroller to output the values of temperature and humidity as serial data.
3) BMP180: is one of sensor of BMP XXX series.It's designed to measure Barometric Pressure or Atmospheric pressure. BMP180 is a high precision sensor designed for consumer applications.
4) BH1750FVI: is a digital Ambient Light Sensor having I2C interface. This IC is the suitable for obtaining the ambient light data.
## 
### Circuit connections images:
####
![image](https://github.com/NIRANJAN-K-DESHMUKH/Smart-Weather-Station/assets/82277471/4ebb1e2e-5add-4328-b2ab-74c3cb16c82a)
####
![image](https://github.com/NIRANJAN-K-DESHMUKH/Smart-Weather-Station/assets/82277471/cf98a63d-2fbb-4863-a495-9d6096ae1f26)
####
![image](https://github.com/NIRANJAN-K-DESHMUKH/Smart-Weather-Station/assets/82277471/bef5c638-a5bd-4ae5-a09c-514455e1719e)

## 
### Coding in Arduino IDE and uploading in NodeMCU board:
####
![image](https://github.com/NIRANJAN-K-DESHMUKH/Smart-Weather-Station/assets/82277471/cc1509ca-28d1-4a87-8600-100b8289538f)
##
### Sensors' detected Values:
![image](https://github.com/NIRANJAN-K-DESHMUKH/Smart-Weather-Station/assets/82277471/353802d0-f550-4f67-bade-467c5dea7955)

##
### Thingspeak server Configurations:
####
![image](https://github.com/NIRANJAN-K-DESHMUKH/Smart-Weather-Station/assets/82277471/b19c36a6-f65e-4e6d-b34e-082445ce945e)
##
### Data Visualization on the Thingspeak channel:
![image](https://github.com/NIRANJAN-K-DESHMUKH/Smart-Weather-Station/assets/82277471/7b8bf118-50da-47b3-82d6-791331f14c4a)
