/*
* Arduino Wireless Communication Tutorial
*     Example 1 - Transmitter Code
*                
* by Dejan Nedelkovski, www.HowToMechatronics.com
* 
* Library: TMRh20/RF24, https://github.com/tmrh20/RF24/
*/

#include <SPI.h>
//#include <nRF24L01.h>
#include <RF24.h>

RF24 radio(6, 8); // CE, CSN

const byte address[6] = "00001";

void setup() {
  radio.begin();
  radio.openWritingPipe(address);
  radio.setPALevel(RF24_PA_MAX);
  radio.stopListening();
  Serial.begin(9600);
}

void loop() {
  Serial.println("Testing");
  if(radio.isChipConnected())
    Serial.println("afs");
  const char text[] = "Hello World";
  radio.write(&text, sizeof(text));
  const char text1[] = "test1";
  radio.write(&text1, sizeof(text1));
  const char text2[] = "dgtttt";
  radio.write(&text2, sizeof(text2));
  delay(1000);
}
