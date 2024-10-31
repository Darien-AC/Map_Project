// DoublyLinkedList.h
#ifndef DOUBLY_LINKED_LIST_H
#define DOUBLY_LINKED_LIST_H

#include <iostream>

template <typename T>
struct Node {
    T data;
    Node* next;
    Node* prev;

    Node(T value) : data(value), next(nullptr), prev(nullptr) {}
};

template <typename T>
class PointsAndRoutesList {
private:
    Node<T>* head;
    Node<T>* tail;

public:
    PointsAndRoutesList();
    ~PointsAndRoutesList();

    bool isEmpty() const;
    void append(T value);
    void prepend(T value);
    void remove(T value);
    void display() const;
};

#include "PointsAndRoutesList.cpp"  // Incluye la implementación

#endif