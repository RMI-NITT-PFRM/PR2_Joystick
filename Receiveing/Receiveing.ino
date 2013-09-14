/*
-----Joystick data recieve code ver 1.00--------
-----By Ashwin Narayan@RMI-NITT-----------------
  
  This is the side of the code that recieves the 
  joystick data over the RF link. Upload this code
  to the arduino on the PR2 which controls the camera
  motion. Connect the data pin of the RF recieve
  module to pin 11.
  
*/

#include <VirtualWire.h>

String sensorData;

void setup()
{
  Serial.begin(9600); //Debugging
  Serial.println("Setup");
  pinMode(12, OUTPUT);
  
  vw_setup(2000); //Initialize communication at 2000 bits/sec
  vw_rx_start();  //Start the receiver
}

void loop()
{
  uint8_t buf[VW_MAX_MESSAGE_LEN];
  uint8_t buflen = VW_MAX_MESSAGE_LEN;
  char receivedData[12];
  
  if (vw_get_message(buf, &buflen)) // Non-blocking
  {
	int i;

        digitalWrite(13, true); // Flash a light to show received good message
	// Message with a good checksum received, dump it.
	Serial.print("Got: ");
	
	for (i = 0; i < buflen; i++)
	{
	    Serial.print((char)buf[i]);
            if(i<12) receivedData[i] = (char)buf[i];
	    Serial.print(" ");
	}
	Serial.println("");
        sensorData = (String)receivedData;
        Serial.println(sensorData);
        Serial.println("");
        digitalWrite(13, false);
    }
}
