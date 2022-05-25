//
//  Queue.hpp
//  mtmchkin
//
//  Created by Abdul Hadi Yasin on 23/05/2022.
//

#ifndef Queue_hpp
#define Queue_hpp

#include <stdio.h>
#include <iostream>
#include "QueueNode.h"
using namespace std;

// One function works for all data types.
// This would work even for user defined types
// if operator '>' is overloaded
template<class T> class Queue {
public:
    
    /*
     * Type of function for filtering queues.
     * This function should accept an element of a queue and
     * reutrn true if it matches a certain condition & false if it doesn't
     */
    typedef bool (*Predicate)(const T&);
    
    /*
     * Type of function for transforming queues.
     * This function should accept an element of a queue and change it
     */
    typedef void (*Operation)(T&);
    
    struct EmptyQueue : public std::exception {
        const char * what () const throw () {
            return "Can't return the first element of an empty queue";
        }
    };
    
    /**
     * C'tor of Queue class
    */
    Queue<T>() {
        // Initialize an empty queue.
        m_size = 0;
        m_head = m_tail = NULL;
    }
    
    /**
     * D'tor of Queue class
    */
    ~Queue<T>() {
        delete m_head;
    }
    
    Queue& operator=(const Queue& other) {
        if (this == &other)
            return *this;
        
        delete m_head;
        m_head = NULL;
        m_tail = NULL;
        m_size = 0;
        
        QueueNode<T> oNode = other.m_head;
        while(oNode != NULL){
            pushBack(oNode.getValue());
            m_size += 1;
            
            oNode = oNode.getNext();
        }
        
        return *this;
    }
    
    Queue(const Queue& other){
        m_size = other.size();
        m_head = NULL;
        m_tail = NULL;
        
        QueueNode<T>* oNode = other.m_head;
        while(oNode != NULL){
            T& v = oNode->getValue();
            pushBack(v);
            
            oNode = oNode->getNext();
        }
    }
    
    /**
     * Inserts the item to the end of the queue.
     * @param item - The item to be inserted.
     */
    void pushBack(const T& item) {
        if(m_head == NULL){
            QueueNode<T> *newNodePtr = new QueueNode<T>(item);
            
            m_head = newNodePtr;
            m_tail = NULL;
            m_size = 1;
        } else if(m_tail == NULL){
            // There's a head, but theres no tail (single item).
            QueueNode<T> *newNodePtr = new QueueNode<T>(item);
            
            (*m_head).setNext(newNodePtr);
            m_tail = newNodePtr;
            m_size += 1;
        } else {
            // There's a tail.
            QueueNode<T> *newNodePtr = new QueueNode<T>(item);
            (*m_tail).setNext(newNodePtr);
            
            m_tail = newNodePtr;
            m_size += 1;
        }
    }
    
    /**
     * Returns the first item in the queue.
     * @return The item at the start of the queue, if there's no such item returns NULL.
     */
    T& front() const {
        if(m_head == NULL)
            throw EmptyQueue();
        
        T& v = (*m_head).getValue();
        return v;
    }
    
    /**
     * Removes the first item from the queue. If the queue is empty (aka size = 0), does nothing.
     */
    void popFront() {
        if(m_head == NULL || m_size == 0)
            return; // There's no thing to do here.
        
        if(m_size == 1){ // There's only one item in queue, abut to becom empty.
            delete m_head;
            m_head = NULL;
            m_tail = NULL;
            m_size = 0;
            return;
        }
        
        QueueNode<T>* second = m_head->getNext();
        m_head->setNext(NULL);
        delete m_head;
        
        m_head = second;
        
        m_size -= 1;
    }
    
    /**
     * Returns number of items in the queue, or zero if when the receiver is empty.
     * @return Number of items.
     */
    int size() const {
        return m_size;
    }
    
    class Iterator;
    Iterator begin() { return Iterator(this, m_head); }
    Iterator end() { return Iterator(this, NULL); }
    
    class ConstIterator;
    ConstIterator begin() const { return ConstIterator(this, m_head); }
    ConstIterator end() const { return ConstIterator(this, NULL); }
    
private:
    int m_size = 0;
    QueueNode<T>* m_head;
    QueueNode<T>* m_tail;
};

template<class T>
class Queue<T>::Iterator {
    const Queue<T>* m_queue;
    QueueNode<T>* m_current = NULL;
    Iterator(const Queue<T>* queue, QueueNode<T>* node): m_queue(queue), m_current(node) {
        // Initialize an iterator instance.
    }
    
    friend class Queue<T>;
public:
    struct InvalidOperation{
        const std::string what () {
            return "Invalid Operation";
        }
    };
    
    T& operator*() const {
        if(m_current == NULL)
            throw InvalidOperation();
        
        
        T& v = (*m_current).getValue();
        return v;
    }
    T* operator->() const {
        if(m_current == NULL)
            throw InvalidOperation();
        return &((*m_current).getValue());
    }
    
    Iterator& operator++() {
        if(m_current == NULL)
            throw InvalidOperation();
        
        m_current = (*m_current).getNext();
        return *this;
    }
    
    Iterator operator++(int) {
        Iterator result = *this;
        ++*this;
        return result;
    }
    
    bool operator==(const Iterator& iterator) const {
        if(m_queue != iterator.m_queue)
            throw InvalidOperation();
        return m_current == iterator.m_current;
    }
    
    bool operator!=(const Iterator& iterator) const {
        return !(*this == iterator);
    }
    
    Iterator(const Iterator&) = default;
    Iterator& operator=(const Iterator&) = default;
};

template<class T>
class Queue<T>::ConstIterator {
    const Queue<T>* m_queue;
    QueueNode<T>* m_current = NULL;
    ConstIterator(const Queue<T>* queue, QueueNode<T>* node): m_queue(queue), m_current(node) {
        // Initialize an iterator instance.
    }
    
    friend class Queue<T>;
public:
    struct InvalidOperation{
        const std::string what () {
            return "Invalid Operation";
        }
    };
    
    const T operator*() const {
        if(m_current == NULL)
            throw InvalidOperation();
        
        T& v = (*m_current).getValue();
        return v;
    }
    const T* operator->() const {
        if(m_current == NULL)
            throw InvalidOperation();
        return &((*m_current).getValue());
    }
    
    ConstIterator& operator++() {
        if(m_current == NULL)
            throw InvalidOperation();
        
        m_current = (*m_current).getNext();
        return *this;
    }
    
    ConstIterator operator++(int) {
        Iterator result = *this;
        ++*this;
        return result;
    }
    
    bool operator==(const ConstIterator& iterator) const {
        if(m_queue != iterator.m_queue)
            throw InvalidOperation();
        return m_current == iterator.m_current;
    }
    
    bool operator!=(const ConstIterator& iterator) const {
        return !(*this == iterator);
    }
    
    ConstIterator(const ConstIterator&) = default;
    ConstIterator& operator=(const ConstIterator&) = default;
};


template<class T> Queue<T> filter(Queue<T> queue, bool (*predicate)(T)){
    if(predicate == NULL)
        return Queue<T>(queue);
    
    Queue<T> newQueue{};
    for(typename Queue<T>::Iterator i = queue.begin(); i != queue.end(); ++i) {
        /* Handle filtering */
        if(predicate(*i)){
            // Should keep item in filtered queue.
            newQueue.pushBack(*i);
        }
    }
    
    return newQueue;
}

template<class T> void transform(Queue<T>& queue, void (*transformer)(T&)){
    if(transformer == NULL)
        return;
    
    for(typename Queue<T>::Iterator i = queue.begin(); i != queue.end(); ++i) {
        /* Handle filtering */
        T& value = *i;
        transformer(value);
    }
}


#endif /* Queue_hpp */
