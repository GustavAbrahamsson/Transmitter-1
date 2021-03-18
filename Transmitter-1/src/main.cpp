#include <Arduino.h>

#define JS1_X A0
#define JS1_Y A1
#define JS2_X A2
#define JS2_Y A3


int js1_x = 0;
int js1_y = 0;
int js2_x = 0;
int js2_y = 0;

void setup() {
  Serial.begin(9600);
  Serial.println("Program started");

  pinMode(JS1_X, INPUT);
  pinMode(JS1_Y, INPUT);
  pinMode(JS2_X, INPUT);
  pinMode(JS2_Y, INPUT);
}

void loop() {

  delay(10);

  js1_x = analogRead(JS1_X);
  js1_y = analogRead(JS1_Y);
  js2_x = analogRead(JS2_X);
  js2_y = analogRead(JS2_Y);

  Serial.println("1X = " + js1_x);
  Serial.println("1Y = " + js1_y);
  Serial.println("2X = " + js2_x);
  Serial.println("2Y = " + js2_y);
  
  Serial.println();
}