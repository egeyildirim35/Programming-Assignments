#ifndef FCFS_LIST_IMPL_H
#define FCFS_LIST_IMPL_H

template<class T>
FCFSNode<T>:: FCFSNode(const T& t, FCFSNode* node)
    : item(t)
    , next(node)
{}

// ============================ //
template<class T>
FCFSList<T>::FCFSList()
    : head(NULL)
{
    // Using a dummy node
    head = new FCFSNode<T>(T());
}

template<class T>
FCFSList<T>::FCFSList(const FCFSList& other)
{
    head = head = new FCFSNode<T>(T());
    *this = other;
    
    // TODO: Implement
}

template<class T>
FCFSList<T>& FCFSList<T>::operator=(const FCFSList& other)
{
    if (this == &other) return *this;

    FCFSNode<T> *curr = head->next;
    if(curr != NULL)
    {
        FCFSNode<T> * temp;
        while(curr != NULL)
        {
            temp = curr->next;
            delete curr;
            curr = temp;
        }
        head->next = NULL;
    }
    //eski liste elemanlarını sildim ve dommy node null gösteriyo
    curr = other.head->next;
    while(curr)
    {
        Enqueue(curr->item);
        curr = curr->next;
    }
    return *this;
}

template<class T>
FCFSList<T>::~FCFSList()
{
    if(head->next == NULL)
    {
        delete head;
        return;
    }
     FCFSNode<T> * curr = head;
     FCFSNode<T> * temp;
     while(curr)
     {
         temp = curr->next;
         delete curr;
         curr = temp;
     }
    // TODO: Implement
}

template<class T>
void FCFSList<T>::Enqueue(const T& item)
{
    FCFSNode<T> * curr = head;
    while(curr->next != NULL)
    {
        curr = curr->next;
    }
    
    curr->next = new FCFSNode<T>(item,NULL);
    // TODO: Implement
}

template<class T>
T FCFSList<T>::Dequeue()
{
    if(head->next == NULL)
    {
        return T();
    }
    FCFSNode<T> *curr = head->next;
    head->next = curr->next;
    T temp = curr->item;
    delete curr;
    
    // TODO: Implement
    return T(temp);
}
template<class T>
bool FCFSList<T>::is_empty()
{
    if(head->next==NULL)
    {
        return true;
    }
    else
    {
        return false;
    }
}














#endif