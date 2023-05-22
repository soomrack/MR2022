#include <iostream>
#include <map>
#include <string>

class State {
public:
    State(std::string name, bool is_final = false) : name(name), is_final(is_final) {}
    std::string getName() { return name; }
    bool isFinal() { return is_final; }
    void addTransition(char symbol, State* next);
    State* getNextState(char symbol);
private:
    std::string name;
    bool is_final;
    std::map<char, State*> transitions;
};


class FSM {
public:
    FSM(State* start_state) : current_state(start_state) {}
    void addState(State* state) { states[state->getName()] = state; }
    void addTransition(std::string current_state_name, char symbol, std::string next_state_name);
    void setState(std::string state_name) { current_state = states[state_name]; }
    bool process(std::string input);
private:
    State* current_state;
    std::map<std::string, State*> states;
};

void State::addTransition(char symbol, State* next) {
    transitions[symbol] = next;
}

State* State::getNextState(char symbol) {
    if (transitions.find(symbol) != transitions.end()) {
        return transitions[symbol];
    }
    else {
        return nullptr;
    }
}

void FSM::addTransition(std::string current_state_name, char symbol, std::string next_state_name) {
    State* current_state = states[current_state_name];
    State* next_state = states[next_state_name];
    current_state->addTransition(symbol, next_state);
}

bool FSM::process(std::string input) {
    for (char symbol : input) {
        State* next_state = current_state->getNextState(symbol);
        if (next_state == nullptr) {
            return false;
        }
        else {
            current_state = next_state;
        }
    }
    return current_state->isFinal();
}