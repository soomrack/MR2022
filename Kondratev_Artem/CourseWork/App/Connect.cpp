//
// Created by user on 05.03.23.
//

#include "Connect.h"


bool Connect::openArduino() {
    if (Arduino == -1) {
        Arduino = open("/dev/ttyACM1", O_RDWR | O_NOCTTY | O_NONBLOCK);
        if (Arduino == -1) {
            return false;
        }
    }
    tcgetattr(Arduino, &SerialPortSettings);
    cfsetispeed(&SerialPortSettings, SERIAL_BAUDRATE);
    cfsetospeed(&SerialPortSettings, SERIAL_BAUDRATE);
    return true;
}


void Connect::clearCommand() {
    command[0] = START_BYTE;
    command[1] = START_BYTE;
    command[2] = PING_DXL_ID;
    command[3] = PING_TASK;
    command[4] = PING_VALUE;
    command[5] = PING_VALUE;
    calcCommandCheckSum();
}


void Connect::setConnection() {
    if (!openArduino()) {
        std::cout << "Unable to connect" << std::endl;
        return;
    }
    clearCommand();
    bool message_flag = false;
    std::cout << "connecting..." << std::endl;
    auto start_timer = std::chrono::system_clock::now();
    while (!message_flag) {
        auto end_timer = std::chrono::system_clock::now();
        if (std::chrono::duration_cast<std::chrono::milliseconds>(end_timer - start_timer).count() > int(TIMER)) {
            sendCommand();
            message_flag = receiveMessage();
            start_timer = std::chrono::system_clock::now();
        }
    }
    std::cout << "connected" << std::endl;
    sleep(1);
}


void Connect::disconnectArduino() {
    close(Arduino);
}


void Connect::calcCommandCheckSum() {
    uint64_t sum = 0;
    for (int i = COMMAND_START_BYTE1_CELL; i < COMMAND_CHECKSUM_CELL; i++) {
        sum += command[i];
    }
    command[COMMAND_CHECKSUM_CELL] = char(sum / 8);
    //command[COMMAND_CHECKSUM_CELL] = char((command[2] + command[3] + command[4] + command[5]) / 8);
}


char Connect::calcMessageCheckSum(const char buffer[]) {
    uint64_t sum = 0;
    for (int i = MESSAGE_START_BYTE1_CELL; i < MESSAGE_CHECKSUM_CELL; i++) {
        sum += buffer[i];
    }
    return char(sum / 8);
}


void Connect::sendCommand() {
    if (!openArduino()) {
        return;
    }
    calcCommandCheckSum();
    write(Arduino, command, COMMAND_SIZE);
    clearCommand();
}


void Connect::setId(char id) {
    command[COMMAND_ID_CELL] = id;
}


void Connect::setTask(char task) {
    command[COMMAND_TASK_CELL] = task;
}


void Connect::setValue(uint16_t value) {
    command[COMMAND_VALUE1_CELL] = char(value / 100);
    command[COMMAND_VALUE2_CELL] = char(value % 100);
}


void Connect::encodeCommand(uint64_t cmd) {
    char id = char(cmd / 100000);
    setId(id);

    char task = char((cmd % 100000) / 10000);
    setTask(task);

    uint16_t value = cmd % 10000;
    setValue(value);
}


Gservo* Connect::findGservo(uint8_t id) {
    if (id == 1) {
        return &gservo1;
    }
    if (id == 2) {
        return &gservo2;
    }
    if (id == 3) {
        return &gservo3;
    }
    if (id == 4) {
        return &gservo4;
    }
}


void Connect::decodeMessage() {
    Gservo* gservo = findGservo(message[MESSAGE_ID_CELL]);
    gservo->setGoal(message[MESSAGE_GOAL1_CELL], message[MESSAGE_GOAL2_CELL]);
    gservo->setAngle(message[MESSAGE_ANGLE1_CELL], message[MESSAGE_ANGLE2_CELL]);
    gservo->setSpeed(message[MESSAGE_SPEED1_CELL], message[MESSAGE_SPEED2_CELL]);
    gservo->setTorque(message[MESSAGE_TORQUE1_CELL], message[MESSAGE_TORQUE2_CELL]);
    gservo->setIsMoving(message[MESSAGE_IS_MOVING_CELL]);
    gservo->setX(message[MESSAGE_X1_CELL], message[MESSAGE_X2_CELL]);
    gservo->setX(message[MESSAGE_Y1_CELL], message[MESSAGE_Y2_CELL]);
    gservo->setX(message[MESSAGE_Z1_CELL], message[MESSAGE_Z2_CELL]);
}


bool Connect::receiveMessage() {
    if (!openArduino()) {
        return false;
    }

    char buf[MESSAGE_SIZE];
    read(Arduino, buf, MESSAGE_SIZE);

    if (buf[0] == START_BYTE && buf[1] == START_BYTE && buf[MESSAGE_CHECKSUM_CELL] == calcMessageCheckSum(buf)) {
        std::memcpy(message, buf, sizeof(char) * MESSAGE_SIZE);
        Connect::decodeMessage();
        return true;
    }
    return false;
}


uint64_t Connect::checkNumberCommand() {
    char numbers[] = {'0', '1', '2', '3', '4', '5', '6', '7', '8', '9'};
    uint64_t flag = 0;
    for (int i = 0; i < key_cmd.size(); i++) {
        for (char number: numbers) {
            if (key_cmd.getStr()[i] == number) {
                flag++;
                break;
            }
        }
    }
    return flag;
}


void Connect::toolPush() {
    clearCommand();
    command[COMMAND_ID_CELL] = DXL_ID4;
    command[COMMAND_TASK_CELL] = TOOL_PUSH_TASK;
}


void Connect::toolPop() {
    clearCommand();
    command[COMMAND_ID_CELL] = DXL_ID4;
    command[COMMAND_TASK_CELL] = TOOL_POP_TASK;
}


void Connect::decodeKeyInput() {

    if (checkNumberCommand() == key_cmd.size()) {
        Connect::encodeCommand(stoi(key_cmd.getStr()));
        return;
    }
    if (key_cmd.getStr() == "manipulate") {
        manipulate_flag = true;
        return;
    }
    if (key_cmd.getStr() == "push") {
        return toolPush();
    }
    if (key_cmd.getStr() == "pop") {
        return toolPop();
    }
}
