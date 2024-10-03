#ifndef TDA_H
#define TDA_H

#include "ArbolAVL.h"
#include "ArbolBB.h"
#include "ArbolB.h"
#include "ListaSE.h"
#include "ListaDE.h"
#include "ListaCDE.h"
#include "Matriz.h"
#include "Pila.h"
#include <memory>
#include <vector>
#include <string>
#include <iostream>
#include <unordered_map>

using namespace std;

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
    string toString() const {
        return nombre + "," + apellido + "," + fechaNac + "," + correoElectronico + "," + contrasenia;
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
    // Sobrecargar el operador > para comparar con std::string
    bool operator>(const string& other) const {
        return correoElectronico > other;
    }

    // Sobrecargar el operador < para comparar con std::string
    bool operator<(const string& other) const {
        return correoElectronico < other;
    }

    //Sobrecargar el operador == para comparar con std::string
    bool operator==(const string& other) const {
        return correoElectronico == other;
    }
};

struct Comentario {
    string correo;
    string contenido;
    string fechayhora;
    // Constructor por defecto
    Comentario() : correo(""), contenido(""), fechayhora("") {}

    Comentario(string correo, string contenido, string fechayhora): correo(correo), contenido(contenido), fechayhora(fechayhora){}
    friend ostream& operator<<(ostream& os, const Comentario& c) {
        os << c.correo << " " << c.contenido << " " << c.fechayhora << " ";
        return os;
    }

    bool operator<(const Comentario& otro) const {
        return fechayhora < otro.fechayhora;
    }

    bool operator>(const Comentario& otro) const {
        return fechayhora > otro.fechayhora;
    }

    bool operator==(const Comentario& otro) const {
        return fechayhora == otro.fechayhora;
    }

    // Sobrecargar el operador > para comparar con std::string
    bool operator>(const string& other) const {
        return fechayhora > other;
    }

    // Sobrecargar el operador < para comparar con std::string
    bool operator<(const string& other) const {
        return fechayhora < other;
    }

    bool operator==(const string& other) const {
        return fechayhora == other;
    }

    string toString() const {
        return "Correo: " + correo + ", Contenido: " + contenido + ", Fecha y Hora: " + fechayhora; // Customize this to return the desired string representation
    }

    string ObtenerCorreo() const {
        return correo;
    }

    string ObtenerContenido() const {
        return contenido;
    }

    string ObtenerFechayHora() const {
        return fechayhora;
    }
};

struct Publicacion {
    string correo;
    string contenido;
    string fecha;
    string hora;
    ArbolB<Comentario,5> comentarios; // Árbol B que almacena comentarios indexados por fecha y hora

    Publicacion(string correo, string contenido, string fecha, string hora): correo(correo), contenido(contenido), fecha(fecha), hora(hora) {}
    friend ostream& operator<<(ostream& os, const Publicacion& p) {
        os << p.correo << " " << p.contenido << " " << p.fecha << " " << p.hora << " ";
        return os;
    }

    bool operator<(const Publicacion& otro) const {
        return fecha < otro.fecha;
    }

    bool operator>(const Publicacion& otro) const {
        return fecha > otro.fecha;
    }

    bool operator==(const Publicacion& otro) const {
        return fecha == otro.fecha;
    }

    // Sobrecargar el operador > para comparar con std::string
    bool operator>(const string& other) const {
        return fecha > other;
    }

    // Sobrecargar el operador < para comparar con std::string
    bool operator<(const string& other) const {
        return fecha < other;
    }

    bool operator==(const string& other) const {
        return fecha == other;
    }
    string ObtenerCorreo() const {
        return correo;
    }

    string ObtenerContenido() const {
        return contenido;
    }

    string ObtenerFecha() const {
        return fecha;
    }

    string ObtenerHora() const {
        return hora;
    }
    ArbolB<Comentario,5> ObtenerComentarios() const{
        return comentarios;
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

// ----------------------------------------------------- FINAL STRUCT -------------------------------------------------------------

// ----------------------------------------------------- ESTRUCTURAS GLOBALES -----------------------------------------------------

extern ArbolAVL<Usuario> listadmin;
extern ArbolAVL<Usuario> listausers;
extern ListaDE<Publicacion> listapub;
extern Matriz<Relaciones> matrizrel;
extern unordered_map<string, shared_ptr<ArbolBB<Publicacion>>> PublicacionesPorUsuario;
extern unordered_map<string, shared_ptr<ListaSE<Solicitud>>> SolicitudesEnviadasPorUsuario;
extern unordered_map<string, shared_ptr<Pila<Solicitud>>> SoolicitudesRecibidasPorUsuario;

// ----------------------------------------------------- FINAL ESTRUCTURAS GLOBALES -----------------------------------------------

#endif // TDA_H
