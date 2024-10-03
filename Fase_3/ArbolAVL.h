#ifndef ARBOLAVL_H
#define ARBOLAVL_H

#include "Nodos.h"
#include <fstream>
#include <vector>
#include <string>
#include <iostream>

using namespace std;

template <typename T>
class ArbolAVL {
private:
    NodoAVL<T>* raiz;
    int altura(NodoAVL<T>* nodo);
    int balanceFactor(NodoAVL<T>* nodo);
    void actualizarAltura(NodoAVL<T>* nodo);
    NodoAVL<T>* rotarDerecha(NodoAVL<T>* y);
    NodoAVL<T>* rotarIzquierda(NodoAVL<T>* x);
    NodoAVL<T>* balancear(NodoAVL<T>* nodo);
    NodoAVL<T>* Insertar(NodoAVL<T>* nodo, T dato);
    NodoAVL<T>* borrar(NodoAVL<T>* nodo, const string &dato);
    NodoAVL<T>* Encontrar(NodoAVL<T>* nodo, const string &dato);
    NodoAVL<T>* Buscar(NodoAVL<T>* nodo, const string& correo);
    void destruir(NodoAVL<T>* nodo);
    void ObtenerUsuarios(NodoAVL<T>* nodo, vector<string>& usuarios);
    void printRec(NodoAVL<T>* nodo, const string& nodeName, ofstream& file, int& nodeCount) const;
    void preorden(NodoAVL<T>* nodo, vector<T>& usuarios);
    void postorden(NodoAVL<T>* nodo, vector<T>& usuarios);
    void inorden(NodoAVL<T>* nodo, vector<T>& usuarios);
public:
    ArbolAVL(): raiz(nullptr){};
    ~ArbolAVL() {destruir(raiz);};
    void Insertar(T dato);
    bool Modificar(const string& correo, const T& nuevosDatos);
    vector<string> ObtenerUsuarios();
    bool validarLogin(const string& nombre, const string& contrasenia);
    bool arbolVacio();
    void borrar(const string& dt);
    bool Encontrar(const string& dt);
    NodoAVL<T>* Buscar(const string& correo);
    string renderGraphviz(const string& filename) const;
    void preorden(vector<T>& usuarios);
    void postorden(vector<T>& usuarios);
    void inorden(vector<T>& usuarios);
};

template <typename T>
void ArbolAVL<T>::destruir(NodoAVL<T>* nodo) {
    if (nodo) {
        destruir(nodo->izquierdo);
        destruir(nodo->derecho);
        delete nodo;
    }
}

template <typename T>
int ArbolAVL<T>::altura(NodoAVL<T>* nodo) {
    return nodo ? nodo->altura : 0;
}

template <typename T>
int ArbolAVL<T>::balanceFactor(NodoAVL<T>* nodo) {
    return nodo ? altura(nodo->izquierdo) - altura(nodo->derecho) : 0;
}

template <typename T>
void ArbolAVL<T>::actualizarAltura(NodoAVL<T>* nodo) {
    if (nodo) {
        nodo->altura = 1 + std::max(altura(nodo->izquierdo), altura(nodo->derecho));
    }
}

template <typename T>
NodoAVL<T>* ArbolAVL<T>::rotarDerecha(NodoAVL<T>* y) {
    NodoAVL<T>* x = y->izquierdo;
    NodoAVL<T>* T2 = x->derecho;

    x->derecho = y;
    y->izquierdo = T2;

    actualizarAltura(y);
    actualizarAltura(x);

    return x;
}

template <typename T>
NodoAVL<T>* ArbolAVL<T>::rotarIzquierda(NodoAVL<T>* x) {
    NodoAVL<T>* y = x->derecho;
    NodoAVL<T>* T2 = y->izquierdo;

    y->izquierdo = x;
    x->derecho = T2;

    actualizarAltura(x);
    actualizarAltura(y);

    return y;
}

template <typename T>
NodoAVL<T>* ArbolAVL<T>::balancear(NodoAVL<T>* nodo) {
    if (!nodo) return nodo;

    actualizarAltura(nodo);

    int balance = balanceFactor(nodo);

    if (balance > 1) {
        if (balanceFactor(nodo->izquierdo) < 0) {
            nodo->izquierdo = rotarIzquierda(nodo->izquierdo);
        }
        return rotarDerecha(nodo);
    }

    if (balance < -1) {
        if (balanceFactor(nodo->derecho) > 0) {
            nodo->derecho = rotarDerecha(nodo->derecho);
        }
        return rotarIzquierda(nodo);
    }

    return nodo;
}

template <typename T>
NodoAVL<T>* ArbolAVL<T>::Insertar(NodoAVL<T>* nodo, T dato) {
    if (!nodo) return new NodoAVL<T>(dato);

    if (dato < nodo->dato) {
        nodo->izquierdo = Insertar(nodo->izquierdo, dato);
    } else if (dato > nodo->dato) {
        nodo->derecho = Insertar(nodo->derecho, dato);
    } else {
        return nodo;
    }

    return balancear(nodo);
}

template <typename T>
bool ArbolAVL<T>::Modificar(const string& correo, const T& nuevosDatos) {
    NodoAVL<T>* nodo = Encontrar(raiz, correo);
    if (nodo) {
        nodo->dato = nuevosDatos;
        raiz = balancear(raiz);
        return true;
    }
    return false;
}

template <typename T>
void ArbolAVL<T>::Insertar(T dato) {
    raiz = Insertar(raiz, dato);
}

template <typename T>
void ArbolAVL<T>::ObtenerUsuarios(NodoAVL<T>* nodo, vector<string>& usuarios) {
    if (nodo) {
        ObtenerUsuarios(nodo->izquierdo, usuarios);
        usuarios.push_back(nodo->dato.toString());
        ObtenerUsuarios(nodo->derecho, usuarios);
    }
}

template <typename T>
std::vector<std::string> ArbolAVL<T>::ObtenerUsuarios() {
    std::vector<std::string> usuarios;
    ObtenerUsuarios(raiz, usuarios);
    return usuarios;
}

template <typename T>
bool ArbolAVL<T>::validarLogin(const string& correo, const string& contrasenia)
{
    NodoAVL<T>* temp = raiz;
    while (temp != nullptr) {
        if (temp->dato.correoElectronico == correo && temp->dato.contrasenia == contrasenia) {
            return true;
        }
        if (correo < temp->dato.correoElectronico) {
            temp = temp->izquierdo;
        } else {
            temp = temp->derecho;
        }
    }
    return false;
};

template <typename T>
bool ArbolAVL<T>::arbolVacio() {
    return raiz == nullptr;
}

template <typename T>
NodoAVL<T>* ArbolAVL<T>::borrar(NodoAVL<T>* nodo, const string& dato) {
    if (!nodo) return nodo;

    if (dato < nodo->dato.correoElectronico) {
        nodo->izquierdo = borrar(nodo->izquierdo, dato);
    } else if (dato > nodo->dato.correoElectronico) {
        nodo->derecho = borrar(nodo->derecho, dato);
    } else {
        if (!nodo->izquierdo || !nodo->derecho) {
            NodoAVL<T>* temp = nodo->izquierdo ? nodo->izquierdo : nodo->derecho;
            if (!temp) {
                temp = nodo;
                nodo = nullptr;
            } else {
                *nodo = *temp;
            }
            delete temp;
        } else {
            NodoAVL<T>* temp = nodo->derecho;
            while (temp->izquierdo) {
                temp = temp->izquierdo;
            }
            nodo->dato = temp->dato;
            nodo->derecho = borrar(nodo->derecho, temp->dato.correoElectronico);
        }
    }

    if (!nodo) return nodo;

    return balancear(nodo);
}

template <typename T>
void ArbolAVL<T>::borrar(const string& dt) {
    raiz = borrar(raiz, dt);
}

template <typename T>
NodoAVL<T>* ArbolAVL<T>::Encontrar(NodoAVL<T>* nodo, const string &correo) {
    if (!nodo || nodo->dato.correoElectronico == correo) return nodo;

    if (correo < nodo->dato.correoElectronico) {
        return Encontrar(nodo->izquierdo, correo);
    } else {
        return Encontrar(nodo->derecho, correo);
    }
}

template <typename T>
bool ArbolAVL<T>::Encontrar(const string& correo) {
    return Encontrar(raiz, correo) != nullptr;
}

template <typename T>
NodoAVL<T>* ArbolAVL<T>::Buscar(NodoAVL<T>* nodo, const string& correo) {
    if (!nodo || nodo->dato.correoElectronico == correo) return nodo;

    if (correo < nodo->dato.correoElectronico) {
        return Buscar(nodo->izquierdo, correo);
    } else {
        return Buscar(nodo->derecho, correo);
    }
}

template <typename T>
NodoAVL<T>* ArbolAVL<T>::Buscar(const string& correo) {
    return Buscar(raiz, correo);
}

template <typename T>
void ArbolAVL<T>::printRec(NodoAVL<T>* nodo, const string& nodeName, ofstream& file, int& nodeCount)  const {
    if (!nodo) return;

    string leftChild = "Nodo" + to_string(++nodeCount);
    string rightChild = "Nodo" + to_string(++nodeCount);

    file << "\"" << nodeName << "\" [label=\"" << nodo->dato << "\"];\n";

    if (nodo->izquierdo) {
        file << "\"" << nodeName << "\" -> \"" << leftChild << "\";\n";
        printRec(nodo->izquierdo, leftChild, file, nodeCount);
    }

    if (nodo->derecho) {
        file << "\"" << nodeName << "\" -> \"" << rightChild << "\";\n";
        printRec(nodo->derecho, rightChild, file, nodeCount);
    }
}

template <typename T>
string ArbolAVL<T>::renderGraphviz(const string& filename) const {
    string dotFilename = filename + ".dot";
    string pngFilename = filename + ".png";
    string dotCommand = "dot -Tpng " + dotFilename + " -o " + pngFilename;

    ofstream file(dotFilename);
    file << "digraph G {\n";
    file << "node [shape=circle];\n";

    if (raiz) {
        int nodeCount = 0;
        printRec(raiz, "Nodo" + to_string(++nodeCount), file, nodeCount);
    }

    file << "}\n";
    file.close();

    int result = system(dotCommand.c_str());
    if (result != 0) {
        cerr << "Error generating image\n";
        return "";
    } else {
        cout << "Image generated successfully\n";
        return pngFilename;
    }
}

template <typename T>
void ArbolAVL<T>::preorden(NodoAVL<T>* nodo, vector<T>& usuarios) {
    if (nodo != nullptr) {
        usuarios.push_back(nodo->dato);
        preorden(nodo->izquierdo, usuarios);
        preorden(nodo->derecho, usuarios);
    }
}

template <typename T>
void ArbolAVL<T>::preorden(vector<T>& usuarios) {
    preorden(raiz, usuarios);
}

template <typename T>
void ArbolAVL<T>::postorden(NodoAVL<T>* nodo, vector<T>& usuarios) {
    if (nodo != nullptr) {
        postorden(nodo->izquierdo, usuarios);
        postorden(nodo->derecho, usuarios);
        usuarios.push_back(nodo->dato);
    }
}

template <typename T>
void ArbolAVL<T>::postorden(vector<T>& usuarios) {
    postorden(raiz, usuarios);
}

template <typename T>
void ArbolAVL<T>::inorden(NodoAVL<T>* nodo, vector<T>& usuarios) {
    if (nodo != nullptr) {
        inorden(nodo->izquierdo, usuarios);
        usuarios.push_back(nodo->dato);
        inorden(nodo->derecho, usuarios);
    }
}

template <typename T>
void ArbolAVL<T>::inorden(vector<T>& usuarios) {
    inorden(raiz, usuarios);
}

#endif // ARBOLAVL_H
