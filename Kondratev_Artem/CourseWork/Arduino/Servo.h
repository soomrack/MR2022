
#ifndef Servo_h
#define Servo_h


#include <stdint.h>
#include <string>
#include <DynamixelWorkbench.h>
#include "Config.h"


DynamixelWorkbench servos;


class Servo {
private:
    uint8_t DXL_ID;
    uint16_t min_angle;
    uint16_t max_angle;
    uint16_t angle;
    bool inv;
    uint16_t new_angle;
    uint16_t speed;
    uint16_t boost;
public:
    Servo(uint8_t _DXL_ID, uint16_t _min_angle, uint16_t _max_angle, bool _inv = 0);
    static void init();
    static void pingServos();
    static void getStartPosition();

    void setAngle(uint16_t _angle);
    static void setAngle(uint16_t _angle, uint8_t _DXL_ID);
    
    uint8_t getDXL_ID();
    static bool talk(uint16_t _angle);

    static uint16_t checkGamma(uint16_t alpha, uint16_t beta);
    static void test(uint16_t msg);

    void setSpeed(uint16_t _speed);
    void setBoost(uint16_t _boost);
    void setMoveMode(uint16_t _speed, uint16_t _boost);

    int32_t readRegister(char* command);
    uint16_t getAngle();
    uint16_t getGoal();
    int32_t getLoad();
    int32_t isMoving();
    uint16_t getSpeed();
    uint16_t getBoost();

    void Calibration_min();
    void Calibration_max();
    static void Calibration_setup();
};


Servo servo1(DXL_ID1, SERVO1_MIN_ANGLE, SERVO1_MAX_ANGLE, 0);
Servo servo2(DXL_ID2, SERVO2_MIN_ANGLE, SERVO2_MAX_ANGLE, 0);
Servo servo3(DXL_ID3, SERVO3_MIN_ANGLE, SERVO3_MAX_ANGLE, 1);
Servo servo4(DXL_ID4, SERVO4_MIN_ANGLE, SERVO4_MAX_ANGLE, 1);


Servo::Servo(uint8_t _DXL_ID, uint16_t _min_angle, uint16_t _max_angle, bool _inv) {
    DXL_ID = _DXL_ID;
    min_angle = _min_angle;
    max_angle = _max_angle;
    angle = 0;
    new_angle = 0;
    inv = _inv;
}


void Servo::init() {
    servos.init(DEVICE_NAME, SERVO_BAUDRATE);
}


void Servo::pingServos() {
    servos.ping(DXL_ID1, 0, 0);
    servos.ping(DXL_ID2, 0, 0);
    servos.ping(DXL_ID3, 0, 0);
    servos.ping(DXL_ID4, 0, 0);
}


uint16_t reformatAngle(uint16_t angle, uint16_t min_angle, uint16_t max_angle) {
    if (angle < min_angle) {
        return min_angle;
    }
    if (angle > max_angle) {
        return max_angle;
    }
    return angle;
}


void Servo::setAngle(uint16_t _angle) {
    if (inv == 1) {
        _angle = 1023 - _angle;
    }
    if (_angle < min_angle) {
        angle = min_angle;
        servos.goalPosition(DXL_ID, angle);
        if (inv == 1) {
            angle = 1023 - angle;
        }
        return;
    }
    if (_angle > max_angle) {
        angle = max_angle;
        servos.goalPosition(DXL_ID, angle);
        if (inv == 1) {
            angle = 1023 - angle;
        }
        return;
    }
    angle = _angle;
    servos.goalPosition(DXL_ID, angle);
    if (inv == 1) {
        angle = 1023 - angle;
    }
}


void Servo::setAngle(uint16_t _angle, uint8_t _DXL_ID) {
    if (_DXL_ID == 1) {
        servo1.setAngle(_angle);
    }
    if (_DXL_ID == 2) {
        servo2.setAngle(_angle);
    }
    if (_DXL_ID == 3) {
        servo3.setAngle(_angle);
    }
    if (_DXL_ID == 4) {
        servo4.setAngle(_angle);
    }
}


Servo *findServo(uint8_t id) {
    if (id == 1) {
        return &servo1;
    }
    if (id == 2) {
        return &servo2;
    }
    if (id == 3) {
        return &servo3;
    }
    if (id == 4) {
        return &servo4;
    }
}


void Servo::getStartPosition() {
    servo1.setAngle(512);
    servo2.setAngle(512);
    servo3.setAngle(512);
    servo4.setAngle(512);
    delay(5000);
}


uint8_t Servo::getDXL_ID() {
    return DXL_ID;
}


bool Servo::talk(uint16_t msg) {
    if (msg < 10000) {
        return false;
    }
    uint8_t id = msg / 10000;
    Servo *servo = findServo(id);

    uint16_t msg_angle = msg % 10000;
    if (id == 2) {
        servo2.new_angle = reformatAngle(msg_angle, servo2.min_angle, servo2.max_angle);
        servo3.new_angle = servo3.angle + checkGamma(servo2.new_angle, servo3.angle);
        servo3.setAngle(servo3.new_angle);
        servo2.setAngle(servo2.new_angle);
        return true;
    }
    if (id == 3) {
        servo3.new_angle = msg_angle + checkGamma(servo2.angle, msg_angle);
        servo3.setAngle(servo3.new_angle);
        return true;
    }
    servo->setAngle(msg_angle);
    return true;
}


uint16_t Servo::checkGamma(uint16_t alpha, uint16_t beta) {
    beta = beta - BETA0;
    int16_t gamma = 1023 - alpha + beta;
    if (gamma < MIN_GAMMA) {
        return MIN_GAMMA - gamma;
    }/*
    if (gamma > MAX_GAMMA) {
        return MAX_GAMMA - gamma;
    }*/
    return 0;
}


void Servo::setSpeed(uint16_t _speed) {
    speed = _speed;
    servos.jointMode(DXL_ID, speed, boost);
}


void Servo::setBoost(uint16_t _boost) {
    boost = _boost;
    servos.jointMode(DXL_ID, speed, boost);
}


void Servo::setMoveMode(uint16_t _speed, uint16_t _boost) {
    speed = _speed;
    boost = _boost;
    servos.jointMode(DXL_ID, speed, boost);
}


int32_t Servo::readRegister(char* command) {
    int32_t data;
    servos.readRegister(DXL_ID, command, &data);
    return data;
}


int32_t Servo::getLoad(){
    int32_t data;
    servos.readRegister(DXL_ID, "Present_Load", &data);
    if (data > 1023) data -= 1023;
    return data;
}


int32_t Servo::isMoving(){
    int32_t data;
    servos.readRegister(DXL_ID, "Moving", &data);
    return data;
}


uint16_t Servo::getGoal() {
    return angle;
}


uint16_t Servo::getAngle() {
    int32_t data;
    servos.readRegister(DXL_ID, "Present_Position", &data);
    return data;
}


uint16_t Servo::getSpeed() {
    return speed;
}


uint16_t Servo::getBoost() {
    return boost;
}


void Servo::Calibration_max(){
  uint16_t servo_max_angle = 512;
  setSpeed(80);

    while(true){
      // Serial.println(getLoad());  // DEBUG
      // Serial.println(servo_max_angle);
      // Serial.println(getAngle());
      // Serial.println(" ");

      setAngle(servo_max_angle, DXL_ID);
      delay(100);
      if(isMoving() == 0) servo_max_angle += 50;
      else if (getLoad() > 750) {
        servo_max_angle -= 50;
        setAngle(servo_max_angle, DXL_ID);
        break;
      }
    }

    max_angle = servo_max_angle;

    Serial.println(" ");
    Serial.println(servo_max_angle);
}


void Servo::Calibration_min(){
  uint16_t servo_min_angle = 512;
  setSpeed(80);
    while(true){
      // Serial.println(getLoad());  // DEBUG
      // Serial.println(servo_min_angle);
      // Serial.println(getAngle());
      // Serial.println(" ");

      setAngle(servo_min_angle, DXL_ID);
      delay(100);
      if(isMoving() == 0) servo_min_angle -= 50;
      else if (getLoad() > 750) {
        servo_min_angle += 50;
        setAngle(servo_min_angle, DXL_ID);
        break;
      }
    }

    min_angle = servo_min_angle;

    Serial.println(" ");
    Serial.println(servo_min_angle);
}


void Servo::Calibration_setup() {
  servo2.Calibration_max();
  servo2.Calibration_min();
  servo2.setAngle(servo2.min_angle + (servo2.max_angle - servo2.min_angle) / 2);
  delay(2000);
  servo3.Calibration_max();
  servo3.Calibration_min();
}


#endif
