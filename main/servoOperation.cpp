#include "servoOperation.h"
servoOperation::servoOperation(){
  //サーボ初期設定
  //servo　初期PIN設定
  servoRudder.attach(3);
  servoElevator.attach(5);
  servoRudder.writeMicroseconds(mid_servoRud);
  servoElevator.writeMicroseconds(mid_servoElevator);
}

void servoOperation::servoWrite(){
  this->Rud_val = constrain(calc_miliseconds(LEFT_x_value, mid_servoRud, sensitivity_Rud),1100,1900);
  this->Ele_val = constrain(calc_miliseconds(RIGHT_y_value, mid_servoElevator, sensitivity_Ele),1200,1830);

  servoRudder.writeMicroseconds(Rud_val);
  servoElevator.writeMicroseconds(Ele_val);
}

void servoOperation::serEvent(float *cmds) {
  LEFT_x_value = cmds[0];
  LEFT_y_value = cmds[1];
  RIGHT_x_value = cmds[2];
  RIGHT_y_value = cmds[3];
}

int servoOperation::calc_miliseconds(float rawvalue, int midValue, int sensitivity){
  return midValue + int(sensitivity * rawvalue);
}

int servoOperation::constrain(int value, int min, int max){
  if (value < min) {
      return min;
  } else if (value > max) {
    return max;
  } else {
    return value;
  }
}

