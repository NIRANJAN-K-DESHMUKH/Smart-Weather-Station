#include <Adafruit_BMP085.h>

#include <ESPWiFi.h>
#include <ESPHTTPClient.h>
#include <JsonListener.h>

// time
#include <time.h>                       // time() ctime()
#include <sys/time.h>                   // struct timeval

#include "SSD1306Wire.h"
#include "OLEDDisplayUi.h"
#include "Wire.h"
#include "OpenWeatherMapCurrent.h"
#include "OpenWeatherMapForecast.h"
#include "WeatherStationFonts.h"
#include "WeatherStationImages.h"
#include <ESP8266WiFi.h>

#include <Adafruit_BMP085.h>

/*WIFI Settings*/
const char* WIFI_SSID = "N";
const char* WIFI_PWD = "harharmahadev";

/*Begin DHT11 Settings*/
WiFiClient client;
const char *host = "api.thingspeak.com";                  //IP address of the thingspeak server
const char *api_key ="LSIQ3M7BAQ7C372L";                  //Your own thingspeak api_key
const int httpPort = 80;
#define pin 14       // ESP8266-12E  D5 read temperature and Humidity data
int temp = 0; //temperature
int humi = 0; //humidity
void readTemperatureHumidity();
void uploadTemperatureHumidity();
long readTime = 0; 
long uploadTime = 0; 

/*Begin Atmosphere and Light Sensor Settings*/
void readLight();
void readAtmosphere();
Adafruit_BMP085 bmp;
const int Light_ADDR = 0b0100011;   // address:0x23
const int Atom_ADDR = 0b1110111;  // address:0x77
int tempLight = 0;
int tempAtom = 0;


#if defined(ESP8266)
const int SDA_PIN = D3;
const int SDC_PIN = D4;
#else
const int SDA_PIN = GPIO0;
const int SDC_PIN = GPIO2 
#endif

const boolean IS_METRIC = true;

void setup() {
  Serial.begin(115200);

  Wire.begin(0,2);
  
  Wire.beginTransmission(Atom_ADDR);
  //initialize Atmosphere sensor
  if (!bmp.begin()) {
    Serial.println("Could not find BMP180 or BMP085 sensor at 0x77");
  }else{
    Serial.println("Find BMP180 or BMP085 sensor at 0x77");
  }
  Wire.endTransmission();

  //initialize light sensor
  Wire.beginTransmission(Light_ADDR);
  Wire.write(0b00000001);
  Wire.endTransmission();

  WiFi.begin(WIFI_SSID, WIFI_PWD);  
}

void loop() {  
  //Read Temperature Humidity every 5 seconds
  if(millis() - readTime > 5000){
    readTemperatureHumidity();
    readLight();
    readAtmosphere();
    readTime = millis();
  }
}

void setReadyForWeatherUpdate() {
  Serial.println("Setting readyForUpdate to true");
  readyForWeatherUpdate = true;
}

//read temperature humidity data
void readTemperatureHumidity(){
  int j;
  unsigned int loopCnt;
  int chr[40] = {0};
  unsigned long time1;
bgn:
  delay(2000);
  //Set interface mode 2 to: output
  //Output low level 20ms (>18ms)
  //Output high level 40μs
  pinMode(pin, OUTPUT);
  digitalWrite(pin, LOW);
  delay(20);
  digitalWrite(pin, HIGH);
  delayMicroseconds(40);
  digitalWrite(pin, LOW);
  //Set interface mode 2: input
  pinMode(pin, INPUT);

  //Start reading the value of bit1-40
  //Humidity, 8-bit, converted to a value
  humi = chr[0] * 128 + chr[1] * 64 + chr[2] * 32 + chr[3] * 16 + chr[4] * 8 + chr[5] * 4 + chr[6] * 2 + chr[7];
  //Temperature, 8-bit bit, converted to a value
  temp = chr[16] * 128 + chr[17] * 64 + chr[18] * 32 + chr[19] * 16 + chr[20] * 8 + chr[21] * 4 + chr[22] * 2 + chr[23];

    Serial.print("temp:");
    Serial.print(temp);
    Serial.print("    humi:");
    Serial.println(humi);
 
}

void readLight(){
  // reset
  Wire.beginTransmission(Light_ADDR);
  Wire.endTransmission();
 
  // typical read delay 120ms
  delay(120);
  Wire.requestFrom(Light_ADDR, 2); // 2byte every time
  for (tempLight = 0; Wire.available() >= 1; ) {
    char c = Wire.read();
    tempLight += c;
  }

  Serial.print("light: ");
  Serial.println(tempLight);
}


void readAtmosphere(){
  tempAtom = bmp.readPressure();
  Serial.print("Pressure = ");
  Serial.print(tempAtom);
  Serial.println(" Pascal");
}

//update temperature humidity data 
void uploadTemperatureHumidity(){
   if(!client.connect(host, httpPort)){
    Serial.println("connection failed");
    return;
  }
  
  client.print(String("GET ") + "/update?api_key="+api_key+"&field1="+temp+"&field2="+humi + "&field3="+tempLight+"&field4="+tempAtom+" HTTP/1.1\r\n" +"Host: " + host + "\r\n" + "Connection: close\r\n\r\n");
  while(client.available()){
    String line = client.readStringUntil('\r');
    Serial.print(line);
  }
}


