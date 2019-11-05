#ifndef QUEUE_H
#define QUEUE_H

#include "Nodo.h"

template<typename T>
class Queue {
private:
    Nodo<T> *frente, *fondo;

public:
    Queue();


    ~Queue();

    void enqueue(T dato); // Encolar
    T dequeue(); // Desencolar
    bool isEmpty();

    T front();
};

template<typename T>
Queue<T>::Queue() {
    frente = fondo = nullptr;
}

template<typename T>
void Queue<T>::enqueue(T dato) {

    auto *nuevo = new Nodo<T>(dato);
    if (fondo == nullptr)
        frente = nuevo;
    else
        fondo->next = nuevo;

    fondo = nuevo;
}

template<typename T>
T Queue<T>::dequeue() {
    T ret;
    Nodo<T> *aux = frente;

    if (frente == nullptr) {
        throw 404;
    }

    frente = frente->next;
    if (frente == nullptr) // si borro el ultimo elemento
        fondo = nullptr;

    ret = aux->dato;
    delete aux;
    return ret;
}

template<typename T>
T Queue<T>::front() {
    if (frente == nullptr) {
        throw 404;
    }
    return frente->dato;
}

template<typename T>
Queue<T>::~Queue() {
    while (frente != nullptr)
        dequeue();
}

template<typename T>
bool Queue<T>::isEmpty() {
    return frente == nullptr;
}


#endif //QUEUE_H
