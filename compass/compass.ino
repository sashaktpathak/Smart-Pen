#include <QMC5883L.h>
#include <SPI.h>
#include <nRF24L01.h>
#include <RF24.h>
#include <stdio.h>
#include<string.h>
#define sizz 50
RF24 radio(6, 8); // CE, CSN

const byte address[6] = "12341";
int mem[150][100];
QMC5883L compass;
int prev_x,prev_y,prev_z,prev_t,pr;
int swtch = 2;
int swtch2 = 3;
//===============================================
char arr[]={'0','1','2','3','4','5','6','7','8','9'};
int inttoch(int num,char *ch)
{
  //char ch[32]="";
  int nf=0,len=0,t,i;
  if(num<0)
    {nf=1; num = num*-1;}
  t = num;
  while(t>0)
  {
    len++;
    t=t/10;   
  }
  //printf("%d",len);
  t=num;
  if(nf==0)
  {
    ch[len]='\0';
    for(i=0;i<len;i++)
    {
      ch[len-i-1] = arr[t%10];
      t=t/10;
    }
  }
  if(nf==1)
  {
    ch[len+1]='\0';
    for(i=0;i<len;i++)
    {
      ch[len-i] = arr[t%10];
      t=t/10;
    }
    ch[0]='-';
  }
  //printf("%s",ch);
  if(nf==1)
  len++;
  return len;
}

//------------------------------------------------
void setup()
{
  radio.begin();
  radio.openWritingPipe(address);
  radio.setPALevel(RF24_PA_MAX);
  radio.stopListening();
	compass.init();
	compass.setSamplingRate(50);
  pinMode(swtch,INPUT_PULLUP);
  pinMode(swtch2,INPUT_PULLUP);
	Serial.begin(9600);
  pr = compass.readRaw(&prev_x,&prev_y,&prev_z,&prev_t);
} 
void loop()
{
	while(1) {
    //Serial.println("test");
		int heading = compass.readHeading();
    int r;
    int16_t x,y,z,t,l1,l2,l3;
    char buf1[sizz],buf2[sizz],buf3[sizz];
    fflush(stdin);
		if(heading==0) {
			/* Still calibrating, so measure but don't print */
		}
		else {
			char exm[]="!";
      char fin[sizz]="";
			//Serial.println(heading);
		  r = compass.readRaw(&x,&y,&z,&t); 
      //sprintf(buf1,"%d",x);
      //sprintf(buf2,"%d",y);
      //sprintf(buf3,"%d",z);
      l1=inttoch(x,buf1);
      l2=inttoch(y,buf2);
      l3=inttoch(z,buf3);
      strcat(fin,buf1);
      strcat(fin,exm);
      strcat(fin,buf2);
      strcat(fin,exm);
      strcat(fin,buf3);
      int fin_size = l1+l2+l3+2;
      if(digitalRead(swtch2)==0)
       {
        char chat[]= "@@";
        radio.write(&chat,2);
       }
      else if(digitalRead(swtch)==0)
        {radio.write(&fin, fin_size);
         Serial.println(fin);
         delay(300);
         continue;
        }
      
    }
    delay(300);
	}
}
