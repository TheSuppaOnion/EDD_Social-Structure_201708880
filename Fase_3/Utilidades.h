#ifndef UTILIDADES_H
#define UTILIDADES_H

#include "TDA.h"
#include <utility>
#include <ctime>
#include <string>
#include <conio.h>
#include <QString>
#include <nlohmann/json.hpp>

// Declaraciones de funciones
int ValidarOpcion(int& opcion);
char ValidarRespuesta(char& respuesta);
pair<string, string> obtenerFechaHora();
string ValidarContrasenia(string& contra);
bool validarFechaNacimiento(string fechaNacimiento);
bool validarCorreo(string correo);
shared_ptr<ListaSE<Solicitud>> VerificarLista(const string& correo);
shared_ptr<Pila<Solicitud>> VerificarPila(const string& correo);
bool verificarCamposVacios(const std::vector<QString>& campos);
bool EliminarPila(const string& correo);
bool EliminarPublicaciones(const string& correo);
string LeerArchivo(string filePath, int lista);
void imprimirSolicitudesRecibidas();
void limpiarConsola();

#endif // UTILIDADES_H
