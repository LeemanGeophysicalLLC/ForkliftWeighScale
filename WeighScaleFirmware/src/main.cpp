#include <Arduino.h>
#include <Adafruit_ADS1X15.h>
#include <TM1637Display.h>
#include <SPI.h>

Adafruit_ADS1115 ads;
TM1637Display display(4, 5);

float weight_per_mv = 2.54024511;
float tare_weight = 0;
const uint8_t navg = 250;


void setup()
{
  Serial.begin(9600);
  display.setBrightness(0x0F);
  display.clear();
  display.showNumberDec(4444);
  delay(1000);
  display.showNumberDec(3333);
  delay(1000);
  display.showNumberDec(2222);
  delay(1000);
  ads.setGain(GAIN_TWOTHIRDS);
  ads.begin();
  display.showNumberDec(1111);
  delay(1000);
  display.showNumberDec(0000);
  
  pinMode(6, INPUT_PULLUP);

}

void loop()
{
  // Read the ADC
  float sensor_voltage = 0;
  for (int i=0; i<navg; i++)
  {
    sensor_voltage += ads.readADC_Differential_0_1() * 0.1875;
  }
  sensor_voltage /= navg;

  // Calibrate to weight
  int16_t weight = sensor_voltage * weight_per_mv;

  // Display and print on Serial
  Serial.print(sensor_voltage);
  Serial.print(",");
  Serial.print(weight);
  Serial.print(",");
  Serial.print(tare_weight);
  Serial.print(",");
  Serial.println(weight - tare_weight);
  display.clear();
  display.showNumberDec(weight - tare_weight, true);

  // See if we are getting a new tare weight
  if (digitalRead(6) == LOW)
  {
    delay(500);
    if (digitalRead(6) == LOW)
    {
      Serial.println("TARE!");
      tare_weight = weight;
    }
  }

  //delay(1000);
}