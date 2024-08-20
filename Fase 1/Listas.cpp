#include "Listas.h"

struct Usuario {
    string nombre;
    string apellido;
    string fechaNac; 
    string correoElectronico;
    string contrasenia;
    Usuario(string nombre, string apellido, string fechaNac, string correoElectronico, string contrasenia) : nombre(nombre), apellido(apellido), fechaNac(fechaNac), correoElectronico(correoElectronico), contrasenia(contrasenia){}
    friend ostream& operator<<(ostream& os, const Usuario& u) {
        os << u.nombre << " " << u.apellido << " " << u.fechaNac << " " << u.correoElectronico << " " << u.contrasenia << " ";
        return os;
        }
    };
    
struct Publicacion {
    string dato;
    Publicacion(string dato) : dato(dato) {}
    /*friend ostream& operator<<(ostream& os, const Publicacion& p) {
        os << u.nombre << " " << u.apellido << " " << u.fechaNac << " " << u.correoElectronico << " " << u.contrasenia << " ";
        return os;
        }*/
    };

ListaSE<Usuario> listadmin;
ListaSE<Usuario> listausers;


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
bool ListaSE<T>::buscar(string nombre, string contrasenia)
{
    Nodo<T>* temp = primero;
    while (temp != nullptr) {
        if (temp->dato.nombre == nombre && temp->dato.contrasenia == contrasenia) {
            return true;
        }
        temp = temp->siguiente;
    }
    return false;
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
