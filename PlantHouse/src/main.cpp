#include <Arduino.h>
#include <dht.h>
#include <Wire.h>
#include <Adafruit_GFX.h>
#include <Adafruit_SSD1306.h>

//OLED SCREEN SETTINGS
#define SCREEN_WIDTH 128
#define SCREEN_HEIGHT 64
#define SCREEN_ADDR 0x3C
#define OLED_RESET -1

//HARDWARE
#define PUMP 9

//TEMP & HUMIT SENSOR SETTINGS
#define TEMP_SENSOR 10
#define TEMP_TYPE DHT22
DHT dht(TEMP_SENSOR, TEMP_TYPE);
float temp;
float humidity;

//OLED OBJECT
Adafruit_SSD1306 display(SCREEN_WIDTH, SCREEN_HEIGHT, &Wire, OLED_RESET);

void setup() {
  Serial.begin(11500);
  //INIT HARDWARE
  pinMode(PUMP, OUTPUT);
  pinMode(TEMP_SENSOR, OUTPUT);
  //INIT OLED
  if(!display.begin(SSD1306_SWITCHCAPVCC, SCREEN_ADDR)){
    Serial.println(F("SSD1306 allocation failed"));
    for(;;);
  }
  delay(2000);
  display.clearDisplay();
  //INIT TEMP
  dht.begin();
}

void loop() {
  getSensorInfo();
  displayInfo();
}

void getSensorInfo(){
  temp = dht.readTemperature();
  humidity = dht.readHumidity();
  if (isnan(humidity) || isnan(temp)) {
    Serial.println(F("Failed to read from DHT sensor!"));
    return;
  }
}
void displayInfo(){
  //SET TEMP
  display.setCursor(0,0);
  display.write("TEMP : ");
  display.setCursor(0,10);
  display.write(temp);
  //SET HUMIDITY
  display.setCursor(2,0);
  display.write("HUMIDITY");
  display.write(humidity);
}
