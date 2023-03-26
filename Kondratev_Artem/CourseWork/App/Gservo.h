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
    uint16_t boost;
    uint16_t torque;
    uint8_t is_moving;

public:
    explicit Gservo(uint8_t _id);

    uint8_t getId() const;
    uint16_t getGoal() const;
    uint16_t getAngle() const;
    uint16_t getSpeed() const;
    uint16_t getBoost() const;
    uint16_t getTorque() const;
    uint16_t getIsMoving() const;

    void setGoal(uint8_t _goal1, uint8_t _goal2);
    void setAngle(uint8_t _angle1, uint8_t _angle2);
    void setSpeed(uint8_t _speed1, uint8_t _speed2);
    void setBoost(uint8_t _boost1, uint8_t _boost2);
    void setTorque(uint8_t _torque1, uint8_t _torque2);
    void setIsMoving(uint8_t _is_moving);

    void setGoal(uint16_t _goal);
    void setAngle(uint16_t _angle);
    void setSpeed(uint16_t _speed);
    void setBoost(uint16_t _boost);
    void setTorque(uint16_t _torque);
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
