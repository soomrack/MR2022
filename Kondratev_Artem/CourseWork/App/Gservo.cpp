//
// Created by user on 3/18/23.
//

#include "Gservo.h"


Gservo::Gservo(uint8_t _id) {
    id = _id;
    goal = 0;
    angle = 0;
    speed = 0;
    boost = 0;
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


uint16_t Gservo::getBoost() const {
    return boost;
}


uint16_t Gservo::getTorque() const {
    return torque;
}


uint16_t Gservo::getIsMoving() const {
    return is_moving;
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


void Gservo::setBoost(uint8_t _boost1, uint8_t _boost2) {
    boost = _boost1 * 100 + _boost2;
}


void Gservo::setTorque(uint8_t _torque1, uint8_t _torque2) {
    torque = _torque1 * 100 + _torque2;
}


void Gservo::setIsMoving(uint8_t _is_moving1) {
    is_moving = _is_moving1;
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


void Gservo::setBoost(uint16_t _boost) {
    boost = _boost;
}


void Gservo::setTorque(uint16_t _torque) {
    torque = _torque;
}
