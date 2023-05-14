#include <iostream>
#include <map>
#include <string>

class State {
private:
    std::string name;
    bool final;
    std::map<char, State*> transitions;
public:
    State(std::string name, bool is_final = false) : name(name), final(final) {}
    std::string get_name();
    bool is_final();
    void add_transition(char symbol, State* next);
    State* get_next_state(char symbol);
};


std::string State:: get_name(){
    return name;
}

bool State:: is_final() {
    return final;
}


void State::add_transition(char symbol, State* next) {
    transitions[symbol] = next;
}

State* State::get_next_state(char symbol) {
    if (transitions.find(symbol) != transitions.end()) {
        return transitions[symbol];
    }
    else {
        return nullptr;
    }
}


class FSN {
private:
    State* current_state;
    std::map<std::string, State*> states;
public:
    FSN(State* start_state) : current_state(start_state) {}
    void add_state(State* state);
    void add_transition(std::string current_state_name, char symbol, std::string next_state_name);
    void set_state(std::string state_name);
    bool process(std::string input);

};

void FSN:: add_state(State* state) {
    states[state->get_name()] = state;
}


void FSN::add_transition(std::string current_state_name, char symbol, std::string next_state_name) {
    State* current_state = states[current_state_name];
    State* next_state = states[next_state_name];
    current_state->add_transition(symbol, next_state);
}


bool FSN::process(std::string input) {
    for (char symbol : input) {
        State* next_state = current_state->get_next_state(symbol);
        if (next_state == nullptr) {
            return false;
        }
        else {
            current_state = next_state;
        }
    }
    return current_state->is_final();
}

void FSN:: set_state(std::string state_name){
    current_state = states[state_name];
}

int main() {

    return 0;
}

