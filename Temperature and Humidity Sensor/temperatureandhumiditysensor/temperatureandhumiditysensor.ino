
#include <Arduino.h>
#include <SensirionI2CSht4x.h>
#include <Wire.h>
#include<Streaming.h>
#include <TFT_eSPI.h>

TFT_eSPI tft;
SensirionI2CSht4x sht4x;

void setup() {

    tft.begin();
    tft.fillScreen(TFT_BLACK);
    tft.setTextColor(TFT_WHITE);
    tft.setTextSize(2);
    Serial.begin(115200);
    while (!Serial) {
        delay(100);
    }

    Wire.begin();

    uint16_t error;
    char errorMessage[256];

    sht4x.begin(Wire);

    uint32_t serialNumber;
    error = sht4x.serialNumber(serialNumber);
    if (error) {
        Serial.print("Error trying to execute serialNumber(): ");
        errorToString(error, errorMessage, 256);
        Serial.println(errorMessage);
    } else {
        Serial.print("Serial Number: ");
        Serial.println(serialNumber);
    }
}

void loop() {
    uint16_t error;
    char errorMessage[256];

    delay(1000);

    float temperature;
    float humidity;
    error = sht4x.measureHighPrecision(temperature, humidity);
    if (error) {
        tft.printf("Error trying to execute measureHighPrecision(): ");
        errorToString(error, errorMessage, 256);
        tft.printf(errorMessage);
    } else {
        tft.printf("Temperature:");
        tft<<temperature<<endl;
        tft.printf("\t");
        tft.printf("Humidity:");
        tft<<humidity<<endl;
    }
}
