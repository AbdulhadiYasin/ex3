//
//  QueueNode.hpp
//  mtmchkin
//
//  Created by Abdul Hadi Yasin on 23/05/2022.
//

#ifndef QueueNode_hpp
#define QueueNode_hpp

#include <stdio.h>

template <class T> class QueueNode {
public:
    /**
     * C'tor of QueueNode class
     *
     * @param value - The value of the node.
    */
    QueueNode(T value);
    
    /**
     * D'tor of Queue class
    */
    ~QueueNode();
    
    /*
     * Assignment operator of QueueNode class.
     *
     * @param other - reference to an QueueNode object.
     * @return
     *      reference to an QueueNode object.
     */
    QueueNode& operator=(const QueueNode& other) = default;
    
    /**
     * Returns node's value.
     *
     * @return Value of the receiver.
    */
    T& getValue();
    
    /**
     * Sets the receiver (Node) to a new value.
     *
     * @param newValue - The new value to set.
    */
    void setValue(const T& newValue);
    
    /**
     * Adds a new node after the receiver with the provided newValue.
     *
     * @param value - The value to add as the next node of the receiver.
     * @return A reference to the node after the receiver after the update.
    */
    QueueNode* addNext(const T& value);
    
    /**
     * Returns reference to the node after the receiver.
     *
     * @return A reference to the node after the receiver, if there's no such node returns NULL.
    */
    QueueNode* getNext() const;
    
    /**
     * Sets the node after the receiver (Node) to be a new node.
     * @note You are responsible of deleting the previous `next` when needed.
     *
     * @param newNext - The other node to set as next of the receiver.
    */
    void setNext(QueueNode* newNext);
    
    
private:
    T m_value;
    QueueNode<T>* m_next;
};



template<class T> QueueNode<T>::QueueNode(T value): m_value(value), m_next(NULL) {
    m_next = NULL;
}

template<class T> QueueNode<T>::~QueueNode() {
    delete m_next;
}
    
template<class T> T& QueueNode<T>::getValue() {
    return m_value;
}

template<class T> void QueueNode<T>::setValue(const T& newValue) {
    m_value = newValue;
}

template<class T> QueueNode<T>* QueueNode<T>::getNext() const {
    return m_next;
}

template<class T> QueueNode<T>* QueueNode<T>::addNext(const T& value) {
    if(m_next == NULL){
        QueueNode<T> *newNodePtr;
        QueueNode<T> newNode(value);
        newNodePtr = &newNode;
        
        m_next = newNodePtr;
        return m_next;
    }
    
    QueueNode<T> *newNodePtr;
    QueueNode<T> newNode(value);
    newNode.m_next = m_next;
    newNodePtr = &newNode;
    
    m_next = newNodePtr;
    return m_next;
}

template<class T> void QueueNode<T>::setNext(QueueNode<T>* newNext) {
    m_next = newNext;
}

#endif /* QueueNode_hpp */
