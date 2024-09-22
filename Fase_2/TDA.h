#include <functional>
#include <vector>
#include <string>
#include <iostream>

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

template <typename T>
class NodoAVL {
public:
    T dato;
    NodoAVL* izquierdo;
    NodoAVL* derecho;
    int altura;

    NodoAVL(T val) : dato(val), izquierdo(nullptr), derecho(nullptr), altura(1) {}
};

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
