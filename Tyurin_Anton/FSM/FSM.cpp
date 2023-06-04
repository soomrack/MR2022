#include <iostream>

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


double number(double u){
    return u;
}


double numberOpposite(double u){
    return -u;
}


int main() {
    FSM Machine;
    Machine.setState(number);
    std::cout << Machine.activeState(10) << std::endl;
    Machine.setState(numberOpposite);
    std::cout << Machine.activeState(10) << std::endl;
    return 0;
};