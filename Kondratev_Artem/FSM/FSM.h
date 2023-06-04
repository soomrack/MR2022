//
// Created by user on 3/27/23.
//

#ifndef HELLO_WORLD_FSM_H
#define HELLO_WORLD_FSM_H


#include <functional>
#include <utility>

typedef double U;
typedef std::function<double(double)> T;


class FSM {
private:
    T active_state;

public:
    FSM();

    void setState(T state);
    U activeState(double u);
};


FSM::FSM() {
    active_state = nullptr;
}


void FSM::setState(T state) {
    active_state = std::move(state);
}


U FSM::activeState(U u) {
    if (active_state != nullptr) {
        return active_state(u);
    }
}


#endif //HELLO_WORLD_FSM_H
