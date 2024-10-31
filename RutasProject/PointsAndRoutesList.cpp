// DoublyLinkedList.cpp
#ifndef DOUBLY_LINKED_LIST_CPP
#define DOUBLY_LINKED_LIST_CPP

#include "PointsAndRoutesList.h"

// Constructor para inicializar la lista como vacía
template <typename T>
PointsAndRoutesList<T>::PointsAndRoutesList() : head(nullptr), tail(nullptr) {}

// Destructor para liberar la memoria de los nodos
template <typename T>
PointsAndRoutesList<T>::~PointsAndRoutesList() {
    Node<T>* current = head;
    while (current != nullptr) {
        Node<T>* next = current->next;
        delete current;
        current = next;
    }
}

// Método para verificar si la lista está vacía
template <typename T>
bool PointsAndRoutesList<T>::isEmpty() const {
    return head == nullptr;
}

// Método para agregar un elemento al final de la lista
template <typename T>
void PointsAndRoutesList<T>::append(T value) {
    Node<T>* newNode = new Node<T>(value);
    if (isEmpty()) {
        head = tail = newNode;
    }
    else {
        tail->next = newNode;
        newNode->prev = tail;
        tail = newNode;
    }
}

// Método para agregar un elemento al inicio de la lista
template <typename T>
void PointsAndRoutesList<T>::prepend(T value) {
    Node<T>* newNode = new Node<T>(value);
    if (isEmpty()) {
        head = tail = newNode;
    }
    else {
        newNode->next = head;
        head->prev = newNode;
        head = newNode;
    }
}

// Método para eliminar el primer elemento con un valor específico
template <typename T>
void PointsAndRoutesList<T>::remove(T value) {
    if (isEmpty()) return;

    Node<T>* current = head;
    while (current != nullptr) {
        if (current->data == value) {
            if (current == head) {
                head = head->next;
                if (head) head->prev = nullptr;
            }
            else if (current == tail) {
                tail = tail->prev;
                if (tail) tail->next = nullptr;
            }
            else {
                current->prev->next = current->next;
                current->next->prev = current->prev;
            }
            delete current;
            return;
        }
        current = current->next;
    }
}

// Método para mostrar los elementos de la lista
template <typename T>
void PointsAndRoutesList<T>::display() const {
    Node<T>* current = head;
    while (current != nullptr) {
        std::cout << current->data << " ";
        current = current->next;
    }
    std::cout << std::endl;
}

#endif
