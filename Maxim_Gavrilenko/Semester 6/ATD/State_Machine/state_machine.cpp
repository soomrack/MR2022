#include "graph.h"
#include <iostream>
// Создаем автомат для распознавания языка из нулей и единиц, в котором
// четное количество единиц подряд дает результат true, а нечетное - false
int main(){
FiniteStateMachine<double> fsm;
fsm.add_state(0, true); // начальное состояние
fsm.add_state(1, false);
// Добавляем все возможные переходы
fsm.add_transition(0, 0, "0");
fsm.add_transition(0, 1, "1");
fsm.add_transition(1, 1, "1");
fsm.add_transition(1, 0, "0");

std::string input1 = "0010011";
std::cout << fsm.process_input(input1) << std::endl; // Output: true

std::string input2 = "0111101";
std::cout << fsm.process_input(input2) << std::endl; // Output: false

fsm.reset(); // Сброс автомата
std::string input3 = "010101";
std::cout << fsm.process_input(input3) << std::endl; // Output: true
}