#ifndef GY273
#define GY273
	#include <Wire.h> //I2C Arduino Library

	#define GY273_X 1
	#define GY273_Y 2
	#define GY273_Z 3

	#define address 0x0D //0011110b, I2C 7bit address of HMC5883

	#define GY273_SUCCESS 1
	#define GY273_INVALID_PIN -1
	#define GY273_DATA_NOT_AVAILABLE -2


	int GY273Setup()
	{ ////Initialize Serial and I2C communications
		Wire.begin();
		Wire.beginTransmission(address); //open communication with HMC5883
		Wire.write(0x0B);
		Wire.write(0x01);
		Wire.write(0x09); //select mode register
		Wire.write(0x1D); //continuous measurement mode
		Wire.endTransmission();
		return GY273_SUCCESS;
	}

	int GY273Read(unsigned int pin, int * value)
	{
		int x, y, z, xl, yl, zl; //triple axis data
		Wire.beginTransmission(address); //Tell the HMC5883 where to begin reading data
		Wire.write(0x00); //select register 3, X MSB register
		Wire.endTransmission();
		Wire.requestFrom(address, 6); //Read data from each axis, 2 registers per axis
		if(6 <= Wire.available())
		{
			xl = Wire.read() ; //X lsb
			x = (Wire.read()<< 8) + xl;
						
			yl = Wire.read() ; //y lsb
			y = (Wire.read()<< 8) + yl;
			
			zl = Wire.read() ; //z lsb
			z = (Wire.read()<< 8) + zl;
			
			switch (pin)
			{
				case GY273_X:
					*value = x;
					break;
				case GY273_Y:
					*value = y;
					break;
				case GY273_Z:
					*value = z;
					break;
				default:
					return GY273_INVALID_PIN;
			}
			return GY273_SUCCESS;
		}
		else
		{
			return GY273_DATA_NOT_AVAILABLE;
		}
	}
#endif