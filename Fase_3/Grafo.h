#ifndef GRAFO_H
#define GRAFO_H

#include "ListaSE.h"
#include "SimpleMap.h"
#include <iostream>

using namespace std;

// Estructura para el grafo
template <typename T>
class Grafo {
private:
    SimpleMap<T, ListaSE<T>> listaAdyacencia;

public:
    Grafo() = default;
    void agregarArista(const T& origen, const T& destino);
    void imprimirGrafo() const;
    void graphListaAdyacencia() const;
    void graphGrafo() const;
};

// Función para agregar una arista a un grafo no dirigido
template <typename T>
void Grafo<T>::agregarArista(const T& origen, const T& destino) {
    // Agregar una arista de origen a destino
    if (!listaAdyacencia.contains(origen)) {
        listaAdyacencia.insert(origen, ListaSE<T>());
    }
    listaAdyacencia.get(origen)->Insertar(destino);

    // Como el grafo es no dirigido, agregar una arista de destino a origen también
    if (!listaAdyacencia.contains(destino)) {
        listaAdyacencia.insert(destino, ListaSE<T>());
    }
    listaAdyacencia.get(destino)->Insertar(origen);
}

// Función para imprimir la representación de la lista de adyacencia del grafo
template <typename T>
void Grafo<T>::imprimirGrafo() const {
    MapNode<T, ListaSE<T>>* temp = listaAdyacencia.head;
    while (temp != nullptr) {
        cout << "\n Lista de adyacencia del vértice " << temp->key << "\n cabeza ";
        auto nodo = temp->value.obtenerPrimero();
        while (nodo) {
            cout << "-> " << nodo->dato;
            nodo = nodo->siguiente;
        }
        cout << endl;
        temp = temp->next;
    }
}

// Función para generar la representación gráfica de la lista de adyacencia
template <typename T>
void Grafo<T>::graphListaAdyacencia() const {
    ofstream file("lista_adyacencia.dot");

    file << "digraph G{" << endl;

    MapNode<T, ListaSE<T>>* temp = listaAdyacencia.head;
    while (temp != nullptr) {
        file << temp->key << "[label=\"" << temp->key << "\"];" << endl;

        auto nodo = temp->value.obtenerPrimero();
        while (nodo) {
            file << temp->key << " -> " << nodo->dato << "[dir=none];" << endl;
            nodo = nodo->siguiente;
        }
        temp = temp->next;
    }

    file << "}" << endl;
    file.close();

    string command = "dot -Tpng lista_adyacencia.dot -o lista_adyacencia.png";
    if (system(command.c_str()) == 0) {
        cout << "Lista de adyacencia creada exitosamente" << endl;
    } else {
        cout << "Error al crear la lista de adyacencia" << endl;
    }
}

// Función para generar la representación gráfica del grafo
template <typename T>
void Grafo<T>::graphGrafo() const {
    ofstream file("grafo.dot");

    file << "graph G{" << endl;

    MapNode<T, ListaSE<T>>* temp = listaAdyacencia.head;
    while (temp != nullptr) {
        auto nodo = temp->value.obtenerPrimero();
        while (nodo) {
            file << temp->key << " -- " << nodo->dato << ";" << endl;
            nodo = nodo->siguiente;
        }
        temp = temp->next;
    }

    file << "}" << endl;
    file.close();

    string command = "dot -Tpng grafo.dot -o grafo.png";
    if (system(command.c_str()) == 0) {
        cout << "Grafo creado exitosamente" << endl;
    } else {
        cout << "Error al crear el grafo" << endl;
    }
}

#endif // GRAFO_H
