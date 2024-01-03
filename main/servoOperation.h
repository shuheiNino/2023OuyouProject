#ifndef servoOperation_h
#define servoOperation_h
#include <string>
#include <Servo.h>

class servoOperation{
  //member variable
  private:
    //サーボインスタンス
    Servo servoRudder;
    Servo servoElevator;

    //ジョイコンの値格納場所
    float LEFT_x_value = 0;
    float LEFT_y_value = 0;
    float RIGHT_x_value = 0;
    float RIGHT_y_value = 0;

    //miliseconds格納場所
    int Rud_val = 1500;
    int Ele_val = 1500;

    //サーボモータの中心点設定
    int mid_servoRud = 1570;
    int mid_servoElevator = 1430;

    //スティックの感度調整(0~400)
    int sensitivity_Rud = 330;
    int sensitivity_Ele = 330;

  public:

  //member function
  private:
    int calc_miliseconds(float rawvalue, int midValue, int sensitivity);
    int constrain(int value, int min, int max);

  public:
    //constructer
    servoOperation(); 
    void serEvent(float *cmds);
    void servoWrite();

    //access function
    int Rud_value(){
      return Rud_val;
    };
    int Ele_value(){
      return Ele_val;
    };
};

#endif 