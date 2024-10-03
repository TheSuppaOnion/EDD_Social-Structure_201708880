#ifndef TDA_H
#define TDA_H

#include <functional>
#include <string>
#include <fstream>
#include <vector>
#include <string>
#include <iostream>

using namespace std;

// ----------------------------------------------------- INICIO NODOS ------------------------------------------------------------------

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

template <typename T>
class NodoAVL {
public:
    T dato;
    NodoAVL* izquierdo;
    NodoAVL* derecho;
    int altura;

    NodoAVL(T val) : dato(val), izquierdo(nullptr), derecho(nullptr), altura(1) {}
};

// ----------------------------------------------------- FINAL NODOS -------------------------------------------------------------------

// ----------------------------------------------------- LISTA SIMPLEMENTE ENLAZADA ----------------------------------------------------

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
    cout << "Fin de la lista!" << endl;
};

template <typename T>
void ListaSE<T>::ImprimirPerfil(string correo)
{
    Nodo<T>* temp = primero;
    while (temp != nullptr) {
        if (temp->dato.correoElectronico == correo) {
            cout << "Nombre: " << temp->dato.nombre << endl;
            cout << "Apellido: " << temp->dato.apellido << endl;
            cout << "Fecha de nacimiento: " << temp->dato.fechaNac << endl;
            cout << "Correo electronico: " << temp->dato.correoElectronico << endl;
            cout << "Contrasenia: " << temp->dato.contrasenia << endl;
            return;
        }
        temp = temp->siguiente;
    }
};

template <typename T>
bool ListaSE<T>::validarLogin(string correo, string contrasenia)
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
vector<string> ListaSE<T>::getInformacion(string dt)
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
void ListaSE<T>::Borrar(string dt)
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
bool ListaSE<T>::buscar(string dt)
{
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

// ----------------------------------------------------- FINAL LISTA SIMPLEMENTE ENLAZADA ----------------------------------------------------

// ----------------------------------------------------- LISTA CIRCULAR DOBLEMENTE ENLAZADA --------------------------------------------------

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
void ListaCDE<T>::Insertar(T dato) {
    Nodo<T>* nuevoNodo = new Nodo<T>(dato);
    nuevoNodo->dato = dato;
    nuevoNodo->siguiente = nullptr;
    nuevoNodo->anterior = nullptr;

    if (ListaVacia()) {
        primero = nuevoNodo;
        ultimo = nuevoNodo;
        primero->siguiente = primero;
        primero->anterior = ultimo;
    } else {
        ultimo->siguiente = nuevoNodo;
        nuevoNodo->anterior = ultimo;
        nuevoNodo->siguiente = primero;
        primero->anterior = nuevoNodo;
        ultimo = nuevoNodo;
    }
}

template <typename T>
void ListaCDE<T>::Navegar(char direccion) {
    if (ListaVacia()) {
        cout << "La lista está vacía." << endl;
        return;
    }

    static Nodo<T>* temp = primero;

    if (direccion == 'I' || direccion == 'i') {
        temp = temp->anterior;
    } else if (direccion == 'D' || direccion == 'd') {
        temp = temp->siguiente;
    } else {
        cout << "Dirección inválida." << endl;
        return;
    }

    vector<string> partes = temp->dato.ObtenerPartes();
    for (size_t i = 1; i < partes.size(); ++i) {
        cout << partes[i];
        if (i < partes.size() - 1) {
            cout << " || ";
        }
    }
    cout << endl;
}

template <typename T>
void ListaCDE<T>::Vaciar() {
    Nodo<T>* temp = primero;
    while (temp != nullptr) {
        Nodo<T>* siguiente = temp->siguiente;
        delete temp;
        temp = siguiente;
        if (temp == primero) {
            break;
        }
    }
    primero = nullptr;
    ultimo = nullptr;
}

template <typename T>
void ListaCDE<T>::Imprimir()
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
        if (temp == primero) {
            break;
        }
    }
    cout << "Fin de las publicaciones!" << endl;
}

// ----------------------------------------------------- FINAL LISTA CIRCULAR DOBLEMENTE ENLAZADA --------------------------------------------

// ----------------------------------------------------- LISTA DOBLEMENTE ENLAZADA -----------------------------------------------------------
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
void ListaDE<T>::CopiarPorCorreo(const string& correo, ListaDE<T>& listaDestino) {
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
vector<string> ListaDE<T>::getContenido(string dt)
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
void ListaDE<T>::conversionListaDEaListaCDE(ListaDE<T>& listaDE, ListaCDE<T>& listaCDE) {
    Nodo<T>* temp = listaDE.primero;
    while (temp != nullptr) {
        listaCDE.Insertar(temp->dato);
        temp = temp->siguiente;
    }
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
void ListaDE<T>::renderGraphviz(const string& dotFilename, const string& imageFilename) {
    string command = "dot -Tpng " + dotFilename + " -o " + imageFilename;
    system(command.c_str());
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

// ----------------------------------------------------- FINAL LISTA DOBLEMENTE ENLAZADA --------------------------------------------

// ----------------------------------------------------- INICIO PILA --------------------------------------------------------

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

template <typename T>
void Pila<T>::Push(T dato) {
    NodoPila<T>* nuevoNodo = new NodoPila<T>(dato);
    nuevoNodo->siguiente = tope;
    tope = nuevoNodo;
}

template <typename T>
void Pila<T>::Pop() {
    if (PilaVacia()) {
        return;
    }
    NodoPila<T>* temp = tope;
    tope = tope->siguiente;
    delete temp;
}

template <typename T>
T Pila<T>::Top() {
    if (PilaVacia()) {
        throw runtime_error("La pila está vacía");
    }
    return tope->dato;
}

template <typename T>
void Pila<T>::ImprimirTope() {
    if (tope == nullptr) {
        cout << "La pila está vacía" << endl;
        return;
    }

    cout << "1. ";
    vector<string> partes = tope->dato.ObtenerPartes();
    for (size_t i = 1; i < partes.size(); ++i) {
        cout << partes[i];
        if (i < partes.size() - 1) {
            cout << " || ";
        }
    }
    cout << endl;
}

template <typename T>
void Pila<T>::ImprimirPila() {
    NodoPila<T>* temp = tope;
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
}

template <typename T>
bool Pila<T>::buscar(string dt)
{
    NodoPila<T>* temp = tope;
    while (temp != nullptr) {
        if (temp->dato.correo == dt) {
            return true;
        }
        temp = temp->siguiente;
    }
    return false;
}

// ----------------------------------------------------- FINAL PILA ---------------------------------------------------------

// ----------------------------------------------------- ARBOL AVL ----------------------------------------------------------

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
    NodoAVL<T>* Borrar(NodoAVL<T>* nodo, T dato);
    NodoAVL<T>* buscar(NodoAVL<T>* nodo, T dato);
    void destruir(NodoAVL<T>* nodo);
    void Imprimir(NodoAVL<T>* nodo);
    void ImprimirPerfil(NodoAVL<T>* nodo, const string& correo);
    void generarDot(NodoAVL<T>* nodo, ostream& out);
public:
    ArbolAVL(): raiz(nullptr){};
    ~ArbolAVL();
    void Insertar(T dato);
    void Imprimir();
    void ImprimirPerfil(const string& correo);
    bool validarLogin(const string& nombre, const string& contrasenia);
    bool arbolVacio();
    void Borrar(const string& dt);
    bool buscar(const string& dt);
    void generarDot(const string& filename);
    void renderGraphviz(const string& dotFilename, const string& imageFilename);
};

template <typename T>
ArbolAVL<T>::~ArbolAVL() {
    destruir(raiz);
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
void ArbolAVL<T>::Insertar(T dato) {
    raiz = Insertar(raiz, dato);
}

template <typename T>
void ArbolAVL<T>::destruir(NodoAVL<T>* nodo) {
    if (nodo) {
        destruir(nodo->izquierdo);
        destruir(nodo->derecho);
        delete nodo;
    }
}

template <typename T>
void ArbolAVL<T>::Imprimir(NodoAVL<T>* nodo) {
    if (nodo) {
        Imprimir(nodo->izquierdo);
        cout << nodo->dato << " ";
        Imprimir(nodo->derecho);
    }
}

template <typename T>
void ArbolAVL<T>::Imprimir() {
    Imprimir(raiz);
    cout << endl;
}

template <typename T>
void ArbolAVL<T>::ImprimirPerfil(NodoAVL<T>* nodo, const string& correo) {
    if (nodo) {
        ImprimirPerfil(nodo->izquierdo, correo);
        if (nodo->dato.getCorreo() == correo) {
            cout << nodo->dato << endl;
        }
        ImprimirPerfil(nodo->derecho, correo);
    }
}

template <typename T>
void ArbolAVL<T>::ImprimirPerfil(const string& correo) {
    ImprimirPerfil(raiz, correo);
}

template <typename T>
bool ArbolAVL<T>::validarLogin(const string& correo, const string& contrasenia) {
    std::function<bool(NodoAVL<T>*)> validar = [&](NodoAVL<T>* nodo) {
        if (!nodo) return false;
        if (nodo->dato.correoElectronico == correo && nodo->dato.contrasenia == contrasenia) {
            return true;
        }
        return validar(nodo->izquierdo) || validar(nodo->derecho);
    };
    return validar(raiz);
}

template <typename T>
bool ArbolAVL<T>::arbolVacio() {
    return raiz == nullptr;
}

template <typename T>
NodoAVL<T>* ArbolAVL<T>::Borrar(NodoAVL<T>* nodo, T dato) {
    if (!nodo) return nodo;

    if (dato < nodo->dato) {
        nodo->izquierdo = borrar(nodo->izquierdo, dato);
    } else if (dato > nodo->dato) {
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
            nodo->derecho = borrar(nodo->derecho, temp->dato);
        }
    }

    if (!nodo) return nodo;

    return balancear(nodo);
}

template <typename T>
void ArbolAVL<T>::Borrar(const string& dt) {
    raiz = borrar(raiz, dt);
}

template <typename T>
NodoAVL<T>* ArbolAVL<T>::buscar(NodoAVL<T>* nodo, T dato) {
    if (!nodo || nodo->dato == dato) return nodo;

    if (dato < nodo->dato) {
        return buscar(nodo->izquierdo, dato);
    } else {
        return buscar(nodo->derecho, dato);
    }
}

template <typename T>
bool ArbolAVL<T>::buscar(const string& dt) {
    return buscar(raiz, dt) != nullptr;
}

template <typename T>
void ArbolAVL<T>::generarDot(NodoAVL<T>* nodo, ostream& out) {
    if (nodo) {
        if (nodo->izquierdo) {
            out << nodo->dato << " -> " << nodo->izquierdo->dato << ";" << endl;
            generarDot(nodo->izquierdo, out);
        } else {
            out << nodo->dato << " -> null" << nodo->dato << "L [style=invis];" << endl;
        }
        if (nodo->derecho) {
            out << nodo->dato << " -> " << nodo->derecho->dato << ";" << endl;
            generarDot(nodo->derecho, out);
        } else {
            out << nodo->dato << " -> null" << nodo->dato << "R [style=invis];" << endl;
        }
    }
}

template <typename T>
void ArbolAVL<T>::generarDot(const string& filename) {
    ofstream out(filename);
    out << "digraph G {" << endl;
    out << "node [shape=circle];" << endl;
    if (raiz) {
        generarDot(raiz, out);
    }
    out << "}" << endl;
    out.close();
}

template <typename T>
void ArbolAVL<T>::renderGraphviz(const string& dotFilename, const string& imageFilename) {
    string command = "dot -Tpng " + dotFilename + " -o " + imageFilename;
    system(command.c_str());
}

// ----------------------------------------------------- FINAL ARBOL AVL -------------------------------------------------------

// ----------------------------------------------------- INICIO STRUCT ---------------------------------------------------------

struct Usuario {
    string nombre;
    string apellido;
    string fechaNac;
    string correoElectronico;
    string contrasenia;
    Usuario(string nombre, string apellido, string fechaNac, string correoElectronico, string contrasenia) : nombre(nombre), apellido(apellido), fechaNac(fechaNac), correoElectronico(correoElectronico), contrasenia(contrasenia){}
    friend ostream& operator<<(ostream& os, const Usuario& u) {
        os << u.nombre << " " << u.apellido << " " << u.fechaNac << " "  << u.correoElectronico << " " << u.contrasenia << " ";
        return os;
    }
    vector<string> ObtenerPartes() const {
        return {nombre, apellido, fechaNac, correoElectronico, contrasenia};
    }

    bool operator<(const Usuario& otro) const {
        return correoElectronico < otro.correoElectronico;
    }

    bool operator>(const Usuario& otro) const {
        return correoElectronico > otro.correoElectronico;
    }

    bool operator==(const Usuario& otro) const {
        return correoElectronico == otro.correoElectronico;
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

struct Solicitud {
    string usuarioemisor;
    string correoElectronico;
    string fecha;
    string hora;
    Solicitud(string usuarioemisor, string correoElectronico, string fecha, string hora) : usuarioemisor(usuarioemisor), correoElectronico(correoElectronico), fecha(fecha), hora(hora){}
    friend ostream& operator<<(ostream& os, const Solicitud& s) {
        os << s.usuarioemisor << " " << s.correoElectronico << " " << s.fecha << " " << s.hora << " ";
        return os;
    }
    vector<string> ObtenerPartes() const {
        return {usuarioemisor, correoElectronico, fecha, hora};
    }
    string ObtenerCorreo() const {
        return correoElectronico;
    }
};

struct Relaciones{
    string usuarioemisor;
    string usuarioreceptor;
    string estado;
    Relaciones(string usuarioemisor, string usuarioreceptor, string estado) : usuarioemisor(usuarioemisor), usuarioreceptor(usuarioreceptor), estado(estado){}
    friend ostream& operator<<(ostream& os, const Relaciones& r) {
        os << r.usuarioemisor << " " << r.usuarioreceptor << " " << r.estado << " ";
        return os;
    }
    vector<string> ObtenerPartes() const {
        return {usuarioemisor, usuarioreceptor, estado};
    }
};

extern ArbolAVL<Usuario> listadmin;
extern ArbolAVL<Usuario> listausers;
extern ListaDE<Publicacion> listapub;
extern ListaDE<Publicacion> listapubtemp;
extern ListaCDE<Publicacion> listapubcircular;
//Matriz<Relaciones> matrizrel;

// ----------------------------------------------------- FINAL STRUCT -------------------------------------------------------------

#endif // TDA_H
