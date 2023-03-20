
#ifndef Test_h
#define Test_h


#include "Servo.h"


void Servo::test(uint16_t msg) {
    if (msg == 0) {
        return;
    }
    uint16_t msg_angle = msg % 10000;
    if (id == 2) {
        Serial.print("msg angle ");
        Serial.println(msg_angle);
        Serial.print("msg in function ");
        Serial.println(msg);
        uint16_t num;
        uint16_t angle3 = 1023 - servo3.angle;

        if (angle3 < 450) {
            num = 640;
            if (msg > (640 - angle3)) {
                servo2.setAngle(msg);
                return;
            } else {
                uint16_t a3 = angle3 - (msg - (num - angle3));
                a3 = 1023 - a3;
                servo2.setAngle(msg);
                servo3.setAngle(a3);
                return;
            }
        } else {
            num = 1060;
            if (msg < (1060 - angle3)) {
                servo2.setAngle(msg);
                return;
            } else {
                uint16_t a3 = angle3 - (msg - (num - angle3));
                a3 = 1023 - a3;
                servo2.setAngle(msg);
                servo3.setAngle(a3);
                return;
            }
        }
    }

#endif    
