/*
-----Joystick data transmission code ver 1.00---
-----By Ashwin Narayan@RMI-NITT-----------------
  
  This is the transmission side of the the code.
  Upload this code to the arduino which takes the
  readings from the joystick. Connect the X reading
  of the joystick to pin A0 and the Y-reading of the
  joystick to pin A1. Connect the data pin of the RF
  module to pin 12.
  
*/

#include <VirtualWire.h>

int JoyStickXPin = A0; //Connect Joystick x axis output to pin A0
int JoyStickYPin = A1; //Connect Joystick y axis output to pin A1
int SensorValX   = 0;  //Stores X sensor reading
int SensorValY   = 0;  //Stores Y sensor reading
int debugLEDPin  = 13; //For debugging

String sensorData= "";
const char *RF_Message = "Hello!";

void setup()
{
  Serial.begin(9600); //Start serial monitor for debugging
  pinMode(debugLEDPin, OUTPUT); //Set the LED pinmode to output
  sensorData.reserve(11);
  
  vw_setup(2000);        //Setup the virtualwire library to transmit
                         //at 2000 bits per second. Connect the data
                         //pin of the transmitter module to pin 12 of
                         //the arduino.
}

void loop()
{
  sensorData = "X";
  SensorValX = analogRead(JoyStickXPin); //Read the values from
  SensorValY = analogRead(JoyStickYPin); //the joystick
  
  //Pack the sensor data into a suitable format for sending over RF link
  sensorData += SensorValX;
  sensorData += ",";
  sensorData += SensorValY;
  sensorData += "Y";
  //Print sensor data
  Serial.println(sensorData);
  //Convert to c string for sending over RF
  RF_Message = sensorData.c_str();
  
  //Flash LED to show message is being sent
  digitalWrite(debugLEDPin, true);
  vw_send((uint8_t *)RF_Message, strlen(RF_Message)); //Send
  vw_wait_tx(); //Wait until whole message is gone
  digitalWrite(debugLEDPin, false);
  
  delay(10);
}

