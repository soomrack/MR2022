
#ifndef Config_h
#define Config_h


#include <cstdint>


#define PRINT_FLAG           false


#define DEVICE_NAME            "3"

#define SERVO_BAUDRATE     1000000
#define SERIAL_BAUDRATE    2000000

#define DXL_ID1                  1
#define DXL_ID2                  2
#define DXL_ID3                  3
#define DXL_ID4                  4

#define DEFAULT_SPEED          100
#define DEFAULT_BOOST           40

#define SERVO1_START_POSITION    0
#define SERVO2_START_POSITION  512
#define SERVO3_START_POSITION  512
#define SERVO4_START_POSITION  512


#define COMMAND_SIZE             7
#define MESSAGE_SIZE            15
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
#define MESSAGE_IS_MOVING_CELL  13
#define MESSAGE_CHECKSUM_CELL   14

#define SET_ANGLE_TASK           1
#define SET_SPEED_TASK           2
#define SET_BOOST_TASK           3
#define TOOL_PUSH_TASK           4
#define TOOL_POP_TASK            5
#define REBOOT_TASK              8
#define GET_ERROR_TASK           9
#define CALIBRATION_TASK         7


#define SERVO4_MAX_LOAD        600

#define SERVO1_MIN_ANGLE       150
#define SERVO1_MAX_ANGLE       853

#define SERVO2_MIN_ANGLE       212//200
#define SERVO2_MAX_ANGLE       612//550

#define SERVO3_MIN_ANGLE       390
#define SERVO3_MAX_ANGLE       790

#define SERVO4_MIN_ANGLE       511
#define SERVO4_MAX_ANGLE      1023

#define ALPHA0 SERVO2_MAX_ANGLE
#define BETA0 760//660
const uint16_t MIN_GAMMA = 1023 + BETA0 - ALPHA0;//1023 - ALPHA0 + SERVO4_MIN_ANGLE - BETA0; // pos 512 instead of 1023
const uint16_t MAX_GAMMA = 2 ^ 16;


#endif
