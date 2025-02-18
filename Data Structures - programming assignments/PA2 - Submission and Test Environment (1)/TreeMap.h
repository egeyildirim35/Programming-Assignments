#ifndef TREEMAP_H
#define TREEMAP_H

#include <iostream>
#include <vector>

#include "KeyValuePair.h"
#include "DSWTree.h"

template<class K, class V>
class TreeMap {
public: // DO NOT CHANGE THIS PART.
    TreeMap();

    void clear();

    const V &get(const K &key) const;

    V &operator[](const K &key) const;

    void put(const K &key, const V &value);

    bool containsKey(const K &key); // Declaration of the new method

    bool deletekey(const K &key); // Declaration of the new method

    const KeyValuePair<K, V> &ceilingEntry(const K &key);

    const KeyValuePair<K, V> &firstEntry();

    const KeyValuePair<K, V> &lastEntry();

    std::vector<KeyValuePair<K, V> > subMap(K fromKey, K toKey) const;

    void print() const;

    int size();

    void balance();

private: // YOU MAY ADD YOUR OWN UTILITY MEMBER FUNCTIONS HERE.

private: // DO NOT CHANGE THIS PART.
    DSWTree<KeyValuePair<K, V> > stree;

};

template<class K, class V>
TreeMap<K, V>::TreeMap() {}

template<class K, class V>
void TreeMap<K, V>::clear() {
    stree.removeAllNodes();
    /* TODO */
}

template<class K, class V>
const V &TreeMap<K, V>::get(const K &key) const 
{
    if(stree.isEmpty()) throw NoSuchItemException();
    
    KeyValuePair<K, V> myPair(key, V());
    try
    {
        return stree.get(myPair).getValue();
        
    }
    catch(NoSuchItemException)
    {
        throw NoSuchItemException();
    }
}
/*
template<class K, class V>
const V &TreeMap<K, V>::get(const K &key,Node<KeyValuePair<K, V> >*& node) const {
    if(node == NULL) throw NoSuchItemException();
    if(node->element.key == key) return node->element.value;
    else if (node->element.key > key) return get(key,node->left);
    else if (node->element.key < key) return get(key,node->right);
}
*/
template<class K, class V>
const KeyValuePair<K, V> &TreeMap<K, V>::ceilingEntry(const K &key) {
    const KeyValuePair<K, V> myPair(key,V());
    try
    {
        return stree.getCeiling(myPair);
    }
    catch(NoSuchItemException)
    {
        throw NoSuchItemException();
    }
    
    
    /* TODO */
}

template<class K, class V>
const KeyValuePair<K, V> &TreeMap<K, V>::firstEntry() 
{
    if(stree.isEmpty()) throw NoSuchItemException();
    
    try
    {
        return stree.getMin();
        
    }
    catch(NoSuchItemException)
    {
        throw NoSuchItemException();
    }
    
    /* TODO */
}

template<class K, class V>
const KeyValuePair<K, V> &TreeMap<K, V>::lastEntry() 
{
    if(stree.isEmpty()) throw NoSuchItemException();
    
    try
    {
        return stree.getMax();
        
    }
    catch(NoSuchItemException)
    {
        throw NoSuchItemException();
    }
    /* TODO */
}
template<class K, class V>
std::vector<KeyValuePair<K, V> > TreeMap<K, V>::subMap(K fromKey, K toKey) const 
{
    
    std::vector<KeyValuePair<K, V> > subVector;
    try 
    {
        KeyValuePair<K, V> currentPair = stree.get(KeyValuePair<K, V>(fromKey, V()));
        subVector.push_back(currentPair);
        
        while (stree.getNext(currentPair) <= toKey) 
        {
            currentPair = stree.getNext(currentPair);
            subVector.push_back(currentPair);
        }
    } 
    catch (NoSuchItemException&)
    {
        return subVector;
    }
    return subVector;
    
/* TODO */
}

template<class K, class V>
void TreeMap<K, V>::print() const {

    std::cout << "# Printing the tree map ..." << std::endl;

    std::cout << "# DSWTree<KeyValuePair<K, V> > stree:" << std::endl;
    stree.printPretty();

    std::cout << "# Printing is done." << std::endl;
}

template<class K, class V>
void TreeMap<K, V>::put(const K &key, const V &value) 
{
    if(containsKey(key))
    {
        KeyValuePair<K, V> newPair(key, value);
        const KeyValuePair<K, V> & already_exist = stree.get(newPair);
        KeyValuePair<K, V>& not_const_existing_pair = const_cast<KeyValuePair<K, V>&>(already_exist);
        not_const_existing_pair.setValue(value);
    }
    else
    {
        KeyValuePair<K, V> new_pair(key, value);
        stree.insert(new_pair);
    }
    /* TODO */
}

template<class K, class V>
V& TreeMap<K, V>::operator[](const K &key) const 
{   
    try
    {
        const V& const_value = get(key);
        return const_cast<V &>(const_value);
    }
    catch(NoSuchItemException)
    {
        throw NoSuchItemException();
    }
    /* TODO */
}

template<class K, class V>
bool TreeMap<K, V>::deletekey(const K &key) 
{
    const KeyValuePair<K, V> myPair(key,V());
    if(stree.remove(myPair)) return true;
    else return false;
    
    /* TODO */
}
template<class K, class V>
bool TreeMap<K, V>::containsKey(const K &key) 
{
    try 
    {
        const V value = get(key);
        return true;
        
    } 
    catch (NoSuchItemException) 
    {
        return false;
    }
    /* TODO */
}

template<class K, class V>
void TreeMap<K, V>::balance() {
    stree.balance();
    /* TODO */
}

#endif //TREEMAP_H
