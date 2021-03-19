
#include <Arduino.h>

/*
#include <SPI.h>
#include <nRF24L01.h>
#include <RF24.h>
*/


// NRF24L01
#define CE 7
#define CSN 8
#define MOSI 11
#define MISO 12
#define SCK 13

// Joysticks
#define JS1_X A0
#define JS1_Y A1
#define JS1_SW 6

#define JS2_X A2
#define JS2_Y A3
#define JS2_SW 10

// Rotary encoder
#define CLK 4
#define DT 5
#define RE_SW 9

// General
#define TGL_SW 3
#define BTN1 2

// Joystick values
int js1_x = 0;
int js1_y = 0;
bool js1_sw = 0;

int js2_x = 0;
int js2_y = 0;
bool js2_sw = 0;

// Rotary encoder
int state1CLK = 0;
int state0CLK = 0;
int rotaryValue = 0;
bool re_sw = 0;

void setup() {

  Serial.begin(9600);
  Serial.println("Program started");

  pinMode(JS1_X, INPUT);
  pinMode(JS1_Y, INPUT);
  pinMode(JS1_SW, INPUT_PULLUP);
  pinMode(JS2_X, INPUT);
  pinMode(JS2_Y, INPUT);
  pinMode(JS2_SW, INPUT_PULLUP);

  pinMode(CLK, INPUT);
  pinMode(DT,  INPUT);
  pinMode(RE_SW, INPUT_PULLUP);

  pinMode(TGL_SW, INPUT_PULLUP);
  pinMode(BTN1, INPUT_PULLUP);





  pinMode(2,INPUT_PULLUP);

}

void loop() {

  delay(1);

  js1_x = analogRead(JS1_X);
  js1_y = analogRead(JS1_Y);
  js2_x = analogRead(JS2_X);
  js2_y = analogRead(JS2_Y);

  js1_sw = !digitalRead(JS1_SW);
  js2_sw = !digitalRead(JS2_SW);
  re_sw = !digitalRead(RE_SW);

  Serial.println(digitalRead(2));

  state1CLK = digitalRead(CLK);

  if(state1CLK != state0CLK){
    if(digitalRead(DT) != state1CLK){
      rotaryValue--;
    }else{
      rotaryValue++;
    }
  }
  state0CLK = state1CLK;

  /*

  Serial.print("1: "); Serial.print(js1_x); Serial.print(" | ");Serial.print(js1_y);Serial.print(" | ");Serial.println(js1_sw);

  Serial.print("2: "); Serial.print(js2_x); Serial.print(" | ");Serial.print(js2_y);Serial.print(" | ");Serial.println(js2_sw);
  
  Serial.println("");

  Serial.print("RE: "); Serial.print(rotaryValue); Serial.print(" | ");Serial.println(re_sw);

  Serial.println("");
  */
}