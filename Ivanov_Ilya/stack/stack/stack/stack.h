#ifndef MR2022_stack
#define MR2022_stack
#include "iostream"
#define MAX_SIZE 500
class stack_error : public std::domain_error{
    public:
    stack_error(const char* const message): std:: domain_error(message){}
};

stack_error overflowed("stack is overflowed");
stack_error empty("Stack is empty");
class stack {
private:
int current_size;
int top;
int data[MAX_SIZE];
public:
stack();
~stack();
void push(int x);
int pop();
void print();
unsigned int get_size();
bool is_full();
bool is_empty();
};

stack::stack(){
    current_size = 0;
    top = -1;
}
bool stack::is_full() {
    return top == MAX_SIZE - 1;
}
bool stack::is_empty() {
    return top == -1;
}
void stack::push(int x){
    if(current_size == MAX_SIZE) throw overflowed;
    top++;
    current_size++;
    data[top]=x;
}
int stack::pop(){
    if(current_size == 0) throw empty;
    current_size--;
    return data[top--];
}
stack::~stack(){
    while(current_size){
        pop();
    }

}
void stack::print(){
    for(int i=0; i<current_size;i++){
        std::cout << data[i] << "\n";
    }
}
unsigned int stack::get_size() {
    if (is_empty()) throw empty;
        return current_size;
}
#endif //MR2022_stack
