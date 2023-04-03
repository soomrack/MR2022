#ifndef ATD_DYNAMIC_ARRAY_H
#define ATD_DYNAMIC_ARRAY_H

//#define DEBUG

//using try/catch for working with this class


class dynamic_array
{
private:
    unsigned size;
    int* data;
public:
    unsigned buf_size;
    unsigned filled_size;

    inline dynamic_array();
    dynamic_array(const unsigned size, unsigned buf_size = 50);
    dynamic_array(const dynamic_array &other);
    dynamic_array(dynamic_array &&other);

    dynamic_array& operator=(const dynamic_array &other);
    bool operator==(const dynamic_array& other);
    bool operator!=(dynamic_array& other);
    int& operator[](unsigned idx);
    void resize(unsigned new_size);

    //resize #TODO
    dynamic_array& resize();
    int find(int element);  // return index first equal element
    void fill_random(int MAX_RANDOM_VALUE=100);
    void push_back(const int value); // del it #TODO
    void pop_back();  // del it #TODO

    void show();
    int get_size();

    ~dynamic_array();

};


#endif //ATD_DYNAMIC_ARRAY_H
