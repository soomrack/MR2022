//
// Created by user on 3/27/23.
//

#ifndef HELLO_WORLD_FSM_H
#define HELLO_WORLD_FSM_H


class FSM {
private:
    void (*active_state)();

public:
    FSM();

    void setState(void state());
    void delState();
    void activeState();
};


FSM::FSM() {
    active_state = nullptr;
}


void FSM::setState(void state()) {
    active_state = state;
}


void FSM::delState() {
    active_state = nullptr;
}


void FSM::activeState() {
    if (active_state != nullptr) {
        active_state();
    }
}


#endif //HELLO_WORLD_FSM_H
