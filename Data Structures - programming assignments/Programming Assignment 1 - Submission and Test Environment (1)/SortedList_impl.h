#ifndef SORTED_LIST_IMPL_H
#define SORTED_LIST_IMPL_H

template<class T>
SortedListNode<T>::SortedListNode(T* itemIn,
                                  SortedListNode* nextNodeIn,
                                  SortedListNode* prevNodeIn)
    : item(itemIn)
    , next(nextNodeIn)
    , prev(prevNodeIn)
{}

template<class T>
SortedList<T>::SortedList()
    : head(NULL)
    , back(NULL)
{}

template<class T>
SortedList<T>::SortedList(const SortedList& other)
    : head(NULL)
    , back(NULL)
{
    if(other.head == NULL)
    {
        return;
    }
    SortedListNode<T>*curr;
    SortedListNode<T>*temp;
    
    T* new_item = new T;
    *new_item = *other.head->item;
    head = new SortedListNode<T>(new_item,NULL,NULL);
    back = head;
    
    curr = other.head ->next;
    temp = head;
    while(curr)
    {
        new_item = new T;
        *new_item = *(curr->item);
        temp->next = new SortedListNode<T>(new_item,NULL,temp);
        temp = temp->next;
        back = temp;
        curr = curr->next;
    }
    // TODO: Implement
}

template<class T>
SortedList<T>& SortedList<T>::operator=(const SortedList& other)
{
    if (this == &other) return *this;
    
    SortedListNode<T>*curr = head;
    SortedListNode<T>*temp;
    while(curr!=NULL)
    {
        temp = curr->next;
        delete curr->item;
        delete curr;
        curr = temp;
    }
    head = back = NULL;
    
    if(other.head == NULL)
    {
        return *this;
    }
    T* new_item = new T;
    *new_item = *other.head->item;
    head = new SortedListNode<T>(new_item,NULL,NULL);
    back = head;
    
    curr = other.head ->next;
    temp = head;
    while(curr)
    {
        new_item = new T;
        *new_item = *(curr->item);
        temp->next = new SortedListNode<T>(new_item,NULL,temp);
        temp = temp->next;
        back = temp;
        curr = curr->next;
    }
    
    
    // TODO: Implement
    return *this;
}

template<class T>
SortedList<T>::~SortedList()
{
    SortedListNode<T>*curr = head;
    SortedListNode<T>*temp;
    while(curr!=NULL)
    {
        temp = curr->next;
        delete curr->item;
        delete curr;
        curr = temp;
    }
    head = back = NULL;
    // TODO: Implement
}

template<class T>
void SortedList<T>::InsertItem(T* i)
{
    if(head == NULL)
    {
        head = new SortedListNode<T>(i,NULL,NULL);
        back = head;
        return;
    }
    
    SortedListNode<T>* curr;
    
    if(*i < *(head->item))
    {
        curr = new SortedListNode<T>(i,head,NULL);
        head = curr;
        head->next->prev = head;
        return;
    }
    
    curr = head;
    while(curr->next != NULL && *(curr->next->item) < *i )
    {
        curr = curr->next;
    }
    
    if(curr->next == NULL)
    {
         SortedListNode<T>* temp = new SortedListNode<T>(i,NULL,curr);
         curr->next = temp;
         back = temp;
         return;
    }
    
    if(*(curr->next->item) == *i )
    {
        while(curr->next != NULL && *(curr->next->item) == *i)
        {
            curr = curr->next;
        }
    }
    
    if(curr->next == NULL)
    {
         SortedListNode<T>* temp = new SortedListNode<T>(i,NULL,curr);
         curr->next = temp;
         back = temp;
         return;
    }
    
    SortedListNode<T>* temp = new SortedListNode<T>(i,curr->next,curr);
    curr->next = temp;
    temp->next->prev = temp;
    return;
}


template<class T>
void SortedList<T>::InsertItemPrior(T* i)
{
    if(head == NULL)
    {
        head = new SortedListNode<T>(i,NULL,NULL);
        back = head;
        return;
    }
    
    SortedListNode<T>* curr;
    
    if(*i < *(head->item)||*i == *(head->item))
    {
        curr = new SortedListNode<T>(i,head,NULL);
        head = curr;
        head->next->prev = head;
        return;
    }
    
    curr = head;
    while(curr->next != NULL && *(curr->next->item) < *i )
    {
        curr = curr->next;
    }
    
    if(curr->next == NULL)
    {
         SortedListNode<T>* temp = new SortedListNode<T>(i,NULL,curr);
         curr->next = temp;
         back = temp;
         return;
    }
    
    SortedListNode<T>* temp = new SortedListNode<T>(i,curr->next,curr);
    curr->next = temp;
    temp->next->prev = temp;
    return;
    // TODO: Implement
}

template<class T>
T* SortedList<T>::RemoveFirstItem()
{
    if(head==NULL)
    {
        return NULL;
    }
    
    SortedListNode<T>*node_to_remove = head;
    head = head->next;
    if(head)
    {
        head->prev = NULL;
    }
    else
    {
        back = NULL;
    }
    
    T* item_to_return = node_to_remove->item;
    delete node_to_remove;
    return item_to_return;
}

template<class T>
T* SortedList<T>::RemoveFirstItem(int priority)
{
    if(head==NULL)
    {
        return NULL;
    }
    SortedListNode<T>*curr = head;
    while(curr!= NULL && !(*(curr->item) == priority))
    {
        curr = curr->next;
    }
    
    
    if(curr==NULL)
    {
        return NULL;
    }
    
    T* item_to_return = curr->item;
    
    if(curr->next == NULL && curr->prev == NULL)
    {
        delete curr;
        head = back = NULL;
        return item_to_return;
    }
    if(curr->next == NULL)
    {
        SortedListNode<T>*temp = curr->prev;
        temp->next = NULL;
        back = temp;
        delete curr;
        return item_to_return;
    }
    if(curr->prev == NULL)
    {
        head = head->next;
        head->prev = NULL;
        delete curr;
        return item_to_return;
    }
    
    SortedListNode<T>*temp = curr->prev;
    temp->next = curr->next;
    temp->next->prev = temp;
    delete curr;
    return item_to_return;
    
}

template<class T>
T* SortedList<T>::RemoveLastItem(int priority)
{
    if(head==NULL)
    {
        return NULL;
    }
    
    SortedListNode<T>*curr = head;
    SortedListNode<T>*node_to_remove = NULL;
    
    while(curr!=NULL)
    {
        if(*curr->item == priority)
        {
            node_to_remove = curr;
        }
        curr=curr->next;
    }
    
    if(node_to_remove==NULL)
    {
        return NULL;
    }
    
    T* item_to_return = node_to_remove->item;
    
    if(node_to_remove->next == NULL && node_to_remove->prev == NULL)
    {
        delete node_to_remove;
        head = back = NULL;
        return item_to_return;
    }
    if(node_to_remove->next == NULL)
    {
        SortedListNode<T>*temp = node_to_remove->prev;
        temp->next = NULL;
        back = temp;
        delete node_to_remove;
        return item_to_return;
    }
    if(node_to_remove->prev == NULL)
    {
        head = head->next;
        head->prev = NULL;
        delete node_to_remove;
        return item_to_return;
    }
    
    SortedListNode<T>*temp = node_to_remove->prev;
    temp->next = node_to_remove->next;
    temp->next->prev = temp;
    delete node_to_remove;
    return item_to_return;
}

template<class T>
const T* SortedList<T>::FirstItem() const
{
    return (head) ? head->item : NULL;
}

template<class T>
const T* SortedList<T>::LastItem() const
{
    return (back) ? back->item : NULL;
}

template<class T>
bool SortedList<T>::IsEmpty() const
{
    return head == NULL;
}
/*
template<class T>
void SortedList<T>::ChangePriorityOf(int priority, int newPriority)
{
    if(head == NULL)
    {
        return;
    }
    SortedListNode<T> *curr = head;
    
    while(curr!=NULL)
    {
        if(*(curr->item) == priority)
        {
            SortedListNode<T> *Node_to_change;
            Node_to_change = curr;
            curr = curr->next;
            if(Node_to_change->prev == NULL && Node_to_change->next == NULL)
            {
                (Node_to_change->item)->setPriority(newPriority);
                return;
            }
            if(Node_to_change->prev == NULL)
            {
                head = head->next;
                head->prev = NULL;
            }
            if(Node_to_change->next == NULL)
            {
                back = back->prev;
                back->next = NULL;
            }
            if(Node_to_change->next != NULL && Node_to_change->prev != NULL)
            {
                Node_to_change->prev->next = Node_to_change->next;
                Node_to_change->next->prev = Node_to_change->prev;
            
                //prioritysi değişecek olan nodeu listeden çıkardık
                //node unu silip insert item olarak geri eklicez
            
                (Node_to_change->item)->setPriority(newPriority);
                InsertItem(Node_to_change->item);
                delete Node_to_change;
            }
        }
        else
        {
            curr = curr->next;
        }
    }
    // TODO: Implement
}
*/

template<class T>
void SortedList<T>::ChangePriorityOf(int priority, int newPriority)
{
    if(head == NULL)
    {
        return;
    }
    
    SortedListNode<T> *curr = head;
    
    if(newPriority>priority)
    {
        int count = 0;
        while(curr!=NULL)
        {
            if(*curr->item == priority)
            {
                count++;
            }
            curr = curr->next;
        }
        if(count!=0)
        {
            T*item_to_insert;
            for(int i =0;i<count;i++)
            {
                item_to_insert = RemoveLastItem(priority);
                item_to_insert->setPriority(newPriority);
                InsertItemPrior(item_to_insert);
            }
        }
    }
    else
    {
        int count = 0;
        while(curr!=NULL)
        {
            if(*curr->item == priority)
            {
                count++;
            }
            curr = curr->next;
        }
        if(count!=0)
        {
            T*item_to_insert;
            for(int i =0;i<count;i++)
            {
                item_to_insert = RemoveFirstItem(priority);
                item_to_insert->setPriority(newPriority);
                InsertItem(item_to_insert);
            }
        }
    }
}    

template<class T>
void SortedList<T>::Split(SortedList& listLeft,
                          SortedList& listRight,
                          int priority)
{
    assert(listLeft.head == NULL);
    assert(listRight.head == NULL);
    
    if(head == NULL)
    {
        return;
    }
    SortedListNode<T> *curr = head;
    while(curr!=NULL && *(curr->item)<priority)
    {
        curr = curr->next;
    }
    //tüm priorityler daha küçükse sadece leftlist olacak
    if(curr==NULL)
    {
        listLeft.head = head;
        listLeft.back = back;
        head = back = NULL;
        return;
    }
    //tüm priorityler daha büyükse sadece rightlist olacak
    if(curr == head)
    {
        listRight.head = head;
        listRight.back = back;
        head = back = NULL;
        return;
    }
    //ortadan bölünüyorsa curr rigtlistin başladığı node u point eder
    //curr pointerının bir öncesine kadar leftlist
    
    curr->prev->next = NULL;
    curr->prev = NULL;
    listLeft.head = head;
    listRight.head = curr;
    listRight.back = back;
    
    curr = listLeft.head;
    if(curr->next == NULL)
    {
        listLeft.back = curr;
    }
    while(curr->next != NULL)
    {
        curr = curr->next;
    }
    listLeft.back = curr;
    
    head = back =  NULL;
    // TODO: Implement
}

template<class T>
SortedList<T> SortedList<T>::Merge(const SortedList& list0,
                                   const SortedList& list1)
{
   SortedList<T> merged;
   merged = list0;
   
   SortedListNode<T> *curr = list1.head;
   while(curr)
   {
       T*item_to_insert = new T;
       *item_to_insert = *(curr->item);
       merged.InsertItem(item_to_insert);
       
       curr = curr->next;
   }
   
   return merged;
}

#endif

























