/**************************************************
Author:         Fawaaz Kamali Siddiqui
Last Update:    3 August 2023
===================================================
Description:    With the help of an IR receiver, a TV remote
                is used to control the robot. Two motor drivers
                were used for this project and it was powered
                from an Arduino Uno.
===================================================
Connections:    First motor driver
                enA:                 10
                in1:                 4
                in2:                 5
                Second motor driver
                enB:                 10
                in3:                 6
                in4:                 7
                
                green LED:           13
                red LED:             12
                IR receiver:         8                
**************************************************/


#include <IRremote.h>

// Instantiations - for devices with seperate libraries
const int RECV_PIN = 8;
IRrecv IR(RECV_PIN);

// variable declaration section
int enA = 9; // 9
int in1 = 4; // 4
int in2 = 5; // 5
int enB = 10; // 10
int in3 = 6; // 6
int in4 = 7; // 7

int redLEDPin = 12;
int greenLEDPin = 13;

bool isOn = false;  // to check current robot setting

void setup() {
  
    Serial.begin(9600);

    pinMode(enA, OUTPUT);
    pinMode(enB, OUTPUT);
    pinMode(in1, OUTPUT);
    pinMode(in2, OUTPUT);
    pinMode(in3, OUTPUT);
    pinMode(in4, OUTPUT);

    analogWrite(enA, 150);
    analogWrite(enB, 150);

    IR.enableIRIn();

    pinMode(redLEDPin, OUTPUT);
    pinMode(greenLEDPin, OUTPUT);

    isOn = false;

}

void loop() {
    while (true) {
        if (!isOn) {
            digitalWrite(redLEDPin, HIGH);
            digitalWrite(greenLEDPin, LOW);
        }
        if (IR.decode()) 
        {
            Serial.println(IR.decodedIRData.decodedRawData, HEX);

            if (!isOn) {
                if (IR.decodedIRData.decodedRawData == 0x13AD || IR.decodedIRData.decodedRawData == 0x1BAD) { // Blue 'off' button
                    isOn = true;
                    digitalWrite(greenLEDPin, HIGH);
                    digitalWrite(redLEDPin, LOW);
                }            
            }
            else {
                if (IR.decodedIRData.decodedRawData == 0x138C || IR.decodedIRData.decodedRawData == 0x1B8C) { // Red 'off' button
                    isOn = false;
                    digitalWrite(greenLEDPin, LOW);
                    digitalWrite(redLEDPin, HIGH);
                    stop();
                }
                else if (IR.decodedIRData.decodedRawData == 0x13BD || IR.decodedIRData.decodedRawData == 0x1BBD) { // arrow up button
                    moveForward();
                }
                else if (IR.decodedIRData.decodedRawData == 0x13BE || IR.decodedIRData.decodedRawData == 0x1BBE) { // arrow down button
                    moveBackward();
                }
                else if (IR.decodedIRData.decodedRawData == 0x13AB || IR.decodedIRData.decodedRawData == 0x1BAB) { // arrow right button
                    rotateRight();
                }
                else if (IR.decodedIRData.decodedRawData == 0x1BBF || IR.decodedIRData.decodedRawData == 0x13BF) { // arrow left button
                    rotateLeft();
                }
            }        
            
            delay(15);
            // stop();
            IR.resume(); // tells the receiver to read the next data
        }
    }

}

// Motor methods

void moveForward() {
    digitalWrite(in1, LOW);
    digitalWrite(in2, HIGH);
    digitalWrite(in3, LOW);
    digitalWrite(in4, HIGH);
}

void moveBackward() {
    digitalWrite(in1, HIGH);
    digitalWrite(in2, LOW);
    digitalWrite(in3, HIGH);
    digitalWrite(in4, LOW);
}

void rotateRight() {
    digitalWrite(in1, HIGH);
    digitalWrite(in2, LOW);
    digitalWrite(in3, LOW);
    digitalWrite(in4, HIGH);
}

void rotateLeft() {
    digitalWrite(in1, LOW);
    digitalWrite(in2, HIGH);
    digitalWrite(in3, HIGH);
    digitalWrite(in4, LOW);
}

void stop() {
    digitalWrite(in1, LOW);
    digitalWrite(in2, LOW);
    digitalWrite(in3, LOW);
    digitalWrite(in4, LOW);
}
