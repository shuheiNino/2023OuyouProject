#include <Wire.h>
#include <Servo.h>
#include "servoOperation.h"

#include <MadgwickAHRS.h>

#include "MS5837.h"

#include "BMX055Class.h"

String cmds_string[4] = {"\0"}; // 分割された文字列を格納する配列
float cmds_float[4] = {0};
servoOperation servoOperation1;

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

unsigned long previousMillis = 0;
const long interval = 1000;  // 1秒の間隔
char buff[50];

void setup()
{
  Wire.begin();
  Serial.begin(9600);
  //auto sensor_BMX055 = Sensor_BMX055();

  servoOperation1.servoWrite();
}

void loop()
{
  unsigned long currentMillis = millis();
  //BMX055からroll,pitch,headingの出力
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

  //bar02深度センサ読み取り
  sensor.read();

  //servo operation
  servoOperation1.servoWrite();

  // 1秒ごとに処理を実行
  if (currentMillis - previousMillis >= interval) {
    // タイマーリセット
    previousMillis = currentMillis;
    //serial送信
    sprintf(buff," %f, %f, %f, %f, %i, %i\n", heading, pitch, roll, sensor.depth(), servoOperation1.Rud_value(), servoOperation1.Ele_value());
    Serial.print(buff);
  }

  //serial受信
  if(Serial.available() > 0) {
    serEvent();
  }
}

void serEvent(){
  //割り込み処理のはず
  String input = Serial.readStringUntil('\n');
  int data_num = split(input, ',', cmds_string);

  //Serial.println(cmds[0]);
  cmds_float[0] = cmds_string[0].toFloat();
  cmds_float[1] = cmds_string[1].toFloat();
  cmds_float[2] = cmds_string[2].toFloat();
  cmds_float[3] = cmds_string[3].toFloat();

  servoOperation1.serEvent(cmds_float);
  
  // cmds 配列の中身を空にする
  for (int i = 0; i < 4; ++i) {
    cmds_string[i] = "";
  }
}


//split関数、コンマで値を分割
int split(String data, char delimiter, String *dst){
    int index = 0; 
    int datalength = data.length();
    
    for (int i = 0; i < datalength; i++) {
        char tmp = data.charAt(i);
        if ( tmp == delimiter ) {
            index++;
        }
        else dst[index] += tmp;
    }
    
    return (index + 1);
}

  
//=====================================================================================//
