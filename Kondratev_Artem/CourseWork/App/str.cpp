//
// Created by user on 3/17/23.
//

#include "str.h"

#include <utility>


str::str() {
    string = "";
    curs = -1;
}


str::str(std::string _string) {
    string = std::move(_string);
    curs = (int)string.size();
}


void str::push(char symbol, int index) {
    curs = index;
    if (index >= string.size()) {
        string += symbol;
        return;
    }
    std::string buffer = string;
    string = "";
    for (int i = 0; i < index; i++) {
        string += buffer[i];
    }
    string += symbol;
    for (int i = index; i < buffer.size(); i++) {
        string += buffer[i];
    }
}


void str::pop(int index) {
    std::string buffer = string;
    string = "";
    for (int i = 0; i < buffer.size(); i++) {
        if (i != index) {
            string += buffer[i];
        }
    }
}


void str::reset() {
    curs = -1;
    string = "";
}


uint64_t str::size() {
    return string.size();
}


const char* str::get() {
    return string.c_str();
}


std::string str::getStr() {
    return string;
}


void str::keyBackspace() {
    pop(curs);
}


void str::keyDelete() {
    pop(curs + 1);
}


void str::setCurs(int CURS_X) {
    if (CURS_X >= string.size()) {
        curs = (int)string.size() - 1;
        return;
    }
    curs = CURS_X - 1;
}


int str::getCurs() const {
    return curs;
}


void str::set(std::string _string) {
    string = std::move(_string);
}
