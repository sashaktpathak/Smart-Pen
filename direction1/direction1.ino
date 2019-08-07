#include <QMC5883L.h>

QMC5883L compass;
int prev_x,prev_y,prev_z,prev_t,pr;
void setup()
{
  compass.init();
  compass.setSamplingRate(50);

  Serial.begin(9600);
  //Serial.println("QMC5883L Compass Demo");
  //Serial.println("Turn compass in all directions to calibrate....");
  pr = compass.readRaw(&prev_x,&prev_y,&prev_z,&prev_t);
} 
void loop()
{
  while(1) {
    int heading = compass.readHeading();
    int r;
    int16_t x,y,z,t;

    if(heading==0) {
      /* Still calibrating, so measure but don't print */
    }
    else {
      //Serial.println(heading);
      r = compass.readRaw(&x,&y,&z,&t); 
      //Serial.print(x);
      //Serial.print(" ");
      //Serial.print(y);
      //Serial.print(" ");
      //Serial.print(z);
      if(abs(y-prev_y) >= 200 && y < prev_y)
      {
        Serial.println("UP");
        prev_y = y;
      }
      else if(abs(y-prev_y) >= 200 && y > prev_y)
      {
        Serial.println("DOWN");
        prev_y = y;
      }
      else if(abs(z-prev_z) >= 200 && z < prev_z)
      {
        Serial.println("LEFT");
        prev_z = z;
      }
      else if(abs(z-prev_z) >= 200 && z > prev_z)
      {
        Serial.println("RIGHT");
        prev_z = z;
      }
    }
    delay(500);
  }
}
