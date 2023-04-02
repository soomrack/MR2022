
#include <cstdint>
#include <cmath>
#include "print.h"


class Joint {
private:
    uint8_t DXL_ID;
    // Coordinates in mm.
    int32_t x;
    int32_t y;
    int32_t z;
public:
    Joint(uint8_t _DXL_ID);
    ~Joint() = default;

    void GoTo(int32_t my_x, int32_t my_y, int32_t my_z);
    void getCoordinates();

};


Joint::Joint(uint8_t _DXL_ID) {
    DXL_ID = _DXL_ID;

    // Lengths of links in mm:
    const uint8_t x0 = -25;
    const uint8_t z0 = 100;
    const uint8_t len1 = 103;
    const uint8_t len2 = 150;
    const uint8_t len3 = len2;
    const uint8_t len4 = 120;
    int8_t q0 = map(servo1.getAngle(), 0, 1023, 0, 360);
    int8_t q1 = map(servo2.getAngle(), 0, 1023, 0, 360);
    int8_t q2 = map(servo3.getAngle(), 0, 1023, 0, 360);

    switch (DXL_ID) {
        case 1: {
            x = x0 * cos(q0);
            y = x0 * sin(q0);
            z = z0;
            break;
        }
        case 2: {
            x = (x0 + len2 * cos(q1)) * cos(q0);
            y = (x0 + len2 * cos(q1)) * sin(q0);
            z = z0 + len2 * sin(q1);
            break;
        }
        case 3: {
            x = (x0 + len2 * cos(q1) + len3 * cos(q2)) * cos(q0);
            y = (x0 + len2 * cos(q1) + len3 * cos(q2)) * sin(q0);
            z = z0 + len1 * sin(q1) + len3 * sin(q2);
            break;
        }
        case 4: {
            x = (x0 + len2 * cos(q1) + len3 * cos(q2) + len4) * cos(q0);
            y = (x0 + len2 * cos(q1) + len3 * cos(q2) + len4) * sin(q0);
            z = z0 + len1 * sin(q1) + len3 * sin(q2);
            break;
        }
        default:
            print("Wrong DXL_ID!");
            break;
    }
}


void GoTo(int32_t x, int32_t y, int32_t z);


void Joint::getCoordinates() {
    print("Coordinate x: ");
    println(x);
    print("Coordinate y: ");
    println(y);
    print("Coordinate z: ");
    println(z);
}
