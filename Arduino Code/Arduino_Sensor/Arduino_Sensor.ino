#include <stdlib.h>

const byte numChars = 32;
char receivedChars[numChars]; // an array to store the received data
int number;

boolean newData = false;

void setup() {
 Serial.begin(9600);

 pinMode(A0,INPUT);
  pinMode(A1,INPUT);
  pinMode(A2,INPUT);
  pinMode(A3,INPUT);
  pinMode(A4,INPUT);
  pinMode(A5,INPUT);
  pinMode(0,INPUT);
  pinMode(1,INPUT);
  pinMode(2,INPUT);
  pinMode(3,INPUT);
  pinMode(4,INPUT);
  pinMode(5,INPUT);
  pinMode(6,INPUT);
  pinMode(7,OUTPUT);
  pinMode(8,OUTPUT);
  pinMode(9,OUTPUT);
  pinMode(10,OUTPUT);
  pinMode(11,OUTPUT);
  pinMode(12,OUTPUT);
  pinMode(13,OUTPUT);
}

void loop() {
 recvWithEndMarker();
 showNewData();
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

  if(receivedChars[0] == 'A')
    {
      Serial.println(analogRead(number));
    }
    else
    {
      if(number>=7) digitalWrite(number, !digitalRead(number));
      else Serial.println(digitalRead(number));
    }
 }
}
