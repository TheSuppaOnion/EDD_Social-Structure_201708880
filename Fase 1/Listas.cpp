#include "Listas.h"
#include <vector>

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
    string correo;
    string contenido;
    string fecha;
    string hora;
    Publicacion(string correo, string contenido, string fecha, string hora) : correo(correo), contenido(contenido), fecha(fecha), hora(hora){}
    friend ostream& operator<<(ostream& os, const Publicacion& p) {
        os << p.correo << " " << p.contenido << " " << p.fecha << " " << p.hora << " ";
        return os;
        }
    vector<string> ObtenerPartes() const {
        return {correo, contenido, fecha, hora};
    }
    };

ListaSE<Usuario> listadmin;
ListaSE<Usuario> listausers;
ListaDE<Publicacion> listapub;
ListaDE<Publicacion> listapubtemp;

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
bool ListaSE<T>::buscar(string correo, string contrasenia)
{
    Nodo<T>* temp = primero;
    while (temp != nullptr) {
        if (temp->dato.correoElectronico == correo && temp->dato.contrasenia == contrasenia) {
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
        vector<string> partes = temp->dato.ObtenerPartes();
        for (size_t i = 1; i < partes.size(); ++i) {
            cout << partes[i];
            if (i < partes.size() - 1) {
                cout << " || ";
            }
        }
        cout << endl;
        temp = temp->siguiente;
    }
    cout << "Fin de las publicaciones!" << endl;
};

template <typename T>
void ListaDE<T>::CopiarPorCorreo(const std::string& correo, ListaDE<T>& listaDestino) {
    Nodo<T>* temp = primero;
    while (temp != nullptr) {
        if (temp->dato.correo == correo) {
            listaDestino.Insertar(temp->dato);
        }
        temp = temp->siguiente;
    }
}

template <typename T>
void ListaDE<T>::Vaciar() {
    Nodo<T>* temp = primero;
    while (temp != nullptr) {
        Nodo<T>* siguiente = temp->siguiente;
        delete temp;
        temp = siguiente;
    }
    primero = nullptr;
    ultimo = nullptr;
}

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
