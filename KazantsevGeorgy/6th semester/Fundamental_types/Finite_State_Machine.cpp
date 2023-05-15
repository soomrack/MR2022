#include <functional>
#include <utility>
#include <iostream>
#include <cmath>
#include <string>
using namespace std;
const int kf = 10;

typedef function<double(double)> T;


class Finite_State_Machine {
private:
    T active_state;

public:
    Finite_State_Machine();
    void setState(T state);
    double activeState(double val);
};

Finite_State_Machine::Finite_State_Machine() {
    active_state = nullptr;
}

void Finite_State_Machine::setState(T state) {
    active_state = std::move(state);
}

double Finite_State_Machine::activeState(double val) {
    if (active_state != nullptr) {
        return active_state(val);
    }
    return 0;
}

double mult(double val) { return kf * val; }
double sinx(double val) { return sin(val); }

int main() {
    Finite_State_Machine A;
    A.setState(sinx);
    cout << A.activeState(2.5);
    return 0;
}
