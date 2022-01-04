#include <Arduino.h>
#include <Wire.h>
#include <VL53L0X.h>

int average;
int Distanc;
int DistancHi;
int DistancLo;
int Real_Dist;

VL53L0X sensor;
int LED_lamp = 6;
unsigned int distance;
void setup() {
  Wire.begin();
pinMode(4, OUTPUT);   //LED_Rot
pinMode(2, OUTPUT);  //LED_Gruen
  pinMode(LED_lamp, OUTPUT);
  digitalWrite(LED_lamp, LOW);
  sensor.setTimeout(512);
  if (!sensor.init())
  {
    while (1) {}
  }
  sensor.startContinuous();
  long sum = 0;                                     // локальная переменная sum
  for (int i = 0; i < 100; i++) {          // согласно количеству усреднений
    sum += sensor.readRangeContinuousMillimeters(); // суммируем значения дистанции в переменную sum
  }
  average = sum / 100;                     // находим среднее арифметическое, разделив сумму на число измерений
  Distanc = average / 10;
  DistancHi = average + 48;
  DistancLo = average - 48;
}
void loop()
{
  // read the input on analog pin 1:
  int sensorValue = analogRead(1);
if (sensorValue >= 737 && sensorValue <= 797){ // 3.6v - 3.9v
digitalWrite(2, HIGH); 
digitalWrite(3, HIGH);
}
if (sensorValue >= 675 && sensorValue <= 736){ // 3.6v - 3.3v
digitalWrite(2, LOW); 
digitalWrite(3, HIGH);
delay(128);
digitalWrite(2, LOW);
delay(128);}
if (sensorValue >= 614 && sensorValue <= 674){  // 3.3v - 3.0v
digitalWrite(2, LOW); 
digitalWrite(3, HIGH);
}
if (sensorValue <= 613){              // 3.0v
digitalWrite(3, HIGH); 
digitalWrite(2, LOW);
delay(128);
digitalWrite(3, LOW);
delay(128);
}
    Real_Dist = sensor.readRangeContinuousMillimeters();
  if ((Real_Dist < DistancHi) && (Real_Dist > DistancLo))
    {  digitalWrite(LED_lamp, HIGH);}
else { digitalWrite(LED_lamp, LOW);}
  delay(512);
}