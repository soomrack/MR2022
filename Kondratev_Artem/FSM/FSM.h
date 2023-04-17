//
// Created by user on 3/27/23.
//

#ifndef HELLO_WORLD_FSM_H
#define HELLO_WORLD_FSM_H


class FSM {
private:
    double (*active_state)(double);

public:
    FSM();

    void setState(double state(double));
    double activeState(double u);
};


FSM::FSM() {
    active_state = nullptr;
}


void FSM::setState(double state(double)) {
    active_state = state;
}


double FSM::activeState(double u) {
    if (active_state != nullptr) {
        return active_state(u);
    }
}


#endif //HELLO_WORLD_FSM_H
