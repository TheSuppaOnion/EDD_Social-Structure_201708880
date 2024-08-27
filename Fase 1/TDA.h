#include <iostream>
#include <vector>
#include <string>
#include <fstream>
#include <iomanip>

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
struct NodoPila {
    T dato;
    NodoPila<T>* siguiente;
    NodoPila(T dato) : dato(dato), siguiente(nullptr) {}
};

/*// Clase NodeVal para manejar los valores en la matriz
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
};*/


template <typename T>
class ListaSE
{
    
    private:
        Nodo<T>* primero;
        Nodo<T>* ultimo;
        string correo;

    public:
        ListaSE(): primero(nullptr), ultimo(nullptr) {}
        ListaSE(const string& correo) : primero(nullptr), ultimo(nullptr), correo(correo) {}

        ~ListaSE() {
           Nodo<T>* temp = primero;
            while (temp != nullptr) {
                Nodo<T>* siguiente = temp->siguiente;
                delete temp;
                temp = siguiente;
            }
        }
        void Insertar(T dato);
        void Imprimir();
        void ImprimirPerfil(string correo);
        bool validarLogin(string nombre, string contrasenia);
        bool ListaVacia() {return (primero == nullptr);}
        vector<string> getInformacion(string dt);
        void Borrar(string dt);
        bool buscar(string dt);
        void generarDot(const string &filename);
        void renderGraphviz(const string& dotFilename, const string& imageFilename);
};

template <typename T>
class ListaCDE
{
    private:
        Nodo<T>* primero;
        Nodo<T>* ultimo;
    public:
        
        ListaCDE(): primero(nullptr), ultimo(nullptr) {}

        ~ListaCDE() {
            Nodo<T>* temp = primero;
            while (temp != nullptr) {
                Nodo<T>* siguiente = temp->siguiente;
                delete temp;
                temp = siguiente;
            }
        }
        void Insertar(T dato);
        void Navegar(char direccion);
        void Vaciar();
        void Borrar(string contenido);
        bool ListaVacia() {return (primero == nullptr);}
        void Imprimir();
};

template <typename T>
class ListaDE
{
    private:
        Nodo<T>* primero;
        Nodo<T>* ultimo;
    
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
        void CopiarPorCorreo(const string& correo, ListaDE<T>& listaDestino);
        void Vaciar();
        void Borrar(string contenido);
        bool ListaVacia() {return (primero == nullptr);}
        vector<string> getContenido(string dt);
        void conversionListaDEaListaCDE(ListaDE<T>& listaDE, ListaCDE<T>& listaCDE);
        void generarDot(const string &filename);
        void renderGraphviz(const string& dotFilename, const string& imageFilename);
        vector<string> obtenerCorreos();
};

template <typename T>
class Pila 
{
    private:
        NodoPila<T>* tope;
    public:
        Pila() : tope(nullptr) {}
    void Push(T dato);
    void Pop();
    T Top();
    void ImprimirTope();
    void ImprimirPila();
    bool buscar(string dt);
    bool PilaVacia() {return tope == nullptr;}
};

/*template <typename T>   
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
            NodoMatriz<T>* siguiente = temp->down;
            while (temp != nullptr) {
                NodoMatriz<T>* siguiente = temp->right;
                delete temp;
                temp = siguiente;
            }
            temp = siguiente;
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
};*/