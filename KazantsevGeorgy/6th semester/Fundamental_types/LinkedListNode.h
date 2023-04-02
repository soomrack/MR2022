

template <typename Q>
class LinkedListNode
{
public:
    LinkedListNode(Q value,
                   LinkedListNode<Q>* previos = nullptr,
                   LinkedListNode<Q>* next = nullptr);

    Q Data;
    LinkedListNode* Previos;
    LinkedListNode* Next;
};



