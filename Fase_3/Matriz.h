#ifndef MATRIZ_H
#define MATRIZ_H

#include "Nodos.h"
#include <iomanip>
#include <iostream>

using namespace std;

template <typename T>
class Matriz {
private:
    NodoMatriz<T>* root = nullptr;
    int width = 0;
    int height = 0;

public:
    Matriz() : root(nullptr), width(0), height(0) {}
    ~Matriz() {
        NodoMatriz<T>* temp = root;
        while (temp != nullptr) {
            NodoMatriz<T>* siguienteFila = temp->down;
            NodoMatriz<T>* tempCol = temp;
            while (tempCol != nullptr) {
                NodoMatriz<T>* siguienteCol = tempCol->right;
                delete tempCol;
                tempCol = siguienteCol;
            }
            temp = siguienteFila;
        }
    }
    void insert(int i, int j, T dato);
    NodoMatriz<T>* searchRow(int i);
    NodoMatriz<T>* searchColumn(int j);
    bool nodeExists(NodoMatriz<T>* newNode);
    NodoMatriz<T>* insertRowHeader(int i);
    NodoMatriz<T>* insertColumnHeader(int j);
    void insertInRow(NodoMatriz<T>* newNode, NodoMatriz<T>* rowHeader);
    void insertInColumn(NodoMatriz<T>* newNode, NodoMatriz<T>* columnHeader);
    void print() const;
    void printColumnHeaders() const;
    NodeVal<T>* getValue(int i, int j) const;
};

// Método para insertar un nuevo nodo en la matriz
template <typename T>
void Matriz<T>::insert(int i, int j, T dato) {
        NodoMatriz<T>* newNode = new NodoMatriz(i, j, dato);

        if (!root) {
            root = new NodoMatriz(-1, -1, T());
        }

        NodoMatriz<T>* row = searchRow(i);
        NodoMatriz<T>* column = searchColumn(j);

        if (j > width) width = j;
        if (i > height) height = i;

        if (!nodeExists(newNode)) {
            if (!column) {
                column = insertColumnHeader(j);
            }

            if (!row) {
                row = insertRowHeader(i);
            }
            insertInColumn(newNode, row);
            insertInRow(newNode, column);
        }
}

// Método para buscar una fila por su índice
template <typename T>
NodoMatriz<T>* Matriz<T>::searchRow(int i) {
        NodoMatriz<T>* current = root;

        while (current) {
            if (current->i == i) return current;
            current = current->down;
        }
        return nullptr;
}

// Método para buscar una columna por su índice
template <typename T>
NodoMatriz<T>* Matriz<T>::searchColumn(int j) {
        NodoMatriz<T>* current = root;

        while (current) {
            if (current->j == j) return current;
            current = current->right;
        }
        return nullptr;
}

// Método para verificar si un nodo ya existe
template <typename T>
bool Matriz<T>::nodeExists(NodoMatriz<T>* newNode) {
        NodoMatriz<T>* rowHeader = root;

        while (rowHeader) {
            if (rowHeader->i == newNode->i) {
                NodoMatriz<T>* column = rowHeader;
                while (column) {
                    if (column->j == newNode->j) {
                        column->dato = newNode->dato;
                        return true;
                    }
                    column = column->right;
                }
                return false;
            }
            rowHeader = rowHeader->down;
        }
        return false;
}

// Método para insertar un encabezado de fila
template <typename T>
NodoMatriz<T>* Matriz<T>::insertRowHeader(int i) {
        NodoMatriz<T>* newRowHeader = new NodoMatriz<T>(i, -1);
        insertInRow(newRowHeader, root);
        return newRowHeader;
}

// Método para insertar un encabezado de columna
template <typename T>
NodoMatriz<T>* Matriz<T>::insertColumnHeader(int j) {
        NodoMatriz<T>* newColumnHeader = new NodoMatriz<T>(-1, j);
        insertInColumn(newColumnHeader, root);
        return newColumnHeader;
}

// Método para insertar un nodo en una fila
template <typename T>
void Matriz<T>::insertInRow(NodoMatriz<T>* newNode, NodoMatriz<T>* rowHeader) {
        NodoMatriz<T>* current = rowHeader;

        while (current->down) {
            if (newNode->i < current->down->i && newNode->i > current->i) {
                newNode->down = current->down;
                newNode->up = current;
                current->down->up = newNode;
                current->down = newNode;
                return;
            }
            current = current->down;
        }

        current->down = newNode;
        newNode->up = current;
}

// Método para insertar un nodo en una columna
template <typename T>
void Matriz<T>::insertInColumn(NodoMatriz<T>* newNode, NodoMatriz<T>* columnHeader) {
        NodoMatriz<T>* current = columnHeader;

        while (current->right) {
            if (newNode->j < current->right->j && newNode->j > current->j) {
                newNode->right = current->right;
                newNode->left = current;
                current->right->left = newNode;
                current->right = newNode;
                return;
            }
            current = current->right;
        }

        current->right = newNode;
        newNode->left = current;
}

// Método para imprimir la matriz
template <typename T>
void Matriz<T>::print() const {
        printColumnHeaders();

        for (int i = 0; i <= height; ++i) {
            cout << "\n" << setw(3) << i;
            for (int j = 0; j <= width; ++j) {
                NodeVal<T>* val = getValue(i, j);
                if (!val->exists) {
                    cout << setw(3) << "X";
                } else {
                    cout << setw(3) << val->dato;
                }
            }
        }
        cout << endl;
}

// Método para imprimir los encabezados de las columnas
template <typename T>
void Matriz<T>::printColumnHeaders() const {
        for (int j = -1; j <= width; ++j) {
            cout << setw(3) << j;
        }
}


// Método para obtener el valor de un nodo en la matriz
template <typename T>
NodeVal<T>* Matriz<T>::getValue(int i, int j) const {
        NodeVal<T>* val;
        val->exists = false;
        NodoMatriz<T>* rowHeader = root;

        while (rowHeader) {
            if (rowHeader->i == i) {
                NodoMatriz<T>* column = rowHeader;
                while (column) {
                    if (column->j == j) {
                        val->dato = column->dato;
                        val->exists = true;
                        return val;
                    }
                    column = column->right;
                }
                return val;
            }
            rowHeader = rowHeader->down;
        }
        return val;
}

#endif // MATRIZ_H
