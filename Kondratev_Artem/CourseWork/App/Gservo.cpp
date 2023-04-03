//
// Created by user on 3/18/23.
//

#include "Gservo.h"


Gservo::Gservo(uint8_t _id) {
    id = _id;
    goal = 0;
    angle = 0;
    speed = 0;
    torque = 0;
    is_moving = 0;
}


uint8_t Gservo::getId() const {
    return id;
}


uint16_t Gservo::getGoal() const {
    return goal;
}


uint16_t Gservo::getAngle() const {
    return angle;
}


uint16_t Gservo::getSpeed() const {
    return speed;
}


uint16_t Gservo::getTorque() const {
    return torque;
}


uint16_t Gservo::getIsMoving() const {
    return is_moving;
}


uint16_t Gservo::getX() const {
    return x;
}


uint16_t Gservo::getY() const {
    return y;
}


uint16_t Gservo::getZ() const {
    return z;
}


void Gservo::setGoal(uint8_t _goal1, uint8_t _goal2) {
    goal = _goal1 * 100 + _goal2;
}


void Gservo::setAngle(uint8_t _angle1, uint8_t _angle2) {
    angle = _angle1 * 100 + _angle2;
}


void Gservo::setSpeed(uint8_t _speed1, uint8_t _speed2) {
    speed = _speed1 * 100 + _speed2;
}


void Gservo::setTorque(uint8_t _torque1, uint8_t _torque2) {
    torque = _torque1 * 100 + _torque2;
}


void Gservo::setIsMoving(uint8_t _is_moving1) {
    is_moving = _is_moving1;
}


void Gservo::setX(uint8_t _x1, uint8_t _x2) {
    x = _x1 * 100 + _x2;
}


void Gservo::setY(uint8_t _y1, uint8_t _y2) {
    y = _y1 * 100 + _y2;
}


void Gservo::setZ(uint8_t _z1, uint8_t _z2) {
    z = _z1 * 100 + _z2;
}


void Gservo::setGoal(uint16_t _goal) {
    goal = _goal;
}


void Gservo::setAngle(uint16_t _angle) {
    angle = _angle;
}


void Gservo::setSpeed(uint16_t _speed) {
    speed = _speed;
}


void Gservo::setTorque(uint16_t _torque) {
    torque = _torque;
}


void Gservo::setX(uint16_t _x) {
    x = _x;
}


void Gservo::setY(uint16_t _y) {
    y = _y;
}


void Gservo::setZ(uint16_t _z) {
    z = _z;
}
