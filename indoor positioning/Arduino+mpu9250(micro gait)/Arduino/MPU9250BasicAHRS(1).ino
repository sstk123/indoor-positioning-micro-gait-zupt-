#include "MPU9250.h"

MPU9250 myIMU;

void setup()
{
  Wire.begin();
  TWBR = 12;  // 400 kbit/sec I2C speed
  Serial.begin(115200);
  byte c = myIMU.readByte(MPU9250_ADDRESS, WHO_AM_I_MPU9250);
  if (c == 0x71) // WHO_AM_I should always be 0x68
  {
    myIMU.MPU9250SelfTest(myIMU.SelfTest);
    myIMU.calibrateMPU9250(myIMU.gyroBias, myIMU.accelBias);
    myIMU.initMPU9250();
  } 
  else
  {
    Serial.print("Could not connect to MPU9250: 0x");
    Serial.println(c, HEX);
  }
}

void loop()
{
   if (myIMU.readByte(MPU9250_ADDRESS, INT_STATUS) & 0x01)
   {
    //读取加速度数据
	//Read acceleration data
    myIMU.readAccelData(myIMU.accelCount);  // Read the x/y/z adc values
    myIMU.getAres();
    //数据换算
	// data conversion
    myIMU.ax = (float)myIMU.accelCount[0]*myIMU.aRes; 
    myIMU.ay = (float)myIMU.accelCount[1]*myIMU.aRes; 
    myIMU.az = (float)myIMU.accelCount[2]*myIMU.aRes; 
    //读取陀螺仪数据
	//Reading gyroscope data
    myIMU.readGyroData(myIMU.gyroCount);  // Read the x/y/z adc values
    myIMU.getGres();
    //数据换算
   // data conversion
    myIMU.gx = (float)myIMU.gyroCount[0]*myIMU.gRes;
    myIMU.gy = (float)myIMU.gyroCount[1]*myIMU.gRes;
    myIMU.gz = (float)myIMU.gyroCount[2]*myIMU.gRes;
    //时间更新update time
    myIMU.updateTime();
    
    //数据输出
	//data output
    Serial.print(myIMU.lastUpdate);
    Serial.print(" "); 
       
    Serial.print(myIMU.ax);
    Serial.print(" "); 
    Serial.print(myIMU.ay);
    Serial.print(" ");
    Serial.print(myIMU.az);
    Serial.print(" "); 
        
    Serial.print(myIMU.gx, 3);
    Serial.print(" "); 
    Serial.print(myIMU.gy, 3);
    Serial.print(" "); 
    Serial.println(myIMU.gz, 3);
    
    /*
    //采样率 sampling rate 
    Serial.print("rate = ");
    Serial.print((float)myIMU.sumCount/myIMU.sum, 2);
    Serial.println(" Hz");

    myIMU.sumCount = 0;
    myIMU.sum = 0;
    */
   }
}
