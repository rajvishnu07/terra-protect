#include <Arduino.h>
#include <TFT_eSPI.h>
#include <Wire.h>
#include <SensirionI2CSht4x.h>

TFT_eSPI tft;
SensirionI2CSht4x sht;

void setup() {
    tft.begin();
    tft.setRotation(3);
    tft.fillScreen(TFT_BLACK);
    tft.setTextColor(TFT_WHITE);
    tft.setTextSize(2);
    Wire.begin();
    sht.begin(Wire);
}

void loop() {
    float temperature;
    float humidity;
    uint16_t error = sht.measureHighPrecision(temperature, humidity);

    if (error) {
        tft.setCursor(0, 0);
        tft.printf("Error: %d", error);
    } else {
        tft.setCursor(40, 50);
        tft.printf("Temperature: %0.2f C", temperature);
        tft.setCursor(40, 80);
        tft.printf("Humidity: %0.2f %%", humidity);
    }

    delay(2000);
    tft.fillScreen(TFT_BLACK);
}
