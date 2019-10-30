#ifndef STACK_H
#define STACK_H

#include "Nodo.h"

template<typename T>
class Stack {
private:
    Nodo<T> *cima;
    unsigned int tamanio;

public:
    /**
     * @brief Constructor de stack, inicializa la cima en 0
     */
    Stack() {
        cima = nullptr;
        tamanio = 0;
    };

    ~Stack() {
        // TODO
        while(cima != nullptr)
            pop();

    }

    /**
     * @brief Metodo que agrega un elemento a la pila
     * @param dato Valor que se va a agregar a la pila
     */
    void push(T dato) {
        auto *nuevo = new Nodo<T>(dato, cima);
        cima = nuevo;
        tamanio++;
    }


    /**
     * @brief Metodo que saca un elemento de la pila
     * @return  Valor extraido de la pila si no hubo error
     */
    T pop() {
        if (cima == nullptr)
            throw 404;

        Nodo<T> *aBorrar = cima;
        T dato = cima->dato;
        cima = cima->next;
        delete aBorrar;
        tamanio--;
        return dato;
    }

    /**
     * @brief Método que devuelve el valor actual de la cima sin modificar la pila
     */
    T top() {
        if (cima == nullptr)
            throw 404;
        return cima->dato;
    }

    /**
     * @brief Metodo  que devuelve el tamaño actual de la pila
     * @return Tamaño de la pila
     */
    int size() {
        return tamanio;
    }

    /**
     * @brief Metodo que indica si la pila está vacia o no.
     * @return true si esta vacia, false si no lo está
     */
    bool empty() {
        return cima == nullptr;
    }

};

#endif //STACK_H
