
#ifndef Servo_h
#define Servo_h


#include <stdint.h>
#include <string>
#include <DynamixelWorkbench.h>
#include "Config.h"
#include "print.h"


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

public:
    Servo(uint8_t _DXL_ID, uint16_t _min_angle, uint16_t _max_angle, bool _inv = 0);

    static void init();
    static void pingServos();
    static void getStartPosition();
    uint16_t reformatAngle(uint16_t _angle);
    static Servo* findServo(uint8_t id);

    void setAngle(uint16_t _angle);
    static void setAngle(uint16_t _angle, uint8_t _DXL_ID);
    void setMaxAngle(uint16_t _max_angle);
    void setMinAngle(uint16_t _min_angle);

    void setSpeed(uint16_t _speed);
    static void setSpeed(uint16_t _speed, uint8_t _DXL_ID);

    void setTorque(bool status);

    void setX(int32_t _x);
    void setY(int32_t _y);
    void setZ(int32_t _z);

    static void test(uint16_t msg);
    static bool talk(uint16_t _angle);

private:
    int32_t readRegister(char* command);

public:
    uint8_t getDXL_ID();

    uint16_t getAngle();
    uint16_t getMaxAngle();
    uint16_t getMinAngle();

    uint16_t getGoal();

    int32_t getLoad();

    int32_t isMoving();

    uint16_t getSpeed();

    static void toolPush();
    static void toolPop();

    void reload();
};


Servo servo1(DXL_ID1, SERVO1_MIN_ANGLE, SERVO1_MAX_ANGLE, 0);
Servo servo2(DXL_ID2, SERVO2_MIN_ANGLE, SERVO2_MAX_ANGLE, 0);
Servo servo3(DXL_ID3, SERVO3_MIN_ANGLE, SERVO3_MAX_ANGLE, 1);
Servo servo4(DXL_ID4, SERVO4_MIN_ANGLE, SERVO4_MAX_ANGLE, 1);


Servo::Servo(uint8_t _DXL_ID, uint16_t _min_angle, uint16_t _max_angle,
             bool _inv) {
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


void Servo::getStartPosition() {
    servo1.setAngle(SERVO1_START_POSITION);
    servo2.setAngle(SERVO2_START_POSITION);
    servo3.setAngle(SERVO3_START_POSITION);
    servo4.setAngle(SERVO4_START_POSITION);
    delay(3000);
}


uint16_t Servo::reformatAngle(uint16_t _angle) {
    if (_angle < min_angle) {
        return min_angle;
    }
    if (_angle > max_angle) {
        return max_angle;
    }
    return _angle;
}


Servo* Servo::findServo(uint8_t id) {
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


void Servo::setAngle(uint16_t _angle) {
    uint16_t _min_angle = min_angle;;
    uint16_t _max_angle = max_angle;

    if (inv == 1) {
        _angle = 1023 - _angle;        // 800 -> 223
        _max_angle = 1023 - min_angle; //  790 -> 633
        _min_angle = 1023 - max_angle; //  390 -> 233
    }
    if (_angle < _min_angle) {
        angle = _min_angle;
        servos.goalPosition(DXL_ID, angle);
        if (inv == 1) {
            angle = 1023 - angle;
        }
        return;
    }
    if (_angle > _max_angle) {
        angle = _max_angle;
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
    Servo* servo = findServo(_DXL_ID);
    servo->setAngle(_angle);
}


void Servo::setMaxAngle(uint16_t _max_angle) {
    max_angle = _max_angle;
}


void Servo::setMinAngle(uint16_t _min_angle) {
    min_angle = _min_angle;
}


void Servo::setSpeed(uint16_t _speed) {
    speed = _speed;
    servos.jointMode(DXL_ID, speed, DEFAULT_BOOST);
}


void Servo::setSpeed(uint16_t _speed, uint8_t _DXL_ID) {
    Servo* servo = findServo(_DXL_ID);
    servo->setSpeed(_speed);
}


void Servo::setTorque(bool status) {
    if (status == 1)
        servos.torqueOn(DXL_ID);
    if (status == 0)
        servos.torqueOff(DXL_ID);
}


void Servo::test(uint16_t msg) {

    uint16_t neutral_angle_2 = (servo2.max_angle + servo2.min_angle) / 2 - 20;
    uint16_t neutral_angle_3 = (servo3.max_angle + servo3.min_angle) / 2 + 20;

    uint16_t num2 = servo3.max_angle - neutral_angle_2;
    uint16_t num3 = neutral_angle_2 + servo3.min_angle;
    uint16_t num4 = neutral_angle_2 - servo3.min_angle;

    uint16_t angle_3 = 1023 - servo3.getAngle();
    uint16_t angle_2 = servo2.getAngle();

    uint8_t id = msg / 10000;
    uint16_t msg_angle = msg % 10000;

    if (id == 2) {

        uint8_t quart;
        uint16_t correct_angle_3;

        msg_angle = servo2.reformatAngle(msg_angle);

        if (angle_3 > neutral_angle_3) {
            if (msg_angle > neutral_angle_2)
                quart = 1; // Определяем четверть
            else
                quart = 2;
        } else {
            if (msg_angle <= neutral_angle_2)
                quart = 3;
            else
                quart = 4;
        }

        switch (quart) { // Действия для каждой четверти
            case 1:
                servo2.setAngle(msg_angle);
                break;

            case 2:
                correct_angle_3 = num2 + msg_angle;
                if (angle_3 > correct_angle_3)
                    servo3.setAngle(correct_angle_3);
                servo2.setAngle(msg_angle);
                break;

            case 3:
                correct_angle_3 = num3 - msg_angle;
                if (angle_3 < correct_angle_3 && msg_angle < 320)
                    servo3.setAngle(correct_angle_3 + (320 - msg_angle) / 6);
                servo2.setAngle(msg_angle);
                break;

            case 4:
                correct_angle_3 = msg_angle - num4;
                if (angle_3 < correct_angle_3)
                    servo3.setAngle(correct_angle_3);
                servo2.setAngle(msg_angle);
                break;

            default:
                servo2.setAngle(msg_angle);
                break;
        }
        return;
    }

    if (id == 3) {

        uint8_t place;
        uint16_t correct_angle_2;

        msg_angle = servo3.reformatAngle(msg_angle);

        if (msg_angle < neutral_angle_3 - 200) {
            if (angle_2 > neutral_angle_2) {
                place = 7;
            } else {
                place = 8;
            }
        } else if (msg_angle < neutral_angle_3 - 100 &&
                   msg_angle >= neutral_angle_3 - 200) {
            if (angle_2 > neutral_angle_2) {
                place = 5;
            } else {
                place = 6;
            }
        } else if (msg_angle < neutral_angle_3 &&
                   msg_angle >= neutral_angle_3 - 100) {
            if (angle_2 > neutral_angle_2) {
                place = 3;
            } else {
                place = 4;
            }
        } else {
            if (angle_2 > neutral_angle_2) {
                place = 1;
            } else {
                place = 2;
            }
        }

        switch (place) { // Действия для каждой четверти
            case 1:
                servo3.setAngle(msg_angle);
                println("Case 1");
                break;

            case 2:
                correct_angle_2 = msg_angle - num2;
                if (angle_2 < correct_angle_2) {
                    servo2.setAngle(correct_angle_2);
                    print("Case 2, Angle_2 is ");
                    println(correct_angle_2);
                }
                servo3.setAngle(msg_angle);
                println("Case 2");
                break;

            case 3:
            case 7:
                correct_angle_2 = servo2.max_angle - (neutral_angle_3 - msg_angle) / 2;
                if (angle_2 > correct_angle_2) {
                    servo2.setAngle(correct_angle_2);
                    print("Case 3 or 7, Angle_2 is ");
                    println(correct_angle_2);
                }
                servo3.setAngle(msg_angle);
                println("Case 3 or 7");
                break;

            case 4:
            case 6:
                correct_angle_2 = servo2.min_angle + (neutral_angle_3 - msg_angle) / 2;
                if (angle_2 < correct_angle_2) {
                    servo2.setAngle(correct_angle_2);
                    print("Case 4 or 6, Angle_2 is ");
                    println(correct_angle_2);
                }
                servo3.setAngle(msg_angle);
                println("Case 4 or 6");
                break;

            case 5:
                correct_angle_2 = msg_angle + 50;
                if (angle_2 > correct_angle_2) {
                    servo2.setAngle(correct_angle_2);
                    print("Case 5, Angle_2 is ");
                    println(correct_angle_2);
                }
                servo3.setAngle(msg_angle);
                println("Case 5");
                break;

            case 8:
                correct_angle_2 = 300;
                if (angle_2 < correct_angle_2) {
                    servo2.setAngle(correct_angle_2);
                    print("Case 8, Angle_2 is ");
                    println(correct_angle_2);
                }
                servo3.setAngle(msg_angle);
                println("Case 8");
                break;

            default:
                break;
        }
    }
}


bool Servo::talk(uint16_t msg) {
    if (msg < 1) {
        return false;
    }
    if (msg == 1) {
        servo1.setTorque(0);
        println(servo1.getAngle());
        return true;
    }
    if (msg == 2) {
        servo2.setTorque(0);
        println(servo2.getAngle());
        return true;
    }
    if (msg == 3) {
        servo3.setTorque(0);
        println(1023 - servo3.getAngle());
        return true;
    }
    if (msg == 4) {
        servo4.setTorque(0);
        println(servo4.getAngle());
        return true;
    }

    uint8_t id = msg / 10000;
    Servo* servo = findServo(id);

    uint16_t msg_angle = msg % 10000;

    if (id == 2 || id == 3)
        test(msg);
    if (id == 3) {
        // servo3.new_angle = msg_angle + checkGamma(servo2.angle, msg_angle);
        servo3.setAngle(msg_angle);
        return true;
    }
    // servo->setAngle(msg_angle);
    // return true;
}


int32_t Servo::readRegister(char* command) {
    int32_t data;
    servos.readRegister(DXL_ID, command, &data);
    return data;
}


uint8_t Servo::getDXL_ID() {
    return DXL_ID;
}


uint16_t Servo::getAngle() {
    int32_t data;
    servos.readRegister(DXL_ID, "Present_Position", &data);
    return data;
}


uint16_t Servo::getMaxAngle() {
    return max_angle;
}


uint16_t Servo::getMinAngle() {
    return min_angle;
}


uint16_t Servo::getGoal() {
    return angle;
}


int32_t Servo::getLoad() {
    int32_t data;
    servos.readRegister(DXL_ID, "Present_Load", &data);
    if (data > 1023)
        data -= 1023;
    return data;
}


int32_t Servo::isMoving() {
    int32_t data;
    servos.readRegister(DXL_ID, "Moving", &data);
    return data;
}


uint16_t Servo::getSpeed() {
    return speed;
}


void Servo::toolPush() {
    uint16_t angle = servo4.getAngle();
    bool push_flag = false;
    while (!push_flag) {
        angle -= 10;
        servo4.setAngle(angle);
        delay(100);
        if (servo4.getLoad() > SERVO4_MAX_LOAD) {
            push_flag = true;
        }
    }
}


void Servo::toolPop() {
    servo4.reload();
    servo4.setAngle(1023);
}


void Servo::reload() {
    /*bool result = servos.reset(DXL_ID);
    if (result == false) {
        servo4.setSpeed(5192);
    }*/
    servo4.setAngle(1023);
}


#endif
