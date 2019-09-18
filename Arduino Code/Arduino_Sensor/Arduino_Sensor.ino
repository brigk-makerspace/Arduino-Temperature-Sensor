#include <stdlib.h>
#include "DHT.h"

#define DHTPIN 2        // Digital pin connected to the DHT sensor
#define DHTTYPE DHT11   // DHT 11

DHT dht(DHTPIN, DHTTYPE);

const byte numChars = 32;
char receivedChars[numChars]; // an array to store the received data
int number;
float t,h;

boolean newData = false;

void setup() {
  Serial.begin(9600);
  dht.begin();
  pinMode(A0, INPUT);
  pinMode(A1, INPUT);
  pinMode(A2, INPUT);
  pinMode(A3, INPUT);
  pinMode(A4, INPUT);
  pinMode(A5, INPUT);
  pinMode(3, INPUT);
  pinMode(4, INPUT);
  pinMode(5, INPUT);
  pinMode(6, INPUT);
  pinMode(7, OUTPUT);
  pinMode(8, OUTPUT);
  pinMode(9, OUTPUT);
  pinMode(10, OUTPUT);
  pinMode(11, OUTPUT);
  pinMode(12, OUTPUT);
  pinMode(13, OUTPUT);
}

void loop() {
  recvWithEndMarker();
  showNewData();
}

void readTemperature(){
  delay(2000);
  h = dht.readHumidity();
  t = dht.readTemperature();
}

void recvWithEndMarker() {
  static byte ndx = 0;
  char endMarker = '\n';
  char rc;

  // if (Serial.available() > 0) {
  while (Serial.available() > 0 && newData == false) {
    rc = Serial.read();

    if (rc != endMarker) {
      receivedChars[ndx] = rc;
      ndx++;
      if (ndx >= numChars) {
        ndx = numChars - 1;
      }
    }
    else {
      receivedChars[ndx] = '\0'; // terminate the string
      ndx = 0;
      newData = true;
    }
  }
}

void showNewData() {
  if (newData == true) {
    Serial.println(receivedChars);
    newData = false;
    number = atoi(&receivedChars[1]);

    switch(receivedChars[0]){
      case 'A':
        Serial.print(analogRead(number));
        Serial.print("#");
        break;
      case 'D':
        if (number >= 7) digitalWrite(number, !digitalRead(number));
        Serial.print(digitalRead(number));
        Serial.println("#");
        break;
      case 'T':
        readTemperature();
        Serial.print(h);
        Serial.print('/');
        Serial.print(t);
        Serial.println('#');
        break;
      default:
        break;
    }
  }
}
