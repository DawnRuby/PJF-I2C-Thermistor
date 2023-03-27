#include <Wire.h>


int ThermistorPin = 0;
int ThermistorPin2 = 1;
int Temp1Address = 1;
int Temp2Address = 2; 
int curTemp1;
int curTemp2;
int curTemp3;
int Vo;
float R1 = 10000;
float logR2, R2, T;
float c1 = 1.009249522e-03, c2 = 2.378405444e-04, c3 = 2.019202697e-07;


void setup() {
  // put your setup code here, to run once:
  Serial.begin(9600);
  Wire.begin(1);
  Wire.begin(2);
  Wire.onRequest(requestEvent);
}

void loop() {
  // Get value of the first Thermistor
  Vo = analogRead(ThermistorPin);
  R2 = R1 * (1023.0 / (float)Vo - 1.0);
  logR2 = log(R2);
  T = (1.0 / (c1 + c2*logR2 + c3*logR2*logR2*logR2));
  T = T - 273.15;
  curTemp1 = T;

  Serial.print("Temperature 1 is: "); 
  Serial.print(T);
  Serial.println(" C");
  Wire.beginTransmission(Temp1Address);
  Wire.write((int)T);
  Wire.endTransmission();
  delay(500);

  // Get value of the second Thermistor
  Vo = analogRead(ThermistorPin2);
  R2 = R1 * (1023.0 / (float)Vo - 1.0);
  logR2 = log(R2);
  T = (1.0 / (c1 + c2*logR2 + c3*logR2*logR2*logR2));
  T = T - 273.15;
  curTemp2 = T;

  Serial.print("Temperature 2 is: "); 
  Serial.print(T);
  Serial.println(" C");
  Wire.beginTransmission(Temp2Address);
  Wire.write((int)T);
  Wire.endTransmission();
  delay(1000);
}

void requestEvent(){
  // Send Thermistor Temperature 1 to i2c
  Wire.beginTransmission(Temp1Address);
  Wire.write(curTemp1);
  Wire.endTransmission();
  delay(50);

  // Send Thermistor Temperature 2 to i2c
  Wire.beginTransmission(Temp2Address);
  Wire.write(curTemp2);
  Wire.endTransmission();
  delay(50);
}
