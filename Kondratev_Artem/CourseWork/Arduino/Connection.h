
#ifndef Connection_h
#define Connection_h


#include "Config.h"
#include "Servo.h"


uint8_t id = 0;
uint8_t command = 0;
uint16_t value1 = 0;
uint16_t value2 = 0;
uint16_t value = 0;
uint16_t checksum = 0;

uint16_t goal = 0;
uint16_t angle = 0;
uint16_t speed = 0;
uint16_t boost = 0;
uint16_t torque = 0;
uint16_t is_moving = 0;


class Connection {
public:
    static uint16_t calc();
    static void setData(Servo servo);
    static void setData();
    static void getData();
    static void findCommand();
};


uint16_t Connection::calc() {
    return (char(id) + char(command) + char(value1) + char(value2)) / 8;
}


void Connection::setData(Servo servo) {
    id = servo.getDXL_ID();
    goal = servo.getGoal();
    angle = servo.getAngle();
    speed = servo.getSpeed();
    boost = servo.getBoost();
    torque = servo.getLoad();
    is_moving = servo.isMoving();
    
    Serial.print(char(64));
    Serial.print(char(64));
    
    Serial.print(char(id));
    Serial.print(char(goal));
    Serial.print(char(angle));
    Serial.print(char(speed));
    Serial.print(char(boost));
    Serial.print(char(torque));
    Serial.print(char(is_moving));

    Serial.print(char(calc()));
}


void Connection::setData() {
    //add change flag
    setData(servo1);
    //setData(servo2);
    //setData(servo3);
    //setData(servo4);
}


void Connection::getData() {
  if (Serial.available() >= 7) {
      byte start1 = Serial.read();
      byte start2 = Serial.read();
      if (start1 + start2 == 128) {
          id = Serial.read();
          command = Serial.read();
          value1 = Serial.read();
          value2 = Serial.read();
          checksum = Serial.read();
      if (calc() == checksum) {
          findCommand();
          setData();
      }
    }
  }
}


void Connection::findCommand() {
    value = value1 * 100 + value2;
    if (command == 0) {
        
    }
    if (command == 1) {
        Servo::setAngle(value, id);
    }
}


#endif
