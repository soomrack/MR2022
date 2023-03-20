#ifndef ATD_DYNAMIC_ARRAY_H
#define ATD_DYNAMIC_ARRAY_H

//#define DEBUG

//using try/catch for working with this class


class dynamic_array
{
private:
    int size; // unsignint
    int* data;
public:
    int buf_size;

    dynamic_array();
    dynamic_array(const int size);
    dynamic_array(const dynamic_array &other);
    dynamic_array(dynamic_array &&other);

    dynamic_array& operator=(const dynamic_array &other);
    bool operator==(const dynamic_array& other);
    bool operator!=(dynamic_array& other);
    int& operator[](int idx);

    //resize #TODO
    int find(int element);  // return index first equal element
    void fill_random(int MAX_RANDOM_VALUE=100);
    void push_back(const int value); // del it #TODO
    void pop_back();  // del it #TODO

    void show();
    int get_size();

    ~dynamic_array();

};


#endif //ATD_DYNAMIC_ARRAY_H
