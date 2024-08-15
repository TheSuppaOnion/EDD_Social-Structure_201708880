#include "Listas.h"

template <typename T>
void ListaSE<T>::Insertar(T dato)
{
    Nodo<T>* nuevoNodo = new Nodo<T>(dato);
    nuevoNodo->dato = dato;
    nuevoNodo->siguiente = nullptr;

    if (ListaVacia()) {
        primero = nuevoNodo;
        ultimo = nuevoNodo;
    } else {
        ultimo->siguiente = nuevoNodo;
        ultimo = nuevoNodo;
    }
};

template <typename T>
void ListaSE<T>::Imprimir()
{
   Nodo<T>* temp = primero;
        while (temp != nullptr) {
            cout << temp->dato << " -> ";
            temp = temp->siguiente;
        }
        cout << "nullptr" << endl;
};

template <typename T>
void ListaDE<T>::Insertar(T dato) {
    Nodo<T>* nuevoNodo = new Nodo<T>(dato);
    nuevoNodo->dato = dato;
    nuevoNodo->siguiente = nullptr;
    nuevoNodo->anterior = nullptr;

    if (ListaVacia()) {
        primero = nuevoNodo;
        ultimo = nuevoNodo;
    } else {
        ultimo->siguiente = nuevoNodo;
        nuevoNodo->anterior = ultimo;
        ultimo = nuevoNodo;
    }
}

template <typename T>
void ListaDE<T>::Imprimir()
{
    Nodo<T>* temp = primero;
        while (temp != nullptr) {
            cout << temp->dato << " <-> ";
            temp = temp->siguiente;
        }
    cout << "nullptr" << endl;
};

/*string ListaDE<T>::Buscar(string dt)
{
    return 0;
};

void ListaDE<T>::Borrar(string dt)
{
    Publicacion *aux = primero->siguiente;
    Publicacion *aux1 = primero->siguiente->siguiente;
   while (aux!=NULL)
    {
        if(aux->dato==dt)
        {
            delete aux;
        }
        else
        {
            aux = aux->siguiente;
            aux1 = aux1->siguiente;
        }
    }
};*/
