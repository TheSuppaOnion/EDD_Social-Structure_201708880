#include <iostream>
using namespace std;

template <typename T>
class Nodo {
public:
    T dato;
    Nodo* siguiente;
    Nodo* anterior;
    Nodo(T dato) : dato(dato), siguiente(nullptr), anterior(nullptr) {}
};

template <typename T>
class ListaSE
{
    
    private:
        Nodo<T>* primero;
        Nodo<T>* ultimo;

    public:
        ListaSE(): primero(nullptr), ultimo(nullptr) {}

        ~ListaSE() {
           Nodo<T>* temp = primero;
            while (!ListaVacia()) {
                Nodo<T>* siguiente = temp->siguiente;
                delete temp;
                temp = siguiente;
            }
        }
        void Insertar(T dato);
        void Imprimir();
        bool ListaVacia() {return (primero == NULL);}
};

template <typename T>
class ListaDE
{
    private:
    
        Nodo<T>* primero;
        Nodo<T>* ultimo;

    public:
         ListaDE(){
            primero->siguiente = ultimo;
            ultimo->anterior = primero;
            primero->anterior=NULL;
            ultimo->siguiente=NULL;
         }

        ~ListaDE() {
            Nodo<T>* temp = primero;
            while (!ListaVacia()) {
                Nodo<T>* siguiente = temp->siguiente;
                delete temp;
                temp = siguiente;
            }
        }
        void Insertar(T dato);
        void Imprimir();
        void Borrar(T dato);
        bool ListaVacia() {return (primero == NULL);}
        //string  Buscar(string dt);
};