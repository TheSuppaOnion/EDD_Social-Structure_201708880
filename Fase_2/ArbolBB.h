#ifndef ARBOLBB_H
#define ARBOLBB_H

#include "Nodos.h"
#include <fstream>
#include <iostream>
#include <set>
#include <vector>
#include <string>

using namespace std;

template <typename T>
class ArbolBB {
private:
    NodoBB<T>* raiz;
    NodoBB<T>* Insertar(NodoBB<T>* nodo, T dato);
    NodoBB<T>* borrar(NodoBB<T>* nodo, const string &dato);
    NodoBB<T>* Encontrar(NodoBB<T>* nodo, const string &dato);
    NodoBB<T>* Buscar(NodoBB<T>* nodo, const string& correo);
    void destruir(NodoBB<T>* nodo);
    void ObtenerPublicaciones(NodoBB<T>* nodo, vector<string>& publicaciones);
    void printRec(NodoBB<T>* nodo, const string& name, ofstream& file, int& printNodeCount) const;
    void preorden(NodoBB<T>* nodo, vector<T>& publicaciones);
    void postorden(NodoBB<T>* nodo, vector<T>& publicaciones);
    void inorden(NodoBB<T>* nodo, vector<T>& publicaciones);
    void collectDatesRec(NodoBB<T>* nodo, std::set<std::string>& dates) const;
public:
    ArbolBB(): raiz(nullptr){};
    ~ArbolBB() {destruir(raiz);};
    void Insertar(T dato);
    bool Modificar(const string& correo, const T& nuevosDatos);
    vector<string> ObtenerPublicaciones();
    bool arbolVacio();
    void borrar(const string& dt);
    bool Encontrar(const string& dt);
    NodoBB<T>* Buscar(const string& correo);
    string renderGraphviz(const string& filename) const;
    void preorden(vector<T>& publicaciones);
    void postorden(vector<T>& publicaciones);
    void inorden(vector<T>& publicaciones);
    void collectDates(std::set<std::string>& dates) const;
};

template <typename T>
void ArbolBB<T>::destruir(NodoBB<T>* nodo) {
    if (nodo) {
        destruir(nodo->izquierdo);
        destruir(nodo->derecho);
        delete nodo;
    }
}

template <typename T>
NodoBB<T>* ArbolBB<T>::Insertar(NodoBB<T>* nodo, T dato) {
    if (!nodo) return new NodoBB<T>(dato);
    if (dato < nodo->dato)
        nodo->izquierdo = Insertar(nodo->izquierdo, dato);
    else if (dato > nodo->dato)
        nodo->derecho = Insertar(nodo->derecho, dato);
    else
        nodo->listaPublicaciones->Insertar(dato); // Agregar a la lista de publicaciones si la fecha ya existe
    return nodo;
}

template <typename T>
void ArbolBB<T>::Insertar(T dato) {
    raiz = Insertar(raiz, dato);
}

template <typename T>
NodoBB<T>* ArbolBB<T>::borrar(NodoBB<T>* nodo, const string &dato) {
    if (!nodo) return nodo;
    if (dato < nodo->dato)
        nodo->izquierdo = borrar(nodo->izquierdo, dato);
    else if (dato > nodo->dato)
        nodo->derecho = borrar(nodo->derecho, dato);
    else {
        if (!nodo->izquierdo) {
            NodoBB<T>* temp = nodo->derecho;
            delete nodo;
            return temp;
        } else if (!nodo->derecho) {
            NodoBB<T>* temp = nodo->izquierdo;
            delete nodo;
            return temp;
        }
        NodoBB<T>* temp = nodo->derecho;
        while (temp && temp->izquierdo)
            temp = temp->izquierdo;
        nodo->dato = temp->dato;
        nodo->derecho = borrar(nodo->derecho, temp->dato);
    }
    return nodo;
}

template <typename T>
void ArbolBB<T>::borrar(const string& dt) {
    raiz = borrar(raiz, dt);
}

template <typename T>
NodoBB<T>* ArbolBB<T>::Encontrar(NodoBB<T>* nodo, const string &dato) {
    if (!nodo || nodo->dato == dato)
        return nodo;
    if (dato < nodo->dato)
        return Encontrar(nodo->izquierdo, dato);
    return Encontrar(nodo->derecho, dato);
}

template <typename T>
bool ArbolBB<T>::Encontrar(const string& dt) {
    return Encontrar(raiz, dt) != nullptr;
}

template <typename T>
NodoBB<T>* ArbolBB<T>::Buscar(NodoBB<T>* nodo, const string& correo) {
    if (!nodo || nodo->dato == correo)
        return nodo;
    if (correo < nodo->dato)
        return Buscar(nodo->izquierdo, correo);
    return Buscar(nodo->derecho, correo);
}

template <typename T>
NodoBB<T>* ArbolBB<T>::Buscar(const string& correo) {
    return Buscar(raiz, correo);
}

template <typename T>
void ArbolBB<T>::ObtenerPublicaciones(NodoBB<T>* nodo, vector<string>& publicaciones) {
    if (nodo) {
        ObtenerPublicaciones(nodo->izquierdo, publicaciones);
        publicaciones.push_back(nodo->dato);
        ObtenerPublicaciones(nodo->derecho, publicaciones);
    }
}

template <typename T>
vector<string> ArbolBB<T>::ObtenerPublicaciones() {
    vector<string> publicaciones;
    ObtenerUsuarios(raiz, publicaciones);
    return publicaciones;
}

template <typename T>
void ArbolBB<T>::preorden(NodoBB<T>* nodo, vector<T>& publicaciones) {
    if (nodo) {
        publicaciones.push_back(nodo->dato);
        preorden(nodo->izquierdo, publicaciones);
        preorden(nodo->derecho, publicaciones);
    }
}

template <typename T>
void ArbolBB<T>::preorden(vector<T>& publicaciones) {
    preorden(raiz, publicaciones);
}

template <typename T>
void ArbolBB<T>::postorden(NodoBB<T>* nodo, vector<T>& publicaciones) {
    if (nodo) {
        postorden(nodo->izquierdo, publicaciones);
        postorden(nodo->derecho, publicaciones);
        publicaciones.push_back(nodo->dato);
    }
}

template <typename T>
void ArbolBB<T>::postorden(vector<T>& publicaciones) {
    postorden(raiz, publicaciones);
}

template <typename T>
void ArbolBB<T>::inorden(NodoBB<T>* nodo, vector<T>& publicaciones) {
    if (nodo) {
        inorden(nodo->izquierdo, publicaciones);
        publicaciones.push_back(nodo->dato);
        inorden(nodo->derecho, publicaciones);
    }
}

template <typename T>
void ArbolBB<T>::inorden(vector<T>& publicaciones) {
    inorden(raiz, publicaciones);
}

template <typename T>
bool ArbolBB<T>::arbolVacio() {
    return raiz == nullptr;
}

template <typename T>
bool ArbolBB<T>::Modificar(const string& correo, const T& nuevosDatos) {
    NodoBB<T>* nodo = Buscar(correo);
    if (nodo) {
        nodo->dato = nuevosDatos;
        return true;
    }
    return false;
}

template <typename T>
void ArbolBB<T>::printRec(NodoBB<T>* nodo, const string& name, ofstream& file, int& printNodeCount) const {
    if (nodo) {
        string left = "Nodo" + to_string(++printNodeCount);
        string right = "Nodo" + to_string(++printNodeCount);

        file << '"' << name << '"' << "[label=\"" << nodo->dato.ObtenerFecha() << "\"];\n";

        // Representar la lista simplemente enlazada (ListaSE)
        if (nodo->listaPublicaciones) {
            auto current = nodo->listaPublicaciones->obtenerPrimero();
            string prevListNode = name;
            while (current != nullptr) {
                string listNode = "Nodo" + to_string(++printNodeCount);
                file << '"' << listNode << '"' << "[label=\"" << current->dato << "\", shape=box];\n";
                file << '"' << prevListNode << "\"->\"" << listNode << "\" [style=dotted];\n";
                prevListNode = listNode;
                current = current->siguiente;
            }
        }

        if (nodo->izquierdo) {
            file << '"' << name << "\"->\"" << left << "\";\n";
            printRec(nodo->izquierdo, left, file, printNodeCount);
        }
        if (nodo->derecho) {
            file << '"' << name << "\"->\"" << right << "\";\n";
            printRec(nodo->derecho, right, file, printNodeCount);
        }
    }
}

template <typename T>
string ArbolBB<T>::renderGraphviz(const string& filename) const {
    string dotFilename = filename + ".dot";
    string pngFilename = filename + ".png";
    string dotCommand = "dot -Tpng " + dotFilename + " -o " + pngFilename;

    ofstream file(dotFilename);
    file << "digraph G {\n";
    if (raiz) {
        int printNodeCount = 0;
        printRec(raiz, "Nodo" + to_string(++printNodeCount), file, printNodeCount);
    }
    file << "}\n";
    file.close();

    int result = system(dotCommand.c_str());
    if (result != 0) {
        cerr << "Error generating image\n";
    } else {
        cout << "Image generated successfully\n";
    }
    return pngFilename;
}

template <typename T>
void ArbolBB<T>::collectDates(std::set<std::string>& dates) const {
    collectDatesRec(raiz, dates);
}

template <typename T>
void ArbolBB<T>::collectDatesRec(NodoBB<T>* nodo, std::set<std::string>& dates) const {
    if (nodo) {
        collectDatesRec(nodo->izquierdo, dates); // Recorrer el subárbol izquierdo
        dates.insert(nodo->dato.ObtenerFecha()); // Agregar la fecha al set
        collectDatesRec(nodo->derecho, dates); // Recorrer el subárbol derecho
    }
}

#endif // ARBOLBB_H
