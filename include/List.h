#pragma once

#include <stdexcept>



template <typename T>
class List {
private:
    struct Node {
      T value;
      Node*  prev;
      Node* next;

      Node(const T& val) : value(val), prev(nullptr), next(nullptr) {}
    };

    Node* head;
    Node* tail;
    size_t m_size;

public:
    class iterator {
    private:
        Node* ptr;
    public:
        iterator(Node* p = nullptr) : ptr(p) {}

        T* operator->();
        const T* operator->() const;

        T& operator*();
        iterator& operator++();
        iterator operator++(int);
        iterator& operator--();
        iterator operator--(int);
        bool operator==(const iterator& other) const;
        bool operator!=(const iterator& other) const;

        friend class List;
    };

    class const_iterator {
    private:
        const Node* ptr;
    public:
        const_iterator(const Node* p = nullptr) : ptr(p) {}
    
        const T& operator*() const;
        const T* operator->() const;
        const_iterator& operator++();
        const_iterator operator++(int);
        const_iterator& operator--();
        const_iterator operator--(int);
        bool operator==(const const_iterator& other) const;
        bool operator!=(const const_iterator& other) const;
        
        friend class List;
    };

    List() : head(nullptr), tail(nullptr), m_size(0) {}
    ~List();
    List(const List& other);
    List& operator=(const List& other);

    void push_front(const T& value);
    void push_back(const T& value);
    void pop_front();
    void pop_back();

    T& front();
    const T& front() const;
    T& back();
    const T& back() const;

    void clear();
    iterator find(const T& value);
    iterator insert(iterator pos, const T& value);
    iterator erase(iterator pos);

    bool empty() const;
    size_t size() const;

    iterator begin();
    iterator end();

    const_iterator begin() const;
    const_iterator end() const;
};



template<typename T>
T* List<T>::iterator::operator->() {
    return &(ptr->value);
}

template<typename T>
const T* List<T>::iterator::operator->() const {
    return &(ptr->value);
}



template<typename T>
T& List<T>::iterator::operator*() {
    return ptr->value;
}

template<typename T>
typename List<T>::iterator& List<T>::iterator::operator++() {
    ptr = ptr->next;
    return *this;
}

template<typename T>
typename List<T>::iterator List<T>::iterator::operator++(int) {
    iterator tmp = *this;
    ptr = ptr->next;
    return tmp;
}

template<typename T>
typename List<T>::iterator& List<T>::iterator::operator--() {
    ptr = ptr->prev;
    return *this;
}

template<typename T>
typename List<T>::iterator List<T>::iterator::operator--(int) {
    iterator tmp = *this;
    ptr = ptr->prev;
    return tmp;
}

template<typename T>
bool List<T>::iterator::operator==(const iterator& other) const {
    return ptr == other.ptr;
}

template<typename T>
bool List<T>::iterator::operator!=(const iterator& other) const {
    return ptr != other.ptr;
}



template<typename T>
const T& List<T>::const_iterator::operator*() const {
    return ptr->value;
}

template<typename T>
const T* List<T>::const_iterator::operator->() const {
    return &(ptr->value);
}

template<typename T>
typename List<T>::const_iterator& List<T>::const_iterator::operator++() {
    ptr = ptr->next;
    return *this;
}

template<typename T>
typename List<T>::const_iterator List<T>::const_iterator::operator++(int) {
    const_iterator tmp = *this;
    ptr = ptr->next;
    return tmp;
}

template<typename T>
typename List<T>::const_iterator& List<T>::const_iterator::operator--() {
    ptr = ptr->prev;
    return *this;
}

template<typename T>
typename List<T>::const_iterator List<T>::const_iterator::operator--(int) {
    const_iterator tmp = *this;
    ptr = ptr->prev;
    return tmp;
}

template<typename T>
bool List<T>::const_iterator::operator==(const const_iterator& other) const {
    return ptr == other.ptr;
}

template<typename T>
bool List<T>::const_iterator::operator!=(const const_iterator& other) const {
    return ptr != other.ptr;
}



template<typename T>
List<T>::~List() {
    clear();
}

template<typename T>
List<T>::List(const List& other) 
    : head(nullptr), tail(nullptr), m_size(0) {
    Node* current = other.head;
    while (current) {
        push_back(current->value);
        current = current->next;
    }
}

template<typename T>
List<T>& List<T>::operator=(const List<T>& other) {
    if (this == &other) return *this;

    clear();
    
    Node* current = other.head;
    while (current) {
        push_back(current->value);
        current = current->next;
    }
    
    return *this;
}



template<typename T>
void List<T>::push_front(const T& value) {
    Node* newNode = new Node(value);
    if (empty()) {
        head = tail = newNode;
    } else {
        newNode->next = head;
        head->prev = newNode;
        head = newNode;
    }
    ++m_size;
}

template<typename T>
void List<T>::push_back(const T& value) {
    Node* newNode = new Node(value);
    if (empty()) {
        head = tail = newNode;
    } else {
        newNode->prev = tail;
        tail->next = newNode;
        tail = newNode;
    }
    ++m_size;
}

template<typename T>
void List<T>::pop_front() {
    if (empty()) return;
    Node* oldHead = head;
    head = head->next;
    if (head) {
        head->prev = nullptr;
    } else {
        tail = nullptr;
    }
    delete oldHead;
    --m_size;
}

template<typename T>
void List<T>::pop_back() {
    if (empty()) return;
    Node* oldTail = tail;
    tail = tail->prev;
    if (tail) {
        tail->next = nullptr;
    } else {
        head = nullptr;
    }
    delete oldTail;
    --m_size;
}



template<typename T>
T& List<T>::front() {
    if (empty()) throw std::out_of_range("List is empty");
    return head->value;
}

template<typename T>
const T& List<T>::front() const {
    if (empty()) throw std::out_of_range("List is empty");
    return head->value;
}

template<typename T>
T& List<T>::back() {
    if (empty()) throw std::out_of_range("List is empty");
    return tail->value;
}

template<typename T>
const T& List<T>::back() const {
    if (empty()) throw std::out_of_range("List is empty");
    return tail->value;
}



template<typename T>
bool List<T>::empty() const {
    return m_size == 0;
}

template<typename T>
size_t List<T>::size() const {
    return m_size;
}



template<typename T>
void List<T>::clear() {
    while (!empty()) {
        pop_front();
    }
}

template<typename T>
typename List<T>::iterator List<T>::find(const T& value) {
    for (iterator it = begin(); it != end(); ++it) {
        if (*it == value) {
            return it;
        }
    }
    return end();
}

template<typename T>
typename List<T>::iterator List<T>::insert(iterator pos, const T& value) {
    if (pos == begin()) {
        push_front(value);
        return begin();
    }
    
    if (pos == end()) {
        push_back(value);
        return iterator(tail);
    }
    
    Node* current = pos.ptr;
    Node* newNode = new Node(value);
    
    newNode->prev = current->prev;
    newNode->next = current;
    current->prev->next = newNode;
    current->prev = newNode;
    
    ++m_size;
    return iterator(newNode);
}

template<typename T>
typename List<T>::iterator List<T>::erase(iterator pos) {
    if (pos == end()) return end();
    
    Node* current = pos.ptr;
    iterator next(current->next);
    
    if (current == head) {
        pop_front();
        return next;
    }
    
    if (current == tail) {
        pop_back();
        return end();
    }
    
    current->prev->next = current->next;
    current->next->prev = current->prev;
    
    delete current;
    --m_size;
    return next;
}



template<typename T>
typename List<T>::iterator List<T>::begin() {
    return iterator(head);
}

template<typename T>
typename List<T>::iterator List<T>::end() {
    return iterator(nullptr);
}



template<typename T>
typename List<T>::const_iterator List<T>::begin() const {
    return const_iterator(head);
}

template<typename T>
typename List<T>::const_iterator List<T>::end() const {
    return const_iterator(nullptr);
}