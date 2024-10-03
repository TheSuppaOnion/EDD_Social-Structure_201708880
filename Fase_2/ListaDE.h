#ifndef LISTADE_H
#define LISTADE_H

#include "Nodos.h"
#include <unordered_set>
#include <vector>
#include <string>
#include <iostream>
#include <fstream>

using namespace std;

template <typename T>
class ListaDE
{
private:
    Nodo<T>* primero;
    Nodo<T>* ultimo;
    void RecorridoPreorden(Nodo<T>* nodo, vector<T>& resultado, std::unordered_set<Nodo<T>*>& visitados) const;
    void RecorridoInorden(Nodo<T>* nodo, vector<T>& resultado, std::unordered_set<Nodo<T>*>& visitados) const;
    void RecorridoPostorden(Nodo<T>* nodo, vector<T>& resultado, std::unordered_set<Nodo<T>*>& visitados) const;

public:
    ListaDE(): primero(nullptr), ultimo(nullptr) {}

    ~ListaDE() {
        Nodo<T>* temp = primero;
        while (temp != nullptr) {
            Nodo<T>* siguiente = temp->siguiente;
            delete temp;
            temp = siguiente;
        }
    }
    void Insertar(T dato);
    void Imprimir();
    void Vaciar();
    void Borrar(string contenido);
    bool ListaVacia() {return (primero == nullptr);}
    vector<string> getContenidoVector(string dt);
    Nodo<T>* getContenido(const string& contenido);
    void generarDot(const string &filename);
    string renderGraphviz(const string& dotFilename, const string& imageFilename);
    vector<string> obtenerCorreos();
    Nodo<T>* getPrimero() const{return primero;};
    vector<T> RecorridoPreorden() const;
    vector<T> RecorridoInorden() const;
    vector<T> RecorridoPostorden() const;
    vector<T> ObtenerPublicaciones() const;
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
    cout << "Fin de las publicaciones!" << endl;
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

template <typename T>
void ListaDE<T>::Borrar(string contenido) {
    Nodo<T>* temp = primero;
    Nodo<T>* tempAnterior = nullptr;
    while (temp != nullptr) {
        if (temp->dato.contenido == contenido) {
            if (tempAnterior == nullptr) {
                primero = temp->siguiente;
            } else {
                tempAnterior->siguiente = temp->siguiente;
            }
            delete temp;
            return;
        }
        tempAnterior = temp;
        temp = temp->siguiente;
    }
}

template <typename T>
vector<string> ListaDE<T>::getContenidoVector(string dt)
{
    Nodo<T>* temp = primero;
    vector<string> resultados;
    while (temp != nullptr) {
        if (temp->dato.correo == dt) {
            resultados.push_back(temp->dato.contenido);
        }
        temp = temp->siguiente;
    }
    return resultados;
}

template <typename T>
Nodo<T>* ListaDE<T>::getContenido(const string& contenido) {
    Nodo<T>* temp = primero;
    while (temp != nullptr) {
        if (temp->dato.ObtenerContenido() == contenido) {
            return temp;
        }
        temp = temp->siguiente;
    }
    return nullptr;
}

template <typename T>
void ListaDE<T>::generarDot(const string &filename)
{
    ofstream file(filename);
    if (file.is_open())
    {
        file << "digraph G {" << endl;
        file << "node [shape=record];" << endl;
        file << "rankdir=LR;" << endl;

        Nodo<T>* temp = primero;
        int id = 0;
        while (temp != nullptr)
        {
            file << "node" << id << " [label=\"{" << temp->dato << "}\"];" << endl;
            if (temp->siguiente != nullptr)
            {
                file << "node" << id << " -> node" << (id + 1) << ";" << endl;
                file << "node" << (id + 1) << " -> node" << id << ";" << endl;
            }
            temp = temp->siguiente;
            id++;
        }

        file << "}" << endl;
        file.close();
    }
    else
    {
        cout << "No se pudo generar el archivo" << endl;
    }
}

template <typename T>
string ListaDE<T>::renderGraphviz(const string& dotFilename, const string& imageFilename) {
    string command = "dot -Tpng " + dotFilename + " -o " + imageFilename;
    system(command.c_str());
    return imageFilename;
}

template <typename T>
vector<string> ListaDE<T>::obtenerCorreos()
{
    Nodo<T>* temp = primero;
    vector<string> correos;
    while (temp != nullptr) {
        vector<string> partes = temp->dato.ObtenerPartes();
        correos.push_back(partes[0]);
        temp = temp->siguiente;
    }
    return correos;
};

template <typename T>
vector<T> ListaDE<T>::RecorridoPreorden() const {
    vector<T> resultado;
    std::unordered_set<Nodo<T>*> visitados;
    RecorridoPreorden(primero, resultado, visitados);
    return resultado;
}

template <typename T>
void ListaDE<T>::RecorridoPreorden(Nodo<T>* nodo, vector<T>& resultado, std::unordered_set<Nodo<T>*>& visitados) const {
    if (nodo == nullptr || visitados.find(nodo) != visitados.end()) return;
    visitados.insert(nodo); // Marcar el nodo como visitado
    resultado.push_back(nodo->dato); // Procesar el nodo
    RecorridoPreorden(nodo->siguiente, resultado, visitados); // Recorrer el siguiente nodo
}

template <typename T>
vector<T> ListaDE<T>::RecorridoInorden() const {
    vector<T> resultado;
    std::unordered_set<Nodo<T>*> visitados;
    if (primero != nullptr) {
        RecorridoInorden(primero, resultado, visitados);
    }
    return resultado;
}

template <typename T>
void ListaDE<T>::RecorridoInorden(Nodo<T>* nodo, vector<T>& resultado, std::unordered_set<Nodo<T>*>& visitados) const {
    if (nodo == nullptr || visitados.find(nodo) != visitados.end()) return; // Caso base: nodo es nulo o ya visitado
    visitados.insert(nodo); // Marcar el nodo como visitado
    if (nodo->anterior != nullptr) {
        RecorridoInorden(nodo->anterior, resultado, visitados); // Recorrer el nodo anterior
    }
    resultado.push_back(nodo->dato); // Procesar el nodo actual
    if (nodo->siguiente != nullptr) {
        RecorridoInorden(nodo->siguiente, resultado, visitados); // Recorrer el siguiente nodo
    }
}

template <typename T>
vector<T> ListaDE<T>::RecorridoPostorden() const {
    vector<T> resultado;
    std::unordered_set<Nodo<T>*> visitados;
    RecorridoPostorden(primero, resultado, visitados);
    return resultado;
}

template <typename T>
void ListaDE<T>::RecorridoPostorden(Nodo<T>* nodo, vector<T>& resultado, std::unordered_set<Nodo<T>*>& visitados) const {
    if (nodo == nullptr || visitados.find(nodo) != visitados.end()) return;
    visitados.insert(nodo); // Marcar el nodo como visitado
    if (nodo->anterior != nullptr) {
        RecorridoPostorden(nodo->anterior, resultado, visitados); // Recorrer el nodo anterior
    }
    if (nodo->siguiente != nullptr) {
        RecorridoPostorden(nodo->siguiente, resultado, visitados); // Recorrer el siguiente nodo
    }
    resultado.push_back(nodo->dato); // Procesar el nodo
}

template <typename T>
vector<T> ListaDE<T>::ObtenerPublicaciones() const {
    vector<T> resultado;
    Nodo<T>* actual = primero;
    std::unordered_set<Nodo<T>*> visitados;

    while (actual != nullptr && visitados.find(actual) == visitados.end()) {
        visitados.insert(actual); // Marcar el nodo como visitado
        resultado.push_back(actual->dato); // Añadir el dato al resultado
        actual = actual->siguiente; // Mover al siguiente nodo
    }

    return resultado;
}


#endif // LISTADE_H
