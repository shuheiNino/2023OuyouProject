#ifndef BNX055Class_h
#define BNX055Class_h

class BMX055Class{
  private:
    // センサーの値を保存するグローバル変数
    float xAccl;
    float yAccl;
    float zAccl;
    float xGyro;
    float yGyro;
    float zGyro;
    int   xMag;
    int   yMag;
    int   zMag;
    unsigned char Addr_Accl, Addr_Gyro, Addr_Mag;

  public:
    BMX055Class(unsigned char Addr_Accl_from, unsigned char Addr_Gyro_from, unsigned char Addr_Mag_from); //constructor

    void begin();
    void BMX055_Accl(); //get Accelaration
    void BMX055_Gyro(); //get Gyro
    void BMX055_Mag();  //get Mag

    float getXAccl(){
      return xAccl;
    };
    float getYAccl(){
      return yAccl;
    };
    float getZAccl(){
      return zAccl;
    };
    float getXGyro(){
      return xGyro;
    };
    float getYGyro(){
      return yGyro;
    };
    float getZGyro(){
      return zGyro;
    };
    float getXMag(){
      return xMag;
    };
    float getYMag(){
      return yMag;
    };
    float getZMag(){
      return zMag;
    };

};
#endif