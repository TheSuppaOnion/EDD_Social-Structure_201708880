#ifndef LISTASE_H
#define LISTASE_H

#include "Nodos.h"
#include <fstream>
#include <vector>
#include <string>
#include <iostream>

using namespace std;

template <typename T>
class ListaSE
{

private:
    Nodo<T>* primero;
    Nodo<T>* ultimo;
    string indice;

public:
    ListaSE(): primero(nullptr), ultimo(nullptr) {}
    ListaSE(const string& indice) : primero(nullptr), ultimo(nullptr), indice(indice) {}

    ~ListaSE() {
        Nodo<T>* temp = primero;
        while (temp != nullptr) {
            Nodo<T>* siguiente = temp->siguiente;
            delete temp;
            temp = siguiente;
        }
    }
    void Insertar(T dato);
    bool ListaVacia() {return (primero == nullptr);}
    vector<string> getInformacion();
    void borrarPorFecha(string dt);
    void borrarPorCorreo(string dt);
    bool buscarPorCorreo(string dt);
    bool buscarPorFecha(string dt);
    void generarDot(const string &filename);
    void renderGraphviz(const string& dotFilename, const string& imageFilename);
    string getIndice() const { return indice; }
    Nodo<T>* obtenerPrimero() const {return primero;}
};

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
vector<string> ListaSE<T>::getInformacion()
{
    Nodo<T>* temp = primero;
    vector<string> resultados;
    while (temp != nullptr) {
        //if (temp->dato.correo == dt) {
        resultados.push_back(temp->dato.contenido);
        //}
        temp = temp->siguiente;
    }
    return resultados;
}

template <typename T>
void ListaSE<T>::borrarPorFecha(string dt)
{
    Nodo<T>* temp = primero;
    Nodo<T>* tempAnterior = nullptr;
    while (temp != nullptr) {
        if (temp->dato.fecha == dt) {
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
void ListaSE<T>::borrarPorCorreo(string dt)
{
    Nodo<T>* temp = primero;
    Nodo<T>* tempAnterior = nullptr;
    while (temp != nullptr) {
        if (temp->dato.correoElectronico == dt) {
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
bool ListaSE<T>::buscarPorCorreo(string dt){
    Nodo<T>* temp = primero;
    while (temp != nullptr) {
        if (temp->dato.correoElectronico == dt) {
            return true;
        }
        temp = temp->siguiente;
    }
    return false;
}

template <typename T>
bool ListaSE<T>::buscarPorFecha(string dt){
    Nodo<T>* temp = primero;
    while (temp != nullptr) {
        if (temp->dato.fecha == dt) {
            return true;
        }
        temp = temp->siguiente;
    }
    return false;
}

template <typename T>
void ListaSE<T>::generarDot(const string &filename)
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
void ListaSE<T>::renderGraphviz(const string& dotFilename, const string& imageFilename) {
    string command = "dot -Tpng " + dotFilename + " -o " + imageFilename;
    system(command.c_str());
}


#endif // LISTASE_H
