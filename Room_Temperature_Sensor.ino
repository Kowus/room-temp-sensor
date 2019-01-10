// Color definitions
#define BLACK           0x0000
#define BLUE            0x001F
#define RED             0xF800
#define GREEN           0x07E0
#define CYAN            0x07FF
#define MAGENTA         0xF81F
#define YELLOW          0xFFE0
#define WHITE           0xFFFF
#define dc   8
#define cs   10
#define rst  9
#define DHTPIN 3
#define DHTTYPE DHT11

#include <Adafruit_GFX.h>
#include <Adafruit_SSD1351.h>
#include <SPI.h>
#include "DHT.h"



Adafruit_SSD1351 tft = Adafruit_SSD1351(cs, dc, rst);
DHT dht(DHTPIN, DHTTYPE);

int tft_height, tft_width;
char deg = 248;

void setup() {
  // put your setup code here, to run once:
  Serial.begin(9600);
  dht.begin();
  tft.begin();
  tft_height = tft.height();
  tft_width = tft.width();
  tft.fillScreen(BLACK);
  tft.drawRect((tft_width - 1) / 2, (tft_height - 1) / 2, tft_width / 2, tft_height / 2, WHITE);
  tft.setCursor((tft_width / 2) + 6, (tft_height / 2) + 8);
  tft.println("Humidity");
  tft.drawFastHLine((tft_width / 2) + 6, (tft_height / 2) + 16, (tft_width / 2) - 16, WHITE);
  tft.setCursor(tft_width - 10, (tft_height / 2) + 24);
  tft.print("%");
}

void loop() {
  // put your main code here, to run repeatedly:
  int humidity = dht.readHumidity() * 100;
  int top = humidity / 100, bot = humidity % 100;
  String mult = String(top) + "." + String(bot);
  tft.setTextSize(2);
  tft.setCursor((tft_width / 2) + 6, (tft_height / 2) + 35);
  tft.fillRect((tft_width / 2) + 6, (tft_height / 2) + 35, 30, 20, BLACK);
  //  String me = String("%0.2f", humidity);
  tft.print(mult);
  tft.setTextSize(3);
  tft.fillRect(0, 0, (tft_width / 2) - 10, tft_height, BLACK);
  tft.setCursor(0, 80);
  int temp = (int)(dht.readTemperature());
  //  int ttop = temp/100, tbot = temp%100;
  //  String temperature = String(ttop)+"."+String(tbot);
  tft.setTextColor(WHITE);
  tft.print(temp);
  tft.setCursor(30, 60);
  tft.print(deg);
  tft.setCursor(43, 80);
  tft.print('C');
  //  Serial.println(temperature);
  delay(2000);


}
