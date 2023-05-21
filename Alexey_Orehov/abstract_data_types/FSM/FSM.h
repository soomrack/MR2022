#ifndef PROGRAMMING_FSM_H
#define PROGRAMMING_FSM_H

#include <functional>
#include <utility>
#include <string>
#include "graph.h"


class State {
    friend std::hash<State>;
    friend class Game;
private:
    std::string description;
    std::function<void(Game*)> action;

public:
    State(const char* description, std::function<void(Game*)>);

    bool operator==(const State& other) const { return description == other.description; }

    bool operator<(const State& other) {
        return this->description < other.description;
    }

    State(const State& state);
};


namespace std {
    template <>
    struct hash<State> {
        size_t operator()(const State& state) const noexcept
        {
            return hash<string>()(state.description);
        }
    };
}


class Game: public graph::Graph<State> {
public:
    unsigned short health = 100;
    bool armor = false;
    unsigned int money = 10;

public:
    void play(const State& start_state);

    void print_stats() const;
};


State::State(const char *description, std::function<void(Game*)> action) : description(description),
                                                                            action(std::move(action)) {}

State::State(const State& state) {
    description = state.description;
    action = state.action;
}

void Game::print_stats() const {
    std::cout << "You now have " << health << " health, " << money << " money and " <<  (armor ? "":"no") << " armor\n";
}

void Game::play(const State& start_state) {
    auto current_state = start_state;
    auto current_state_neighbours = vertices[current_state]->neighbours;

    while (!current_state_neighbours.empty()) {
        int choice = 1;
        if (health <= 0) {
            std::cout << "Game over" << std::endl;
            return;
        }
        current_state.action(this);
        if (current_state_neighbours.size() != 1) {
            std::cout << "====================================" << std::endl;

            std::cout << "Your path has split, choose what to do next" << std::endl;
            int counter = 1;
            for (auto &el: current_state_neighbours) {
                std::cout << counter++ << " - " << el.second->value.description << std::endl;
            }
            std::cin >> choice;
            while (!(choice > 0 && choice < current_state_neighbours.size() + 1)) {
                std::cout << "\nChoice incorrect, use only suggested options";
                std::cin >> choice;
            }
        }
        int counter = 1;
        for (auto &el: current_state_neighbours) {
            if (counter++ == choice) {
                current_state = el.second->value;
                current_state_neighbours = el.second->neighbours;
                break;
            }
        }
    }
}

#endif //PROGRAMMING_FSM_H
