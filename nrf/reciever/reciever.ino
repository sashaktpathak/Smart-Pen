#include <SPI.h>
#include <nRF24L01.h>
#include <RF24.h>
RF24 radio(7, 8); // CE, CSN
const byte address[6] = "12341";
void setup() {
  Serial.begin(9600);
  pinMode(2,INPUT_PULLUP);
  radio.begin();
  radio.openReadingPipe(0, address);
  radio.setPALevel(RF24_PA_MAX);
  radio.startListening();
}
void process(char *t)
{
  int i=0;
  while(t[i])
  {
    if(t[i]=='!')
      Serial.print(" ");
    else
      Serial.print(t[i]);
    i++; 
  }
  Serial.println();
}
void loop() {
  if(radio.isChipConnected())
  {
    //Serial.println("ndkd;sa,");
  }
  if (radio.available()) {
    char text[16] = "";
    radio.read(&text, sizeof(text));
    if(text[0]!='@')
      process(text);
    else
    {
      Serial.println("-11111 -11111 -11111");
    }
  }
}
