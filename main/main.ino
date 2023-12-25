#include <Wire.h>
#include <Servo.h>

String cmds[4] = {"\0"}; // 分割された文字列を格納する配列 

//ジョイコン値格納場所
float LEFT_x_value = 0;
float LEFT_y_value = 0;
float RIGHT_x_value = 0;
float RIGHT_y_value = 0;

//miliseconds格納場所
int Rud_val = 1500;
int Ele_val = 1500;

//サーボ初期設定
Servo servoRudder;
Servo servoElevator;
float mid_servoRud = 1570;
float mid_servoElevator = 1430;

//スティックの感度調整(0~400)
 int sensitivity_Rud = 330;
 int sensitivity_Ele = 330;

void setup()
{
  Wire.begin();
  Serial.begin(9600);
  //auto sensor_BMX055 = Sensor_BMX055();

  //servo　初期PIN設定
  servoRudder.attach(3);
  servoElevator.attach(5);
  servoRudder.writeMicroseconds(mid_servoRud);
  servoElevator.writeMicroseconds(mid_servoElevator);
}

void loop()
{
  Rud_val = calc_miliseconds(LEFT_x_value, mid_servoRud, sensitivity_Rud);
  Ele_val = constrain(calc_miliseconds(RIGHT_y_value, mid_servoElevator, sensitivity_Ele),1200,1830);
  servoRudder.writeMicroseconds(Rud_val);
  servoElevator.writeMicroseconds(Ele_val);
  Serial.print(Rud_val);
  Serial.print(",");
  Serial.println(Ele_val);
  if(Serial.available() > 0) {
    serEvent();
  }
}

void serEvent(){
  //割り込み処理のはず
  String input = Serial.readStringUntil('\n');
  //Serial.println(input);
  int data_num = split(input, ',', cmds);
  //Serial.println(cmds[0]);
  LEFT_x_value = cmds[0].toFloat();
  LEFT_y_value = cmds[1].toFloat();
  RIGHT_x_value = cmds[2].toFloat();
  RIGHT_y_value = cmds[3].toFloat();
  
  // cmds 配列の中身を空にする
  for (int i = 0; i < 4; ++i) {
    cmds[i] = "";
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

//caluculation of miliseconds(from -1~1 to 1100~1900)
int calc_miliseconds(float rawvalue, int midValue, int sensitivity){
  int ms_temp = midValue + int(sensitivity * rawvalue);
  if (ms_temp >= 1900) {
    return 1900;
  } else {
    if (ms_temp <= 1100) {
      return 1100;
    } else {
      return ms_temp;
    }
  }
}
  
//=====================================================================================//
