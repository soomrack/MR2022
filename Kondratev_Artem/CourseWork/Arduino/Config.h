
#ifndef Config_h
#define Config_h


#include <cstdint>


#define DEVICE_NAME            "3"

#define SERVO_BAUDRATE     1000000
#define SERIAL_BAUDRATE      57600

#define DXL_ID1                  1
#define DXL_ID2                  2
#define DXL_ID3                  3
#define DXL_ID4                  4


#define COMMAND_SIZE             7
#define MESSAGE_SIZE            16
#define TIMER                  100
#define START_BYTE              64

#define PING_DXL_ID              0
#define PING_TASK                0
#define PING_VALUE               0

#define COMMAND_ID_CELL          2
#define COMMAND_TASK_CELL        3
#define COMMAND_VALUE1_CELL      4
#define COMMAND_VALUE2_CELL      5
#define COMMAND_CHECKSUM_CELL    6

#define MESSAGE_ID_CELL          2
#define MESSAGE_GOAL1_CELL       3
#define MESSAGE_GOAL2_CELL       4
#define MESSAGE_ANGLE1_CELL      5
#define MESSAGE_ANGLE2_CELL      6
#define MESSAGE_SPEED1_CELL      7
#define MESSAGE_SPEED2_CELL      8
#define MESSAGE_BOOST1_CELL      9
#define MESSAGE_BOOST2_CELL     10
#define MESSAGE_TORQUE1_CELL    11
#define MESSAGE_TORQUE2_CELL    12
#define MESSAGE_IS_MOVING1_CELL 13
#define MESSAGE_IS_MOVING2_CELL 14
#define MESSAGE_CHECKSUM_CELL   15


#define SERVO1_MIN_ANGLE       150
#define SERVO1_MAX_ANGLE       853

#define SERVO2_MIN_ANGLE         0 //200
#define SERVO2_MAX_ANGLE      1023 //550

#define SERVO3_MIN_ANGLE         0 //250
#define SERVO3_MAX_ANGLE      1023 //1023

#define SERVO4_MIN_ANGLE       511
#define SERVO4_MAX_ANGLE      1023

#define ALPHA0 SERVO2_MAX_ANGLE
#define BETA0 660
const uint16_t MIN_GAMMA = 1023 + BETA0 - ALPHA0;//1023 - ALPHA0 + SERVO4_MIN_ANGLE - BETA0; // pos 512 instead of 1023
const uint16_t MAX_GAMMA = 2 ^ 16;


#endif
