// pin 5 & pin 6 of the arduino are for left motor and pin 7 & pin 8 are for the right motor.
// motor driver l293d is used here
// EN-A = pin 9 & EN-B = pin 10 must be kept in "HIGH" state
// For communicating with MPU module I2C protocol is used


int a1=5;
int a2=6; 
int b1=7;
int b2=8;
int ENA=9;
int ENB=10;
int INT=2;

#include<Wire.h>
const int MPU_addr=0x68;  // I2C address of the MPU-6050
const int MPU_PWR_MGMT_1=0x6B; // PWR_MGMT_1 register
int16_t AcX,AcY,AcZ,Tmp,GyX,GyY,GyZ;

void setup(){
initMPU6050();
Serial.begin(9600);
pinMode(a1,OUTPUT);
pinMode(a2,OUTPUT);
pinMode(b1,OUTPUT);
pinMode(b2,OUTPUT);
pinMode(ENA,OUTPUT);
pinMode(ENB,OUTPUT);
digitalWrite(ENA,HIGH);
digitalWrite(ENB,HIGH);
  
}
void loop(){
  readMPU6050();
// variables AcX and AcY give you accelero readings here !!
Serial.println("X axis -");
Serial.println(AcX);
Serial.println("Y axis -");
Serial.println(AcY);
  delay(333);
}

void initMPU6050(){
  Wire.begin();
  Wire.beginTransmission(MPU_addr);
  Wire.write(MPU_PWR_MGMT_1);  
  Wire.write(0);     // set to zero (wakes up the MPU-6050)
  Wire.endTransmission(true);
}

void readMPU6050(){
  Wire.beginTransmission(MPU_addr);
  Wire.write(0x3B);  // starting with register 0x3B (ACCEL_XOUT_H)
  Wire.endTransmission(false);
  Wire.requestFrom(MPU_addr,14,true);  // request a total of 14 registers
  AcX=Wire.read()<<8|Wire.read();  // 0x3B (ACCEL_XOUT_H) & 0x3C (ACCEL_XOUT_L)    
  AcY=Wire.read()<<8|Wire.read();  // 0x3D (ACCEL_YOUT_H) & 0x3E (ACCEL_YOUT_L)
  AcZ=Wire.read()<<8|Wire.read();  // 0x3F (ACCEL_ZOUT_H) & 0x40 (ACCEL_ZOUT_L)
  Tmp=Wire.read()<<8|Wire.read();  // 0x41 (TEMP_OUT_H) & 0x42 (TEMP_OUT_L)
  Tmp=(Tmp/340.00)+36.53;
  GyX=Wire.read()<<8|Wire.read();  // 0x43 (GYRO_XOUT_H) & 0x44 (GYRO_XOUT_L)
  GyY=Wire.read()<<8|Wire.read();  // 0x45 (GYRO_YOUT_H) & 0x46 (GYRO_YOUT_L)
  GyZ=Wire.read()<<8|Wire.read();  // 0x47 (GYRO_ZOUT_H) & 0x48 (GYRO_ZOUT_L)

if(AcX>5000)
right();
else if(AcX<-8000)
left();
else if(AcY>4000)
forward();
else if(AcY<-9000)
backward();
else if(AcX<1000)
stopbot();
}






void forward()
{
  
   digitalWrite(a1,HIGH);
  digitalWrite(a2,LOW);
  digitalWrite(b1,HIGH);
  digitalWrite(b2,LOW);

  
}

void backward()
{
  
   digitalWrite(a1,LOW);
  digitalWrite(a2,HIGH);
  digitalWrite(b1,LOW);
  digitalWrite(b2,HIGH);

 }

void right()
{
  
  
  digitalWrite(a1,HIGH);
  digitalWrite(a2,LOW);
  digitalWrite(b1,LOW);
  digitalWrite(b2,HIGH);

  
  
  }

void left()
{
  
  
   digitalWrite(a1,LOW);
  digitalWrite(a2,HIGH);
  digitalWrite(b1,HIGH);
  digitalWrite(b2,LOW);
  
  
 }
void stopbot()
{
  
 
   digitalWrite(a1,LOW);
  digitalWrite(a2,LOW);
  digitalWrite(b1,LOW);
  digitalWrite(b2,LOW);
   
  
  
  
  }
