#ifndef DSWTREE_H
#define DSWTREE_H

#include <iostream>
#include <cmath>

#include "Node.h"
#include "NoSuchItemException.h"

enum TraversalMethod {preorder, inorder, postorder};

template<class T>
class DSWTree {
public: // DO NOT CHANGE THIS PART.
    DSWTree();

    DSWTree(const DSWTree<T> &obj);

    ~DSWTree();

    bool isEmpty() const;

    int getHeight() const;
    
    const int getNodeHeight(const T& element) const;

    int getSize() const;

    bool insert(const T &element);

    bool remove(const T &element);

    void removeAllNodes();

    const T &get(const T &element) const;

    void print(TraversalMethod tp=inorder) const;

    void printPretty() const;

    DSWTree<T> &operator=(const DSWTree<T> &rhs);

    bool isBalanced();

    void balance();

    void createBackbone(Node<T> *&root);

    void createCompleteTree(Node<T> *&root, int size);

    const T &getCeiling(const T &element) const;

    const T &getFloor(const T &element) const;

    const T &getMin() const;

    const T &getMax() const;

    const T &getNext(const T &element) const;

private: // YOU MAY ADD YOUR OWN UTILITY MEMBER FUNCTIONS HERE.
    int getSize(Node<T> *node)const;
    bool insert(Node<T> *&node,const T &element);
    void helper_insert(Node<T> *&node,Node<T>* const other_node);
    void height_correcter(Node<T> *node);
    bool remove(Node<T> *&node,const T &element);
    const T& getCeiling(Node<T> * const node,const T &element) const;
    const T& getFloor(Node<T> * const node,const T &element) const;
    const T& getMin(Node<T> * const node) const;
    const T& getMax(Node<T> * const node) const;
    const T& get(Node<T> * const node,const T &element) const;
    void removeAllNodes(Node<T> * node);
    void print(Node<T> *node, TraversalMethod tp) const;
    void printPretty(Node<T> *node, int indentLevel, bool isLeftChild) const;
    const T& getNext(Node<T> *node,const T &element) const;
    const Node<T>* NodeFinder(const Node<T> *node, const T &element) const;
    void RightRotation(Node<T> *&temp, Node<T>*& prev);
    void LeftRotation(Node<T> *&temp, Node<T>*& prev);
    void updateAllHeights(Node<T> *node);
    bool isBalanced(Node<T> *root);
    

private: // DO NOT CHANGE THIS PART.
    Node<T> *root;
};

template<class T>
DSWTree<T>::DSWTree() {
    root = NULL;
    /* TODO */
}

template<class T>
DSWTree<T>::DSWTree(const DSWTree<T> &obj) {
    root = NULL;
    *this = obj;
}

template<class T>
DSWTree<T>::~DSWTree() {
    removeAllNodes();
    root = NULL;
    /* TODO */
}

template<class T>
bool DSWTree<T>::isEmpty() const {
    return(root==NULL)? true : false ; 
    /* TODO */
}

template<class T>
int DSWTree<T>::getHeight() const {
    if(root == NULL)
    {
        return -1;
    }
    return root->height;
    
    /* TODO */
}

template<class T>
int DSWTree<T>::getSize() const {
    int size = getSize(root);
    return size;
    /* TODO */
}
template<class T>
int DSWTree<T>::getSize(Node<T> *node)const{
    if(node == NULL) return 0;
    else if(node->left == NULL && node->right == NULL) return 1;
    else
    {
        return (1+getSize(node->left)+getSize(node->right));
    }
    
    
}

template<class T>
void DSWTree<T>::height_correcter(Node<T> *node)
{
    if (node == NULL) 
    {
        return;
    }
    
    int lheight;
    int rheight;
    int max_height;
    
    if(node->left == NULL)
    {
        lheight = -1;
    }
    else
    {
        lheight = node->left->height;
    }
    // found the left subtree height
    if(node->right == NULL)
    {
        rheight = -1;
    }
    else
    {
        rheight = node->right->height;
    }
    //found the right suntree height
    
    if(lheight>rheight)
    {
        max_height = lheight;
    }
    else
    {
        max_height = rheight;
    }
    node->height = max_height+1;
    
}
template<class T>
bool DSWTree<T>::insert(const T &element) {
    return insert(root,element);
    
}

template<class T>
bool DSWTree<T>::insert(Node<T> *&node,const T &element)
{
    if(node == NULL)
    {
        node = new Node<T>(element,NULL,NULL,0);
        return true;
    }
    else if(node->element < element)
    {
        bool is_inserted = insert(node->right,element);
        if(is_inserted) height_correcter(node);
        return is_inserted;
        
    }
    else if(node->element > element)
    {
        bool is_inserted = insert(node->left,element);
        if(is_inserted) height_correcter(node);
        return is_inserted;
    }
    else
    {
        return false;
    }
    
}

template<class T>
bool DSWTree<T>::remove(const T &element) 
{
    return remove(root,element);
}
template<class T>
bool DSWTree<T>::remove(Node<T> *&node,const T &element) {
    
    if(node == NULL) return false;
    
    if(node->element == element)
    {
        if(node->left == NULL && node->right == NULL) //leaf node için
        {
            delete node;
            node = NULL;
        }
        else if(node->left!=NULL && node->right != NULL) // 2 çocuklu  node
        {
            const T rmin = getMin(node->right);
            node->element = rmin;
            remove(node->right,rmin);
        }
        else if(node->left != NULL && node->right == NULL)// sol çocuklu node
        {
            Node<T> *temp = node;
            node = node->left;
            delete temp;  
        }
        else if(node->left == NULL && node->right != NULL)//sağ çocuklu node
        {
            Node<T> * temp = node;
            node = node->right;
            delete temp;
        }
        height_correcter(node);
        return true;
        
    }
    else if(node->element > element) 
    {
        bool is_removed = remove(node->left,element);
        if(is_removed) height_correcter(node);
        return is_removed;
        
    }
    else if(node->element < element)
    {
        bool is_removed = remove(node->right,element);
        if(is_removed) height_correcter(node);
        return is_removed;
    }
    
}

template<class T>
void DSWTree<T>::removeAllNodes()
{
    if(root == NULL) return;
    removeAllNodes(root);
    root = NULL;
    /* TODO */
}

template<class T>
void DSWTree<T>::removeAllNodes(Node<T>* node) {
    if (node == NULL) return;
    removeAllNodes(node->left);
    removeAllNodes(node->right);
    delete node; 
}

template<class T>
const T &DSWTree<T>::get(const T &element) const {
    return get(root,element);
    
    /* TODO */
}
template<class T>
const T &DSWTree<T>::get(Node<T> * const node,const T &element) const {
    if(node == NULL )  throw  NoSuchItemException();
    if(node->element == element)
    {
        return node->element;
    }
    else if(node->element > element)
    {
        get(node->left,element);
    }
    else if(node->element < element)
    {
        get(node->right,element);
    }
    /* TODO */
}

template<class T>
void DSWTree<T>::print(TraversalMethod tp) const {

    if (tp == preorder) {
        if (isEmpty()) {
            // the tree is empty.
            std::cout << "BST_preorder{}" << std::endl;
            return;
        }

        // the tree is not empty.

        // recursively output the tree.
        std::cout << "BST_preorder{" << std::endl;
        print(root, tp);
        std::cout << std::endl << "}" << std::endl;
        /* TODO */
    } else if (tp == inorder) {
        // check if the tree is empty?
        if (isEmpty()) {
            // the tree is empty.
            std::cout << "BST_inorder{}" << std::endl;
            return;
        }

        // the tree is not empty.

        // recursively output the tree.
        std::cout << "BST_inorder{" << std::endl;
        print(root, tp);
        std::cout << std::endl << "}" << std::endl;
    } else if (tp == postorder) {
        if (isEmpty()) {
            // the tree is empty.
            std::cout << "BST_postorder{}" << std::endl;
            return;
        }

        // the tree is not empty.

        // recursively output the tree.
        std::cout << "BST_postorder{" << std::endl;
        print(root, tp);
        std::cout << std::endl << "}" << std::endl;
        /* TODO */

           }
}

template<class T>
void DSWTree<T>::print(Node<T> *node, TraversalMethod tp) const {
    if (node == NULL) return;
    if (tp == preorder) 
    {
        std::cout << "\t" << node->element;
        
        if (node->left) 
        {
            std::cout << "," << std::endl;
        }
        print(node->left, preorder);
        if (node->right) 
        {
            std::cout << "," << std::endl;
        }
        print(node->right, preorder);
        /* TODO */
    } else if (tp == inorder) {
        // check if the node is NULL?
        if (node == NULL)
            return;

        // first, output left subtree and comma (if needed).
        print(node->left, inorder);
        if (node->left) {
            std::cout << "," << std::endl;
        }

        // then, output the node.
        std::cout << "\t" << node->element;

        // finally, output comma (if needed) and the right subtree.
        if (node->right) {
            std::cout << "," << std::endl;
        }
        print(node->right, inorder);
    } 
    else if (tp == postorder) 
    {
        print(node->left, postorder);
        if (node->left) {
            std::cout << "," << std::endl;
        }
        print(node->right, postorder);
        if (node->right) {
            std::cout << "," << std::endl;
        }
        std::cout << "\t" << node->element;
        /* TODO */

    }
}

template<class T>
void DSWTree<T>::printPretty() const {

    // check if the tree is empty?
    if (isEmpty()) {
        // the tree is empty.
        std::cout << "BST_pretty{}" << std::endl;
        return;
    }

    // the tree is not empty.

    // recursively output the tree.
    std::cout << "BST_pretty{" << std::endl;
    printPretty(root, 0, false);
    std::cout << "}" << std::endl;

}

template<class T>
void DSWTree<T>::printPretty(Node<T> *node, int indentLevel, bool isLeftChild) const {

    // check if the node is NULL?
    if (node == NULL)
        return;

    // output the indentation and the node.
    std::cout << "\t";
    for (int i = 0; i < indentLevel; ++i) {
        std::cout << "---";
    }
    std::cout << (indentLevel == 0 ? "root:" : (isLeftChild ? "l:" : "r:")) << node->element << std::endl;

    // first, output left subtree with one more indentation level.
    printPretty(node->left, indentLevel + 1, true);

    // then, output right subtree with one more indentation level.
    printPretty(node->right, indentLevel + 1, false);
}

template<class T>
void DSWTree<T>::helper_insert(Node<T> *&node,Node<T>* const other_node)
{
    if (other_node == NULL) return;
    
    if(other_node->left)
    {
        node->left = new Node<T>(other_node->left->element,NULL,NULL,0);
        helper_insert(node->left,other_node->left);
        height_correcter(node);

        
    }
    if(other_node->right)
    {
        node->right = new Node<T>(other_node->right->element,NULL,NULL,0);
        helper_insert(node->right,other_node->right);
        height_correcter(node);
    }
    
}
template<class T>
DSWTree<T>& DSWTree<T>::operator=(const DSWTree<T>& rhs) {
    if (this == &rhs) return *this;  

    removeAllNodes(); 

    if (rhs.root == NULL) root = NULL;
    else 
    {
        root = new Node<T>(rhs.root->element, NULL, NULL, 0); 
        helper_insert(root, rhs.root);
    }

    return *this;
}
template <class T>
void DSWTree<T>::updateAllHeights(Node<T> *node) {
    if (node == NULL) return;

    updateAllHeights(node->left);
    updateAllHeights(node->right);
    
    height_correcter(node);
}

template <class T>
void DSWTree<T>::balance() {
    
    createBackbone(root);
    
    int NodeCount = 0;
    Node<T> * current = root;
    while(current)
    {
        NodeCount +=1;
        current = current->right;
    }
    
    createCompleteTree(root,NodeCount);
    updateAllHeights(root);
}
template <class T>
bool DSWTree<T>::isBalanced() 
{
    return isBalanced(root);
}

template <class T>
bool DSWTree<T>::isBalanced(Node<T> *root) 
{
    if(root==NULL) return true;
    int lefth;
    if(root->left) lefth = root->left->height;
    else lefth = -1;
    
    int righth;
    if(root->right) righth = root->right->height;
    else righth = -1;
    
    if((lefth-righth) > 1 || (lefth-righth) < -1 ) return false;
    
    return (isBalanced(root->left) && isBalanced(root->right));
    /* TODO */
}

template <class T>
void DSWTree<T>::RightRotation(Node<T> *&temp, Node<T>*& prev)
{
    Node<T>* RightOfLeft = temp->left->right;
    temp->left->right = temp;
    if(prev == NULL)
    {
        root = temp->left;
        temp->left = RightOfLeft;
        temp = root;
    }
    else
    {
        prev->right = temp->left;
        temp->left = RightOfLeft;
        temp = prev->right;
    }
    
}
template <class T>
void DSWTree<T>::LeftRotation(Node<T> *&temp, Node<T>*& prev)
{
    Node<T>* LeftOfRight = temp->right->left;
    temp->right->left = temp;
    if(prev == NULL)
    {
        root = temp->right;
        temp->right = LeftOfRight;
        temp = root;
    }
    else
    {
        prev->right = temp->right;
        temp->right = LeftOfRight;
        temp = prev->right;
    }
    
}
template <class T>

void DSWTree<T>::createBackbone(Node<T> *&root) {
    Node<T> * temp = root;
    Node<T> * prev = NULL;
    while(temp!= NULL)
    {
        if(temp->left)
        {
            RightRotation(temp,prev);
        }
        else
        {
            prev = temp;
            temp = temp->right;
        }
    }
    /* TODO */
}

template <class T>
void DSWTree<T>::createCompleteTree(Node<T> *&root, int size) {
    float logg = std::log(size + 1) / std::log(2.0);
    int h = logg + 0.001;
    int m = std::pow(2, h) - 1;
    Node<T> *temp = root;
    Node<T> *prev = NULL;

    for (int i = 0; i < size - m; i++) {
        LeftRotation(temp, prev);
        prev = temp;
        if(temp) temp = temp->right;
    }

    while (m > 1) {
        temp = root;
        prev = NULL;

        for (int i = 0; i < m/2; i++) {
            LeftRotation(temp, prev);
            if (temp) prev = temp;
            if(temp){ 
                temp = temp->right;
            }
        }
        m = m/2;
    }
}

template<class T>
const T &DSWTree<T>::getCeiling(const T &element) const {
    if (root == NULL) 
    {
        throw NoSuchItemException(); 
    }
    
    const T max_elem = getMax();
    if(element > max_elem)
    {
        throw NoSuchItemException(); 
    }
    
    return getCeiling(root, element);
}


template<class T>
const T &DSWTree<T>::getCeiling(Node<T> * const node, const T &element) const {
    if (node == NULL) {
        throw NoSuchItemException();
    }

    if (node->element == element) 
    {
        return node->element;
    } 
    
    else if (node->element < element) 
    {
        return getCeiling(node->right, element);
    } 
    
    else if(node->element > element)
    {
        const T& potential_item = node->element;
        try 
        {
            const T &item_to_compare = getCeiling(node->left, element);
            if(potential_item < item_to_compare)
            {
                return potential_item;
            }
            else 
            {
                return item_to_compare;
            }
        } 
        catch (NoSuchItemException&) 
        {
            return node->element;
        }
    }
}

template<class T>
const T &DSWTree<T>::getFloor(const T &element) const {
    if(root==NULL) 
    {
        throw NoSuchItemException();
    }
    
    const T min_elem = getMin();
    if(element < min_elem)
    {
        throw NoSuchItemException();
    }
    return getFloor(root, element);
}

template<class T>
const T &DSWTree<T>::getFloor(Node<T> * const node, const T &element) const {
    if (node == NULL) {
        throw NoSuchItemException();
    }

    if (node->element == element) 
    {
        return node->element;
    } 
    else if (node->element > element) 
    {
        return getFloor(node->left, element);
    } 
    else if(node->element < element)
    {
        const T& potential_item = node->element;
        try 
        {
            const T &item_to_compare = getFloor(node->right, element);
            if( potential_item > item_to_compare)
            {
                return  potential_item;
            }
            else
            {
                return item_to_compare;
            }
        } 
        catch (NoSuchItemException&) 
        {
            return node->element;
        }
    }
}


template<class T>
const T &DSWTree<T>::getMin() const 
{
    if (root==NULL) throw NoSuchItemException();
    return getMin(root);
}
template<class T>
const T& DSWTree<T>::getMin(Node<T> * const node) const
{
    if(node->left == NULL)
    {
        return node->element;
    }
    else
    {
        return getMin(node->left);
    }
}
template<class T>
const T& DSWTree<T>::getMax() const {
    if (root==NULL) throw NoSuchItemException();
    return getMax(root);
}
    
template<class T>
const T& DSWTree<T>::getMax(Node<T> * const node) const {
    if(node->right == NULL)
    {
        return node->element;
    }
    else
    {
        return getMax(node->right);
    }
}

template<class T>
const T& DSWTree<T>::getNext(const T &element) const {
    if(root == NULL)
    {
        throw NoSuchItemException();
    }
    const T max_elem = getMax();
    if(!(element < max_elem))
    {
        throw NoSuchItemException();
    }
    else
    {
        return getNext(root,element);
    }

    /* TODO */
}

template<class T>
const T& DSWTree<T>::getNext(Node<T> *node,const T &element) const {
    if(node == NULL)
    {
        throw NoSuchItemException();
    }
    if(element < node->element)
    {
        try
        {
            return getNext(node->left,element);
        }
        catch (NoSuchItemException&)
        {
            return node->element;
        }
    }
    else
    {
        return getNext(node->right,element);
    }
}

template<class T>
const Node<T>* DSWTree<T>::NodeFinder(const Node<T> *node,const T &element) const {
    if(node == NULL) return NULL;
    
    if(node->element == element) return node;
    else if(node->element > element)
    {
        return NodeFinder(node->left,element);
    }
    else
    {
        return NodeFinder(node->right,element);
    }
}
template<class T>
const int DSWTree<T>:: getNodeHeight(const T& element) const {
    const Node<T>*node =  NodeFinder(root,element);
    if (node == NULL) return -1;
    
    int lheight;
    int rheight;
    int max_height;
    
    if(node->left == NULL)
    {
        lheight = -1;
    }
    else
    {
        lheight = node->left->height;
    }
    // found the left subtree height
    if(node->right == NULL)
    {
        rheight = -1;
    }
    else
    {
        rheight = node->right->height;
    }
    //found the right suntree height
    
    if(lheight>rheight)
    {
        max_height = lheight;
    }
    else
    {
        max_height = rheight;
    }
    return max_height+1;
    
    /* TODO */
}

#endif //DSWTREE_H
