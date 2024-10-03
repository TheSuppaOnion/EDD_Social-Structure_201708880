#include "TDA.h"

// Inicialización de los unordered_map
unordered_map<string, shared_ptr<ArbolBB<Publicacion>>> PublicacionesPorUsuario;
unordered_map<string, shared_ptr<ListaSE<Solicitud>>> SolicitudesEnviadasPorUsuario;
unordered_map<string, shared_ptr<Pila<Solicitud>>> SoolicitudesRecibidasPorUsuario;

// Inicialización de otras estructuras globales
ArbolAVL<Usuario> listadmin;
ArbolAVL<Usuario> listausers;
ListaDE<Publicacion> listapub;
Matriz<Relaciones> matrizrel;
