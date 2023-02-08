#include <iostream>

using namespace std;
typedef struct {  // Задание поля "данные"
    int hours;
    int minutes;
} Data;


typedef struct tag{
    Data data;
    struct tag* next;
}Object;

Object* top = NULL;  // Стек пустой


Object* push(Data data){
    Object* ptr = new Object;
    ptr->data = data;
    ptr->next = top;
    top = ptr;
    return ptr;
}

void pop(){
    if(top == NULL) return;
    Object * ptr = top->next;
    delete top;
    top = ptr;
}


void print(){
    Object * ptr = top;
    while(ptr != NULL){
        cout << ptr->data.hours << ":" << ptr->data.minutes << endl;
        ptr = ptr->next;
    }
}


int main() {
    int quanity = 5;
    int hour, minute;
    for(int i = 0; i < quanity; i ++){
        Data data = {rand()%25,rand()%61};
        push(data);
   }
    print();
    cout << "print new hour";
    cin >> hour;
    cout << "print new minutes";
    cin >> minute;
    push({hour,minute});
    print();
    pop();
    return 0;
}