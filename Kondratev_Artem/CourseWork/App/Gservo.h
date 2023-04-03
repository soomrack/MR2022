//
// Created by user on 3/18/23.
//

#ifndef MANIPULATOR_GSERVO_H
#define MANIPULATOR_GSERVO_H


#include <cstdint>


class Gservo {
private:
    uint8_t id;
    uint16_t goal;
    uint16_t angle;
    uint16_t speed;
    uint16_t torque;
    uint8_t is_moving;
    uint16_t x;
    uint16_t y;
    uint16_t z;

public:
    explicit Gservo(uint8_t _id);

    uint8_t getId() const;
    uint16_t getGoal() const;
    uint16_t getAngle() const;
    uint16_t getSpeed() const;
    uint16_t getTorque() const;
    uint16_t getIsMoving() const;
    uint16_t getX() const;
    uint16_t getY() const;
    uint16_t getZ() const;

    void setGoal(uint8_t _goal1, uint8_t _goal2);
    void setAngle(uint8_t _angle1, uint8_t _angle2);
    void setSpeed(uint8_t _speed1, uint8_t _speed2);
    void setTorque(uint8_t _torque1, uint8_t _torque2);
    void setIsMoving(uint8_t _is_moving);
    void setX(uint8_t _x1, uint8_t _x2);
    void setY(uint8_t _y1, uint8_t _y2);
    void setZ(uint8_t _z1, uint8_t _z2);

    void setGoal(uint16_t _goal);
    void setAngle(uint16_t _angle);
    void setSpeed(uint16_t _speed);
    void setTorque(uint16_t _torque);
    void setX(uint16_t _x);
    void setY(uint16_t _y);
    void setZ(uint16_t _z);
};


inline Gservo gservo1(1);
inline Gservo gservo2(2);
inline Gservo gservo3(3);
inline Gservo gservo4(4);

inline Gservo internal_servo1(1);
inline Gservo internal_servo2(2);
inline Gservo internal_servo3(3);
inline Gservo internal_servo4(4);


#endif //MANIPULATOR_GSERVO_H
