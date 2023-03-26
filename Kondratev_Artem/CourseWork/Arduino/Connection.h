
#ifndef Connection_h
#define Connection_h


#include "Config.h"
#include "Servo.h"


typedef struct Command {
    uint8_t id = 0;
    uint8_t command = 0;
    uint16_t value1 = 0;
    uint16_t value2 = 0;
    uint16_t value = 0;
    uint16_t checksum = 0;
} Command;


typedef struct Message {
    uint8_t id = 0;
    uint16_t goal1 = 0;
    uint16_t goal2 = 0;
    uint16_t angle1 = 0;
    uint16_t angle2 = 0;
    uint16_t speed1 = 0;
    uint16_t speed2 = 0;
    uint16_t boost1 = 0;
    uint16_t boost2 = 0;
    uint16_t torque1 = 0;
    uint16_t torque2 = 0;
    uint8_t is_moving = 0;
} Message;


Command Cmd;
Message Msg;


class Connection {
private:
    static uint16_t getCalc();
    static uint16_t setCalc();
    static void setMsgValues(uint8_t id);
    static void setData(uint8_t id);
public:
    static void getData();
private:
    static void findCommand();
};


uint16_t Connection::getCalc() {
    return (char(Cmd.id) + char(Cmd.command) + char(Cmd.value1) + char(Cmd.value2)) / 8;
}


uint16_t Connection::setCalc() {
    return (char(Msg.id) + char(Msg.goal1) + char(Msg.goal2) + char(Msg.angle1) + char(Msg.angle2) + char(Msg.speed1) +
            char(Msg.speed2) +
            char(Msg.boost1) + char(Msg.boost2) + char(Msg.torque1) + char(Msg.torque2) + char(Msg.is_moving)) / 8;
}


void Connection::setMsgValues(uint8_t id) {
    Servo* servo = Servo::findServo(id);
    Msg.id = servo->getDXL_ID();
    Msg.goal1 = servo->getGoal() / 100;
    Msg.goal2 = servo->getGoal() % 100;
    Msg.angle1 = servo->getAngle() / 100;
    Msg.angle2 = servo->getAngle() % 100;
    Msg.speed1 = servo->getSpeed() / 100;
    Msg.speed2 = servo->getSpeed() % 100;
    Msg.boost1 = servo->getBoost() / 100;
    Msg.boost2 = servo->getBoost() % 100;
    Msg.torque1 = servo->getLoad() / 100;
    Msg.torque2 = servo->getLoad() % 100;
    Msg.is_moving = servo->isMoving();
}


void Connection::setData(uint8_t id) {
    setMsgValues(id);

    Serial.print(char(64));
    Serial.print(char(64));

    Serial.print(char(Msg.id));
    Serial.print(char(Msg.goal1));
    Serial.print(char(Msg.goal2));
    Serial.print(char(Msg.angle1));
    Serial.print(char(Msg.angle2));
    Serial.print(char(Msg.speed1));
    Serial.print(char(Msg.speed2));
    Serial.print(char(Msg.boost1));
    Serial.print(char(Msg.boost2));
    Serial.print(char(Msg.torque1));
    Serial.print(char(Msg.torque2));
    Serial.print(char(Msg.is_moving));

    Serial.print(char(setCalc()));
}


void Connection::getData() {
    if (Serial.available() >= 7) {
        byte start1 = Serial.read();
        byte start2 = Serial.read();
        if (start1 + start2 == 128) {
            Cmd.id = Serial.read();
            Cmd.command = Serial.read();
            Cmd.value1 = Serial.read();
            Cmd.value2 = Serial.read();
            Cmd.checksum = Serial.read();
            if (getCalc() == Cmd.checksum) {
                findCommand();
                setData(DXL_ID1);
                setData(DXL_ID2);
                setData(DXL_ID3);
                setData(DXL_ID4);
            }
        }
    }
}


void Connection::findCommand() {
    Cmd.value = Cmd.value1 * 100 + Cmd.value2;
    if (Cmd.command == 0) {
        return;
    }
    if (Cmd.command == SET_ANGLE_TASK) {
        return Servo::setAngle(Cmd.value, Cmd.id);
    }
    if (Cmd.command == SET_SPEED_TASK) {
        return Servo::setSpeed(Cmd.value, Cmd.id);
    }
    if (Cmd.command == SET_BOOST_TASK) {
        return Servo::setBoost(Cmd.value, Cmd.id);
    }
    if (Cmd.command == TOOL_PUSH_TASK) {
        return Servo::toolPush();
    }
    if (Cmd.command == TOOL_POP_TASK) {
        return Servo::toolPop();
    }

    if (Cmd.command == REBOOT_TASK) {
        return;
    }
    if (Cmd.command == GET_ERROR_TASK) {
        return;
    }
}


#endif
