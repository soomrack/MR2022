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
    T *data;

public:
    unsigned int cache_size = 0;

    explicit DArray(std::list<T> in_list, int new_cache_size = 5); // заполнение массива значениями из массива при создании
    ~DArray() noexcept;
    unsigned int get_size() const;
    void resize(unsigned int new_size);

    T& operator[] (unsigned int idx);
};


#endif //MR2022_DARRAY_H
