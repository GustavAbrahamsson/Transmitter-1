
#include <Arduino.h>

#include <SPI.h>
#include <nRF24L01.h>
#include <RF24.h>

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
#define JS2_SW 10  // Pin 10 happened to be the SS (Slave Select) pin!

// Rotary encoder
#define CLK 4
#define DT 5
#define RE_SW 9

// General
#define TGL_SW 3
#define BTN1 2  // Isn't used.

// General
unsigned long timeVar = 0;

// Joystick values
int js1_x = 0;
int js1_y = 0;
bool js1_sw = 0;

int js2_x = 0;
int js2_y = 0;
// bool js2_sw = 0;

// Rotary encoder
int state1CLK = 0;
int state0CLK = 0;
int rotaryValue = 0;
bool re_sw = 0;

// Toggle switch
bool tgl_sw = 0;

// Switch
bool btn_sw = 0;

// NRF24L01
RF24 radio(7, 8); // CE, CSN
const byte address[6] = "35075";
char package[64] = "";

String analogToString(int data){
  if(data == 0) return "0000";
  String output;
  char numberOfDigits = log10(abs(data)) + 1;
  for(char i = 0; i < 4 - numberOfDigits; i++) output += "0";
  output += String(abs(data));
  return output;
}

String rotaryToString(int data){
  String output;
  if(data >= 0){
    output += "0"; // If positive, add a zero
  }
  else if(data < 0) {
    output += "1"; // If negative, add a one
  }
  output += analogToString(data);
  return output;
}

void setupNRF() {
  radio.begin();
  radio.openWritingPipe(address);
  radio.setPALevel(RF24_PA_MIN);
  radio.stopListening();
}

void sendData(const char data[]) {
  strcpy(package, data);
  radio.write(&package, sizeof(package));
}

void sendAllData(){
  String data = "";

  data += analogToString(js1_x);        // 4: 0-3
  data += analogToString(js1_y);        // 4: 4-7
  data += String(js1_sw);               // 1: 8
  
  data += analogToString(js2_x);        // 4: 9-12
  data += analogToString(js2_y);        // 4: 13-16
  // data += String(js2_sw);

  data += String(tgl_sw);               // 1: 17

  data += rotaryToString(rotaryValue);  // 5: 18-22 (signed + 4)
  data += String(re_sw);                // 23

  //data += String(btn_sw);               (// 24)

  char charData[data.length()];
  strcpy(charData, data.c_str());
  Serial.println(charData);
  sendData(charData);
}

void setup() {

  setupNRF();

  //Serial.begin(9600);
  //Serial.println("Program started");

  pinMode(JS1_X, INPUT);
  pinMode(JS1_Y, INPUT);
  pinMode(JS1_SW, INPUT_PULLUP);
  pinMode(JS2_X, INPUT);
  pinMode(JS2_Y, INPUT);
  pinMode(JS2_SW, OUTPUT); // Made it OUTPUT since SS is affecting SPI

  pinMode(CLK, INPUT);
  pinMode(DT,  INPUT);
  pinMode(RE_SW, INPUT_PULLUP);

  pinMode(TGL_SW, INPUT_PULLUP);
  pinMode(BTN1, INPUT_PULLUP);

  pinMode(2,INPUT_PULLUP);
}

void loop() {
  js1_x = analogRead(JS1_X);
  js1_y = 1023 - analogRead(JS1_Y);
  js2_x = analogRead(JS2_X);
  js2_y = 1023 - analogRead(JS2_Y);

  js1_sw = !digitalRead(JS1_SW);
  //js2_sw = !digitalRead(JS2_SW);
  re_sw = !digitalRead(RE_SW);

  tgl_sw = !digitalRead(TGL_SW);

  //btn_sw = !digitalRead(BTN1);

  //Serial.println(btn_sw);

  state1CLK = digitalRead(CLK);

  if(state1CLK != state0CLK){
    if(digitalRead(DT) != state1CLK){
      if(rotaryValue < 1023) rotaryValue++;
    }else{
      if(rotaryValue > -1023) rotaryValue--;
    }
  }
  state0CLK = state1CLK;

  if(millis() - timeVar > 100){
    timeVar = millis();

    sendAllData();
    /*
    Serial.print("1: "); Serial.print(js1_x); Serial.print(" | ");Serial.print(js1_y);Serial.print(" | ");Serial.println(js1_sw);

    Serial.print("2: "); Serial.print(js2_x); Serial.print(" | ");Serial.print(js2_y);Serial.print(" | ");Serial.println(js2_sw);
    
    Serial.println("");

    Serial.print("RE: "); Serial.print(rotaryValue); Serial.print(" | ");Serial.println(re_sw);

    Serial.print("TGL: "); Serial.print(tgl_sw);

    Serial.println();
    Serial.println();
    Serial.println();
    */

  }
}