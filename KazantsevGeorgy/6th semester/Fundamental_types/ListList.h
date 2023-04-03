#include "LinkedListNode.h"


template <typename Q>
class LinkedList
{
public:
    LinkedList();
    ~LinkedList();

    void PushBack(Q value);
    void PopBack();
    template <typename R>friend std::ostream& operator <<(std::ostream& ostr, const LinkedList<R>& rhs);
    void Clear();
    double Front();
    double Back();
    bool Find(Q value);
    bool Empty();
private:
    LinkedListNode<Q>* Head;
};

