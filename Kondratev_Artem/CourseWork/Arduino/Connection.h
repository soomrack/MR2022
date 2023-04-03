
#ifndef Connection_h
#define Connection_h


#include "Config.h"
//#include "FSM.h"
#include "Joint.h"
#include "Servo.h"


char command[COMMAND_SIZE];
char message[MESSAGE_SIZE];


class Connection {
private:
    //static FSM Machine;

public:
    //static void initFSM();

private:
    static uint16_t calcCommandCheckSum();
    static uint16_t calcMessageCheckSum();
    static void setMsgValues(uint8_t id);
    static void sendMessage(uint8_t id);
    
public:
    static void getData();
    
private:
    static void findCommand();
};


uint16_t Connection::calcCommandCheckSum() {
    uint64_t sum = 0;
    for (int i = COMMAND_START_BYTE1_CELL; i < COMMAND_CHECKSUM_CELL; i++) {
        sum += (uint64_t)command[i];
    }
    return char(sum / 8);
    //return (char(Cmd.id) + char(Cmd.command) + char(Cmd.value1) + char(Cmd.value2)) / 8;
}


uint16_t Connection::calcMessageCheckSum() {
    uint64_t sum = 0;
    for (int i = MESSAGE_START_BYTE1_CELL; i < MESSAGE_CHECKSUM_CELL; i++) {
        sum += (uint64_t)message[i];
    }
    return char(sum / 8);
}


void Connection::setMsgValues(uint8_t id) {
    Servo* servo = Servo::findServo(id);
    
    message[MESSAGE_START_BYTE1_CELL] = START_BYTE;
    message[MESSAGE_START_BYTE2_CELL] = START_BYTE;
    
    message[MESSAGE_ID_CELL] = id;
    
    message[MESSAGE_GOAL1_CELL] = servo->getGoal() / 100;
    message[MESSAGE_GOAL1_CELL] = servo->getGoal() % 100;
    
    message[MESSAGE_ANGLE1_CELL] = servo->getAngle() / 100;
    message[MESSAGE_ANGLE2_CELL] = servo->getAngle() % 100;
    
    message[MESSAGE_SPEED1_CELL] = servo->getSpeed() / 100;
    message[MESSAGE_SPEED2_CELL] = servo->getSpeed() % 100;
    
    message[MESSAGE_TORQUE1_CELL] = servo->getLoad() / 100;
    message[MESSAGE_TORQUE2_CELL] = servo->getLoad() % 100;

    message[MESSAGE_IS_MOVING_CELL] = servo->isMoving();

    message[MESSAGE_TORQUE1_CELL] = servo->getLoad() / 100;

    message[MESSAGE_X1_CELL] = 12;
    message[MESSAGE_X2_CELL] = 13;
    message[MESSAGE_Y1_CELL] = 14;
    message[MESSAGE_Y2_CELL] = 15;
    message[MESSAGE_Z1_CELL] = 16;
    message[MESSAGE_Z2_CELL] = 17;

    message[MESSAGE_CHECKSUM_CELL] = calcMessageCheckSum();
}


void Connection::sendMessage(uint8_t id) {
    setMsgValues(id);

    Serial.print(char(64));
    Serial.print(char(64));


    for (int cell = MESSAGE_START_BYTE1_CELL; cell < MESSAGE_SIZE; cell++) {
        Serial.print(char(message[cell]));
    }
}


void Connection::getData() {
    if (Serial.available() >= 7) {
        command[COMMAND_START_BYTE1_CELL] = Serial.read();
        command[COMMAND_START_BYTE2_CELL] = Serial.read();
        if (command[COMMAND_START_BYTE1_CELL] == START_BYTE && command[COMMAND_START_BYTE1_CELL] == START_BYTE) {
            for (int cell = COMMAND_ID_CELL; cell < COMMAND_SIZE; cell++) {
                command[cell] = Serial.read();
            }
            if (calcCommandCheckSum() == command[COMMAND_CHECKSUM_CELL]) {
                findCommand();
                sendMessage(DXL_ID1);
                sendMessage(DXL_ID2);
                sendMessage(DXL_ID3);
                sendMessage(DXL_ID4);
            }
        }
    }
}


void Connection::findCommand() {
    uint16_t value = command[COMMAND_VALUE1_CELL] * 100 + command[COMMAND_VALUE2_CELL];
    if (command[COMMAND_TASK_CELL] == PING_TASK) {
        return;
    }
    if (command[COMMAND_TASK_CELL] == SET_ANGLE_TASK) {
        return Servo::setAngle(value, command[COMMAND_ID_CELL]);
    }
    if (command[COMMAND_TASK_CELL] == SET_SPEED_TASK) {
        return Servo::setSpeed(value, command[COMMAND_ID_CELL]);
    }
    if (command[COMMAND_TASK_CELL] == TOOL_PUSH_TASK) {
        return Servo::toolPush();
    }
    if (command[COMMAND_TASK_CELL] == TOOL_POP_TASK) {
        return Servo::toolPop();
    }
    if (command[COMMAND_TASK_CELL] == CALIBRATION_TASK) {
        return;
    }
    if (command[COMMAND_TASK_CELL] == REBOOT_TASK) {
        return;
    }
    if (command[COMMAND_TASK_CELL] == GET_ERROR_TASK) {
        return;
    }
    if (command[COMMAND_TASK_CELL] == SET_X_TASK) {
        return Joint::setX(value);
    }
    if (command[COMMAND_TASK_CELL] == SET_Y_TASK) {
        return Joint::setY(value);
    }
    if (command[COMMAND_TASK_CELL] == SET_Z_TASK) {
        return Joint::setZ(value);
    }
}


#endif
