//
// Created by user on 05.03.23.
//

#ifndef MANIPULATOR_GRAPHICS_H
#define MANIPULATOR_GRAPHICS_H


#include <csignal>
#include <sys/ioctl.h>
#include "ncurses.h"
#include "Connect.h"
#include "History.h"


#define KEY_RETURN     10

#define ID_X            9
#define GOAL_X         17
#define ANGLE_X        23
#define SPEED_X        30
#define TORQUE_X       37
#define IS_MOVING_X    45
#define X_X            58
#define Y_X            63
#define Z_X            68

#define COMMAND_Y       8
#define LAST_COMMAND_Y  9

#define KEY_A          97
#define KEY_D         100
#define KEY_K         107
#define KEY_L         108
#define KEY_O         111
#define KEY_P         112


int CURS_Y = 0;
int CURS_X = 0;


uint64_t delta = 0;
int pressed_key = 0;


int get_columns() {
    struct winsize window{};
    ioctl(0, TIOCGWINSZ, &window);
    return window.ws_col;
}


int get_rows() {
    struct winsize window{};
    ioctl(0, TIOCGWINSZ, &window);
    return window.ws_row;
}


void finish() {
    Connect::disconnectArduino();
    resetty();
    endwin();
    exit(0);
}


void sighandler(int sig) {
    if (sig == SIGINT) {
        finish();
    }
}


void print_table() {
    for (int i = 1; i < 5; i++) {
        move(i + 1, 0);
        printw("servo%d", i);
    }

    move(0, ID_X);
    printw("id");

    move(0, GOAL_X);
    printw("goal");
    move(0, ANGLE_X);
    printw("angle");

    move(0, SPEED_X);
    printw("speed");

    move(0, TORQUE_X);
    printw("torque");

    move(0, IS_MOVING_X);
    printw("is_moving");

    move(0, X_X);
    printw("x");

    move(0, Y_X);
    printw("y");

    move(0, Z_X);
    printw("z");

    move(COMMAND_Y - 1, 0);
    printw("Set command:");

    refresh();
}


void print_id() {
    for (int i = 1; i < 5; i++) {
        move(i + 1, ID_X + 1);
        printw("%d", i);
    }
    refresh();
}


void print_exit_option() {
    move(get_rows() - 1, 0);
    printw("Press 'Ctrl+C' to exit");
    refresh();
}


void init_graphics() {
    initscr();
    savetty();  //  save terminal settings

    //nonl();  //  deny going to the new line

    cbreak();  //  send buffer after pressing enter
    echo();  //  visible printing
    timeout(0);

    //leaveok(stdscr, TRUE);
    //curs_set(0);  //  hide cursor
    keypad(stdscr, TRUE);

    signal(SIGINT, sighandler);

    clear();
    print_table();
    print_id();
    print_exit_option();
    move(COMMAND_Y, 0);
    refresh();
}


void clear_command_line() {
    move(COMMAND_Y, 0);
    for (int i = 0; i < get_columns(); i++) {
        printw(" ");
    }
    move(COMMAND_Y, 0);
    refresh();
}


void print_last_command() {
    move(LAST_COMMAND_Y, 0);
    for (int i = 0; i < get_columns(); i++) {
        printw(" ");
    }
    move(LAST_COMMAND_Y, 0);
    printw("%s", Connect::key_cmd.get());
}


void print_command_line() {
    move(COMMAND_Y, 0);
    printw("%s", Connect::key_cmd.get());
}


void key_return_proc() {
    if (Connect::key_cmd.getStr().empty()) {
        return;
    }
    History::append(Connect::key_cmd);
    Connect::decodeKeyInput();
    print_last_command();
    clear_command_line();
    Connect::key_cmd.reset();
    History::resetIndex();
}


void key_backspace_proc() {
    getsyx(CURS_Y, CURS_X);
    Connect::key_cmd.setCurs(CURS_X + 1);
    Connect::key_cmd.keyBackspace();
    clear_command_line();
    print_command_line();
    move(CURS_Y, CURS_X);
}


void key_delete_proc() {
    getsyx(CURS_Y, CURS_X);
    Connect::key_cmd.setCurs(CURS_X);
    Connect::key_cmd.keyDelete();
    clear_command_line();
    print_command_line();
    move(CURS_Y, CURS_X);
}


void key_left_proc() {
    getsyx(CURS_Y, CURS_X);
    move(CURS_Y, CURS_X - 1);
}


void key_right_proc() {
    getsyx(CURS_Y, CURS_X);
    if (CURS_X == Connect::key_cmd.size()) {
        return;
    }
    move(CURS_Y, CURS_X + 1);
}


void key_up_proc() {
    if (History::getIndex() == 0) {
        History::setCurrentCommand(Connect::key_cmd.get());
    }
    History::moveUp();
    Connect::key_cmd.set(History::get());
    clear_command_line();
    print_command_line();
}


void key_down_proc() {
    History::moveDown();
    Connect::key_cmd.set(History::get());
    clear_command_line();
    print_command_line();
}


/*
void move_servo1_via_buttons(uint64_t input_delta) {
    Connect::setId(DXL_ID1);
    Connect::setTask(SET_ANGLE_TASK);
    Connect::setValue(gservo1.getGoal() + input_delta);
}


void key_a_proc() {
    move_servo1_via_buttons(delta);
}


void key_d_proc() {
    move_servo1_via_buttons(-delta);
}


void manipulate_proc() {
    getsyx(CURS_Y, CURS_X);
    clear_command_line();
    int key;
    if (pressed_key == key && delta < 100) {
        delta += 20;
    }
    else {
        delta = 10;
    }
    pressed_key = key;
    if (key == KEY_A) {
        return key_a_proc();
    }
    if (key == KEY_D) {
        return key_d_proc();
    }

    print_command_line();
    move(CURS_Y, Connect::key_cmd.getCurs() + 1);
    refresh();
}
*/

void key_proc(int key) {
    char symbol = (char) key;
    /*if (Connect::manipulate_flag) {
        manipulate_proc();
    }*/

    if (key == KEY_RETURN) {
        return key_return_proc();
    }
    if (key == KEY_BACKSPACE) {
        return key_backspace_proc();
    }
    if (key == KEY_DC) {
        return key_delete_proc();
    }
    if (key == KEY_LEFT) {
        return key_left_proc();
    }
    if (key == KEY_RIGHT) {
        return key_right_proc();
    }
    if (key == KEY_UP) {
        return key_up_proc();
    }
    if (key == KEY_DOWN) {
        return key_down_proc();
    }
    if (key == ERR) {
        return;
    }

    getsyx(CURS_Y, CURS_X);
    Connect::key_cmd.push(symbol, CURS_X - 1);
    clear_command_line();
    print_command_line();
    move(CURS_Y, Connect::key_cmd.getCurs() + 1);
    refresh();
}


void print_param(uint8_t gservo_id, int x, uint16_t param) {
    move(1 + gservo_id, x);
    printw("    ");
    move(1 + gservo_id, x);
    printw("%d", param);
}


void print_goal(uint8_t gservo_id, uint16_t goal) {
    print_param(gservo_id, GOAL_X, goal);
}


void print_angle(uint8_t gservo_id, uint16_t angle) {
    print_param(gservo_id, ANGLE_X + 1, angle);
}


void print_speed(uint8_t gservo_id, uint16_t speed) {
    print_param(gservo_id, SPEED_X + 1, speed);
}


void print_torque(uint8_t gservo_id, uint16_t torque) {
    print_param(gservo_id, TORQUE_X + 1, torque);
}


void print_is_moving(uint8_t gservo_id, uint16_t is_moving) {
    print_param(gservo_id, IS_MOVING_X, is_moving);
}


void printX(uint8_t gservo_id, uint16_t x) {
    print_param(gservo_id, X_X, x);
}


void printY(uint8_t gservo_id, uint16_t y) {
    print_param(gservo_id, Y_X, y);
}


void printZ(uint8_t gservo_id, uint16_t z) {
    print_param(gservo_id, Z_X, z);
}


void print_params_from_servo(Gservo gservo) {
    print_goal(gservo.getId(), gservo.getGoal());
    print_angle(gservo.getId(), gservo.getAngle());
    print_speed(gservo.getId(), gservo.getSpeed());
    print_torque(gservo.getId(), gservo.getTorque());
    print_is_moving(gservo.getId(), gservo.getIsMoving());
    printX(gservo.getId(), gservo.getX());
    printY(gservo.getId(), gservo.getY());
    printZ(gservo.getId(), gservo.getZ());
}


void print_params() {
    getsyx(CURS_Y, CURS_X);
    print_params_from_servo(gservo1);
    print_params_from_servo(gservo2);
    print_params_from_servo(gservo3);
    print_params_from_servo(gservo4);
    move(CURS_Y, CURS_X);
}


#endif //MANIPULATOR_GRAPHICS_H
