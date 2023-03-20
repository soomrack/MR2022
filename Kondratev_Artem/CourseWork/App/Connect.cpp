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
    cfsetispeed(&SerialPortSettings, 9600); //SERIAL_BAUDRATE
    cfsetospeed(&SerialPortSettings, 9600); //SERIAL_BAUDRATE
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
    command[COMMAND_CHECKSUM_CELL] = char((command[2] + command[3] + command[4] + command[5]) / 8);
}


char Connect::calcMessageCheckSum(const char buffer[]) {
    uint64_t sum = 0;
    for (int i = 2; i < MESSAGE_CHECKSUM_CELL; i++) {
        //std::cout << int(buffer[i]) << " ";
        sum += buffer[i];
    }
    //std::cout << std::endl;
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


bool Connect::receiveMessage() {
    if (!openArduino()) {
        return false;
    }

    char buffer[MESSAGE_SIZE];
    read(Arduino, buffer, MESSAGE_SIZE);

    if (buffer[0] == 64 && buffer[1] == 64 && buffer[MESSAGE_CHECKSUM_CELL] == calcMessageCheckSum(buffer)) {
        std::memcpy(message, buffer, sizeof(char) * MESSAGE_SIZE);
        Connect::decodeMessage();
        return true;
    }
    return false;
}


Gservo* findGservo(uint8_t id) {
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
    gservo->setBoost(message[MESSAGE_BOOST1_CELL], message[MESSAGE_BOOST2_CELL]);
    gservo->setTorque(message[MESSAGE_TORQUE1_CELL], message[MESSAGE_TORQUE2_CELL]);
    gservo->setIsMoving(message[MESSAGE_IS_MOVING1_CELL], message[MESSAGE_IS_MOVING2_CELL]);
}


void Connect::decodeKeyInput(const std::string& cmd) {
    encodeCommand(stoi(cmd));
}
