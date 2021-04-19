#include <Arduino.h>
#include <Adafruit_ADS1X15.h>
#include <TM1637Display.h>
#include <SPI.h>

Adafruit_ADS1115 ads;
TM1637Display display(4, 5);

float weight_per_mv = 1;

void setup()
{
  Serial.begin(9600);
  ads.setGain(GAIN_TWOTHIRDS);
  ads.begin();
  display.setBrightness(0x0F);

}

void loop()
{
  // Read the ADC
  float sensor_voltage = ads.readADC_Differential_0_1() * 0.1875;

  // Calibrate to weight
  int16_t weight = sensor_voltage * weight_per_mv;

  // Display and print on Serial
  Serial.println(weight);
  display.clear();
  display.showNumberDec(weight, true);
}