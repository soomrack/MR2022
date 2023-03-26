
#include <DynamixelWorkbench.h>
#include "Calibration.h"
#include "Connection.h"
#include "Config.h"
#include "Servo.h"


void setup() {

    Serial.begin(SERIAL_BAUDRATE);
    Serial.setTimeout(0);

    Servo::init();
    Servo::pingServos();

    servo1.setMoveMode(DEFAULT_SPEED, DEFAULT_BOOST);
    servo2.setMoveMode(DEFAULT_SPEED, DEFAULT_BOOST);
    servo3.setMoveMode(DEFAULT_SPEED, DEFAULT_BOOST);
    servo4.setMoveMode(DEFAULT_SPEED, DEFAULT_BOOST);

    Servo::getStartPosition();
    //Servo::Calibration_setup();
    //Servo::getStartPosition();
}


void loop() {
    Connection::getData();
    //Servo::talk(Serial.parseInt());
    //Servo::anglePrint();
}
