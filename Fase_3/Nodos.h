#ifndef NODOS_H
#define NODOS_H

#include <memory>

template <typename T>
class Nodo {
public:
    T dato;
    Nodo* siguiente;
    Nodo* anterior;
    Nodo(T dato) : dato(dato), siguiente(nullptr), anterior(nullptr) {}
};

template <typename T>
struct NodoPila {
    T dato;
    NodoPila<T>* siguiente;
    NodoPila(T dato) : dato(dato), siguiente(nullptr) {}
};

// Clase NodeVal para manejar los valores en la matriz
template <typename T>
class NodeVal {
public:
    bool exists = false;
    T dato;
};

// Clase Node para cada nodo de la matriz
template <typename T>
class NodoMatriz {
public:
    int i = -1, j = -1;
    T dato;
    NodoMatriz<T>* up = nullptr;
    NodoMatriz<T>* down = nullptr;
    NodoMatriz<T>* right = nullptr;
    NodoMatriz<T>* left = nullptr;

    NodoMatriz(int i = -1, int j = -1, T dato = T()) : i(i), j(j), dato(dato) {}
};

template <typename T>
class NodoAVL {
public:
    T dato;
    NodoAVL* izquierdo;
    NodoAVL* derecho;
    int altura;

    NodoAVL(T val) : dato(val), izquierdo(nullptr), derecho(nullptr), altura(1) {}
};

// Declaración adelantada de ListaSE
template <typename T>
class ListaSE;

template <typename T>
class NodoBB {
public:
    T dato;
    NodoBB* izquierdo;
    NodoBB* derecho;
    std::shared_ptr<ListaSE<T>> listaPublicaciones;

    NodoBB(T dato) : dato(dato), izquierdo(nullptr), derecho(nullptr), listaPublicaciones(std::make_shared<ListaSE<T>>()) {}
};

/*#define MAX 5
#define MIN 1

template <typename T>
class NodoB {
public:
    T val[MAX + 1];
    int num = 0;
    NodoB<T>* link[MAX + 1];
    bool hoja;

    NodoB(bool hoja) : hoja(hoja) {
        for (int i = 0; i < MAX + 1; i++) {
            link[i] = nullptr;
        }
    }
};*/

template <typename T, int ORDER>
class NodoB {
public:
    T keys[ORDER - 1];
    NodoB<T, ORDER>* children[ORDER];
    int n;
    bool leaf;

    NodoB(bool isLeaf = true) : n(0), leaf(isLeaf) {
        for (int i = 0; i < ORDER; i++)
            children[i] = nullptr;
    }
};

#endif // NODOS_H
