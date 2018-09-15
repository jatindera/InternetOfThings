#include <SoftwareSerial.h>
SoftwareSerial mySerial(2, 3); // RX, TX
 
void setup()
{
 Serial.begin(9600);
 mySerial.begin(9600);
 delay(5000);
 }
 
void loop(){
  
 String IncomingString="";
 boolean StringReady = false;
 
 while (mySerial.available()){
   IncomingString=mySerial.readString();
   StringReady= true;
  }
 
  if (StringReady){
    Serial.println("Received String: " + IncomingString);
  
  }
 }
 
