#ifndef PILA_H
#define PILA_H

#include "Nodos.h"
#include <vector>
#include <string>
#include <iostream>

using namespace std;

template <typename T>
class Pila
{
private:
    NodoPila<T>* tope;
public:
    Pila() : tope(nullptr) {}
    void Push(T dato);
    void Pop();
    T Top();
    void ImprimirTope();
    void ImprimirPila();
    bool buscar(string dt);
    bool PilaVacia() {return tope == nullptr;}
    void Eliminar(const string& dt);
};

template <typename T>
void Pila<T>::Push(T dato) {
    NodoPila<T>* nuevoNodo = new NodoPila<T>(dato);
    nuevoNodo->siguiente = tope;
    tope = nuevoNodo;
}

template <typename T>
void Pila<T>::Pop() {
    if (PilaVacia()) {
        return;
    }
    NodoPila<T>* temp = tope;
    tope = tope->siguiente;
    delete temp;
}

template <typename T>
T Pila<T>::Top() {
    if (PilaVacia()) {
        throw runtime_error("La pila está vacía");
    }
    return tope->dato;
}

template <typename T>
void Pila<T>::ImprimirTope() {
    if (tope == nullptr) {
        cout << "La pila está vacía" << endl;
        return;
    }

    cout << "1. ";
    vector<string> partes = tope->dato.ObtenerPartes();
    for (size_t i = 1; i < partes.size(); ++i) {
        cout << partes[i];
        if (i < partes.size() - 1) {
            cout << " || ";
        }
    }
    cout << endl;
}

template <typename T>
void Pila<T>::ImprimirPila() {
    NodoPila<T>* temp = tope;
    int linea = 1;
    while (temp != nullptr) {
        cout << linea << ". " ;
        vector<string> partes = temp->dato.ObtenerPartes();
        for (size_t i = 1; i < partes.size(); ++i) {
            cout << partes[i];
            if (i < partes.size() - 1) {
                cout << " || ";
            }
        }
        cout << endl;
        linea++;
        temp = temp->siguiente;
    }
}

template <typename T>
bool Pila<T>::buscar(string dt)
{
    NodoPila<T>* temp = tope;
    while (temp != nullptr) {
        if (temp->dato.ObtenerCorreo() == dt) {
            return true;
        }
        temp = temp->siguiente;
    }
    return false;
}

// Implementación del método Eliminar
template <typename T>
void Pila<T>::Eliminar(const string& dt) {
    if (PilaVacia()) {
        return;
    }

    // Verificar si el elemento existe en la pila
    if (!buscar(dt)) {
        return;
    }

    NodoPila<T>* actual = tope;
    NodoPila<T>* anterior = nullptr;

    // Buscar el nodo que contiene el dato
    while (actual != nullptr && actual->dato.ObtenerCorreo() != dt) {
        anterior = actual;
        actual = actual->siguiente;
    }

    // Si el nodo a eliminar es el tope
    if (actual == tope) {
        tope = tope->siguiente;
    } else {
        anterior->siguiente = actual->siguiente;
    }

    delete actual;
}

#endif // PILA_H
