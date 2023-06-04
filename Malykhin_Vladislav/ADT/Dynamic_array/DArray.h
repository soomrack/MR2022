#ifndef MR2022_DARRAY_H
#define MR2022_DARRAY_H

#include <iostream>
#include <list>
#include <iterator>
#include <cmath>

/* добавить кеш (не занятую память для последующего расширения, как новый аргумент класса), CHECK
 заменить вектор на какое-нибудь заполнение из списка (зачем нужен наш класс, если есть вектор?), CHECK
 удалить не нужный buffer, копировать напрямую в "нововыделенную" память, CHECK
 можно перегрузить квадратные скобочки, CHECK
 можно выкинуть исключения CHECK
 */


template<typename T>
class DArray {
protected:
    unsigned int size;
    T *data;
    unsigned int default_cache = 5;
    unsigned int real_cache = 5;

public:


    void set_default_cache_size (unsigned int new_size);
    unsigned int get_default_cache_size() const;
    //get_reserved, get_capacity
    unsigned int get_reserved() const;
    unsigned int get_capacity() const;
    explicit DArray(std::list<T> in_list, int new_cache_size = -1); // заполнение массива значениями из массива при создании
    ~DArray() noexcept;
    unsigned int get_size() const;
    void resize(unsigned int new_size);

    T& operator[] (unsigned int idx);
};


#endif //MR2022_DARRAY_H
