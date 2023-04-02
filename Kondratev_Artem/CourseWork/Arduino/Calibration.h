
#ifndef Calibration_h
#define Calibration_h


#include "Servo.h"


class Calibration {
public:
    static void Calibration_min(Servo servo);
    static void Calibration_max(Servo servo);
    static void Calibration_setup();
};


void Calibration::Calibration_max(Servo servo) {
    uint16_t servo_max_angle = 512;
    servo.setSpeed(100);

    while (true) {
        // Serial.println(getLoad());  // DEBUG
        // Serial.println(servo_max_angle);
        // Serial.println(getAngle());
        // Serial.println(" ");

        servo.setAngle(servo_max_angle);
        delay(100);
        if (servo.isMoving() == 0) servo_max_angle += 50;
        else if (servo.getLoad() > 670) {
            servo_max_angle -= 50;
            servo.setAngle(servo_max_angle);
            break;
        }
    }

    servo.setMaxAngle(servo_max_angle);

    println(" ");
    println(servo_max_angle);
}


void Calibration::Calibration_min(Servo servo) {
    uint16_t servo_min_angle = 512;
    servo.setSpeed(100);
    while (true) {
        // Serial.println(getLoad());  // DEBUG
        // Serial.println(servo_min_angle);
        // Serial.println(getAngle());
        // Serial.println(" ");

        servo.setAngle(servo_min_angle);
        delay(100);
        if (servo.isMoving() == 0) servo_min_angle -= 50;
        else if (servo.getLoad() > 670) {
            servo_min_angle += 50;
            servo.setAngle(servo_min_angle);
            break;
        }
    }

    servo.setMinAngle(servo_min_angle);

    println(" ");
    println(servo_min_angle);
}


void Calibration::Calibration_setup() {
    Calibration_max(servo2);
    Calibration_min(servo2);
    servo2.setAngle((servo2.getMinAngle() + servo2.getMaxAngle()) / 2);
    delay(2000);
    Calibration_max(servo3);
    Calibration_min(servo3);
}


#endif
