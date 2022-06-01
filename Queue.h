//
//  Queue.hpp
//  mtmchkin
//
//  Created by Abdul Hadi Yasin on 23/05/2022.
//

#ifndef Queue_hpp
#define Queue_hpp

#include <iostream>
using std::string;

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
        m_head = NULL;
        m_tail = NULL;
    }
    
    Queue& operator=(const Queue& other) {
        if (this == &other)
            return *this;
        
        delete m_head;
        m_head = NULL;
        m_tail = NULL;
        m_size = 0;
        
        Element<T>* oNode = other.m_head;
        while(oNode != NULL){
            pushBack(oNode->getValue());
            oNode = oNode->getNext();
        }
        
        return *this;
    }
    
    Queue(const Queue& other){
        m_size = other.size();
        m_head = NULL;
        m_tail = NULL;
        
        Element<T>* oNode = other.m_head;
        while(oNode != NULL){
            T& v = oNode->getValue();
            try {
                pushBack(v);
            } catch (const std::bad_alloc& e){
                throw e;
            }
            
            
            oNode = oNode->getNext();
        }
    }
    
    /**
     * Inserts the item to the end of the queue.
     * @param item - The item to be inserted.
     */
    void pushBack(const T& item) {
        if(m_head == NULL){
            Element<T> *newNodePtr = new Element<T>(item);
            
            m_head = newNodePtr;
            m_tail = NULL;
            m_size = 1;
        } else if(m_tail == NULL){
            // There's a head, but theres no tail (single item).
            Element<T> *newNodePtr = new Element<T>(item);
            
            (*m_head).setNext(newNodePtr);
            m_tail = newNodePtr;
            m_size += 1;
        } else {
            // There's a tail.
            Element<T> *newNodePtr = new Element<T>(item);
            (*m_tail).setNext(newNodePtr);
            
            m_tail = NULL;
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
        if(m_head == NULL || m_size == 0){
            throw EmptyQueue();
            return; // There's no thing to do here.
        }
        
        if(m_size == 1){ // There's only one item in queue, about to become empty.
            delete m_head;
            m_head = NULL;
            m_tail = NULL;
            m_size = 0;
            return;
        }
        
        Element<T>* second = m_head->getNext();
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
    template<class El> class Element;
    Element<T>* m_head;
    Element<T>* m_tail;
    
public:
    class Iterator {
    private:
        Queue<T>* m_queue;
        Element<T>* m_current = NULL;
    public:
        struct InvalidOperation{
            const std::string what () {
                return "Invalid Operation";
            }
        };
        
        Iterator(Queue<T>* queue, Element<T>* node): m_queue(queue), m_current(node) {
            // Initialize an iterator instance.
        }
        
        Iterator(const Iterator& other): m_queue(other.m_queue), m_current(other.m_current) {
        }
        
        Iterator& operator=(const Iterator& other) {
            if(this == other)
                return *this;
            
            this->m_queue = other.m_queue;
            this->m_current = other.m_current;
            return *this;
        }
        
        /*
         * D'tor of Iterator.
         */
        ~Iterator() = default;
        
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
            if(m_current == NULL)
                throw InvalidOperation();
            
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
    };
public:
    class ConstIterator {
    private:
        const Queue<T>* m_queue;
        Element<T>* m_current = NULL;
    public:
        struct InvalidOperation{
            const std::string what () {
                return "Invalid Operation";
            }
        };
        
        ConstIterator(const Queue<T>* queue, Element<T>* node): m_queue(queue), m_current(node) {
        }
        
        ConstIterator(const ConstIterator& other) : m_current(other.m_current) {
            const Queue<T>* constQueue = other.m_queue;
            m_queue = constQueue;
        }
        
        ConstIterator& operator=(const ConstIterator& other) {
            if(this == other)
                return *this;
            
            this->m_current = other.m_current;
            this->m_queue = other.m_queue;
            return *this;
        }
        
        /*
         * D'tor of Iterator Class
         */
        ~ConstIterator() = default;
        
        const T& operator*() const {
            if(m_current == NULL)
                throw InvalidOperation();
            
            T& v = (*m_current).getValue();
            return v;
        }
        
        ConstIterator& operator++() {
            if(m_current == NULL)
                throw InvalidOperation();
            
            m_current = (*m_current).getNext();
            return *this;
        }
        
        ConstIterator operator++(int) {
            if(m_current == NULL)
                throw InvalidOperation();
            
            ConstIterator result = *this;
            ++ *this;
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
    };
    
private:
    template <class El> class Element {
    public:
        /**
         * C'tor of QueueNode class
         *
         * @param value - The value of the node.
        */
        Element(El value): m_value(value), m_next(NULL){
            m_next = NULL;
        }
        
        /**
         * D'tor of Queue class
        */
        ~Element() {
            if(m_next != NULL)
                delete m_next;
            
            m_next = NULL;
        }
        
        /*
         * Assignment operator of QueueNode class.
         *
         * @param other - reference to an QueueNode object.
         * @return
         *      reference to an QueueNode object.
         */
        Element& operator=(const Element& other) = default;
        
        /**
         * Returns node's value.
         *
         * @return Value of the receiver.
        */
        El& getValue() {
            return m_value;
        }
        
        /**
         * Sets the receiver (Node) to a new value.
         *
         * @param newValue - The new value to set.
        */
        void setValue(const El& newValue) {
            m_value = newValue;
        }
        
        /**
         * Returns reference to the node after the receiver.
         *
         * @return A reference to the node after the receiver, if there's no such node returns NULL.
        */
        Element* getNext() const {
            return m_next;
        }
        
        /**
         * Sets the node after the receiver (Node) to be a new node.
         * @note You are responsible of deleting the previous `next` when needed.
         *
         * @param newNext - The other node to set as next of the receiver.
        */
        void setNext(Element* newNext) {
            m_next = newNext;
        }
        
    private:
        El m_value;
        Element<El>* m_next;
    };
};


template<class T, class Predicate>
Queue<T> filter(Queue<T> queue, Predicate predicate){
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

template<class T, class Operation>
void transform(Queue<T>& queue, Operation operation){
    for(typename Queue<T>::Iterator i = queue.begin(); i != queue.end(); ++i) {
        /* Handle filtering */
        operation(*i);
    }
}


#endif /* Queue_hpp */
