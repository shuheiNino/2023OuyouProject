//================================================================//
//  AE-BMX055             Arduino UNO                             //
//    VCC                    +5V                                  //
//    GND                    GND                                  //
//    SDA                    A4(SDA)                              //
//    SCL                    A5(SCL)                              //
//                                                                //
//   (JP4,JP5,JP6はショートした状態)                                //
//   http://akizukidenshi.com/catalog/g/gK-13010/                 //
//================================================================//

#include<Wire.h>

#include <MadgwickAHRS.h>

#include "MS5837.h"

#include "BMX055Class.h"

// BMX055 加速度センサのI2Cアドレス  
#define Addr_Accl 0x19  // (JP1,JP2,JP3 = Openの時)
// BMX055 ジャイロセンサのI2Cアドレス
#define Addr_Gyro 0x69  // (JP1,JP2,JP3 = Openの時)
// BMX055 磁気センサのI2Cアドレス
#define Addr_Mag 0x13   // (JP1,JP2,JP3 = Openの時)

// センサーの値を保存するグローバル変数
float xAccl = 0.00;
float yAccl = 0.00;
float zAccl = 0.00;
float xGyro = 0.00;
float yGyro = 0.00;
float zGyro = 0.00;
int   xMag  = 0;
int   yMag  = 0;
int   zMag  = 0;
float  roll, pitch, heading, q0, q1, q2, q3;
Madgwick filter;
MS5837 sensor;
BMX055Class BMX055(Addr_Accl, Addr_Gyro, Addr_Mag);
char buff[50];

void setup()
{
 
  // Wire(Arduino-I2C)の初期化
  Wire.begin();
  // デバッグ用シリアル通信は9600bps
  Serial.begin(9600);
  //BMX055 初期化
  BMX055.begin();
  //Madgwick filterの初期化
  filter.begin(10);

  while (!sensor.init()) {
    Serial.println("Init failed!");
    Serial.println("Are SDA/SCL connected correctly?");
    Serial.println("Blue Robotics Bar30: White=SDA, Green=SCL");
    Serial.println("\n\n\n");
    delay(5000);
  }

  sensor.setModel(MS5837::MS5837_30BA);
  sensor.setFluidDensity(997); // kg/m^3 (freshwater, 1029 for seawater)
}

void loop()
{
  Serial.println("--------------------------------------"); 

  //BMX055 加速度の読み取り
  BMX055.BMX055_Accl();
  
  //BMX055 ジャイロの読み取り
  BMX055.BMX055_Gyro();
  
  //BMX055 磁気の読み取り
  BMX055.BMX055_Mag();

  xAccl = BMX055.getXAccl();
  yAccl = BMX055.getYAccl();
  zAccl = BMX055.getZAccl();
  xGyro = BMX055.getXGyro();
  yGyro = BMX055.getYGyro();
  zGyro = BMX055.getZGyro();
  xMag = BMX055.getXMag();
  yMag = BMX055.getYMag();
  zMag = BMX055.getZMag();

  filter.updateIMU(xGyro, yGyro, zGyro, xAccl, yAccl, zAccl);
  /*
  Serial.print(xAccl);
  Serial.print(",");
  Serial.print(yAccl);
  Serial.print(",");
  Serial.print(zAccl);
  Serial.print(",");
  Serial.print(xGyro);
  Serial.print(",");
  Serial.print(yGyro);
  Serial.print(",");
  Serial.print(zGyro);
  Serial.print(",");
  */
  // print the heading, pitch and roll
  roll = filter.getRoll();
  pitch = filter.getPitch();
  heading = filter.getYaw();
  q0 = filter.getQ0();
  q1 = filter.getQ1();
  q2 = filter.getQ2();
  q3 = filter.getQ3();
  /*
  Serial.print(heading);
  Serial.print(",");
  Serial.print(pitch);
  Serial.print(",");
  Serial.print(roll);
  Serial.print(",");
  Serial.print(q0);
  Serial.print(",");
  Serial.print(q1);
  Serial.print(",");
  Serial.print(q2);
  Serial.print(",");
  Serial.print(q3);
  Serial.print(",");
  */
  sensor.read();
  /*
  Serial.print(sensor.pressure()); 
  Serial.print(",");
  Serial.print(sensor.temperature()); 
  Serial.print(",");
  Serial.print(sensor.depth()); 
  Serial.print(",");
  Serial.println(sensor.altitude()); 
  */
  sprintf(buff," %f, %f, %f, %f\n", heading, pitch, roll, sensor.depth());
  Serial.print(buff);

  delay(100);
}