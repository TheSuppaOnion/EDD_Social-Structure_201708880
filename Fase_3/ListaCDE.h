#ifndef LISTACDE_H
#define LISTACDE_H

#include "Nodos.h"
#include <vector>
#include <string>
#include <iostream>

using namespace std;

template <typename T>
class ListaCDE
{
private:
    Nodo<T>* primero;
    Nodo<T>* ultimo;
public:

    ListaCDE(): primero(nullptr), ultimo(nullptr) {}

    ~ListaCDE() {
        Nodo<T>* temp = primero;
        while (temp != nullptr) {
            Nodo<T>* siguiente = temp->siguiente;
            delete temp;
            temp = siguiente;
        }
    }
    void Insertar(T dato);
    void Navegar(char direccion);
    void Vaciar();
    void Borrar(string contenido);
    bool ListaVacia() {return (primero == nullptr);}
    void Imprimir();
};

template <typename T>
void ListaCDE<T>::Insertar(T dato) {
    Nodo<T>* nuevoNodo = new Nodo<T>(dato);
    nuevoNodo->dato = dato;
    nuevoNodo->siguiente = nullptr;
    nuevoNodo->anterior = nullptr;

    if (ListaVacia()) {
        primero = nuevoNodo;
        ultimo = nuevoNodo;
        primero->siguiente = primero;
        primero->anterior = ultimo;
    } else {
        ultimo->siguiente = nuevoNodo;
        nuevoNodo->anterior = ultimo;
        nuevoNodo->siguiente = primero;
        primero->anterior = nuevoNodo;
        ultimo = nuevoNodo;
    }
}

template <typename T>
void ListaCDE<T>::Navegar(char direccion) {
    if (ListaVacia()) {
        cout << "La lista está vacía." << endl;
        return;
    }

    static Nodo<T>* temp = primero;

    if (direccion == 'I' || direccion == 'i') {
        temp = temp->anterior;
    } else if (direccion == 'D' || direccion == 'd') {
        temp = temp->siguiente;
    } else {
        cout << "Dirección inválida." << endl;
        return;
    }

    vector<string> partes = temp->dato.ObtenerPartes();
    for (size_t i = 1; i < partes.size(); ++i) {
        cout << partes[i];
        if (i < partes.size() - 1) {
            cout << " || ";
        }
    }
    cout << endl;
}

template <typename T>
void ListaCDE<T>::Vaciar() {
    Nodo<T>* temp = primero;
    while (temp != nullptr) {
        Nodo<T>* siguiente = temp->siguiente;
        delete temp;
        temp = siguiente;
        if (temp == primero) {
            break;
        }
    }
    primero = nullptr;
    ultimo = nullptr;
}

template <typename T>
void ListaCDE<T>::Imprimir()
{
    Nodo<T>* temp = primero;
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
        if (temp == primero) {
            break;
        }
    }
    cout << "Fin de las publicaciones!" << endl;
}

#endif // LISTACDE_H
