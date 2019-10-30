#ifndef NODO_H
#define NODO_H

template<typename T>
class Nodo {
public:
    T dato;
    Nodo<T> *next;

    Nodo();

    Nodo(T dato);

    Nodo(T dato, Nodo<T> *next);
};

template<typename T>
Nodo<T>::Nodo() {
    next = nullptr;
}

template<typename T>
Nodo<T>::Nodo(T dato) {
    this->dato = dato;
    next = nullptr;
}

template<typename T>
Nodo<T>::Nodo(T dato, Nodo<T> *next) {
    this->dato = dato;
    this->next = next;
    next = nullptr;
}

#endif