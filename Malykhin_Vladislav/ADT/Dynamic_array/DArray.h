#ifndef MR2022_DARRAY_H
#define MR2022_DARRAY_H

#include <iostream>
#include <list>
#include <iterator>

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
    unsigned int cache_size = 0;
    T *data;
public:
    explicit DArray(std::list<T> in_list, int new_cache_size = 5); // заполнение массива значениями из массива при создании
    ~DArray() noexcept;
    T& operator[] (int idx);
    unsigned int get_size() const;
    T get(unsigned int id) const;
    void resize(unsigned int new_size);
    void print() const;

};


#endif //MR2022_DARRAY_H
