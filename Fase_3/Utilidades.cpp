#include "Utilidades.h"
#include <iostream>
#include <limits>
#include <fstream>
#include <QMessageBox>

using namespace std;
using json = nlohmann::json;

int ValidarOpcion(int& opcion) {
    while (!(cin >> opcion)) {
        // Si la entrada no es un carácter, limpiar el error y el buffer de entrada
        cin.clear(); // Limpia el estado de error de cin
        cin.ignore(numeric_limits<streamsize>::max(), '\n'); // Ignora el resto de la línea
        cout << "Opcion invalida, por favor intente de nuevo: ";
    }
    return opcion;
}

char ValidarRespuesta(char& respuesta) {
        do {
            cin >> respuesta;
            if (cin.fail() || cin.peek() != '\n') {
                cout << "Opcion invalida, por favor intente de nuevo: ";
                cin.clear();
                cin.ignore(numeric_limits<streamsize>::max(), '\n');
                }
            } while (cin.fail() || cin.peek() != '\n');
    return respuesta;
}

pair<string, string> obtenerFechaHora() {
    // Obtener la fecha y hora actual del sistema
    time_t now = time(0);
    tm* localTime = localtime(&now);

    // Obtener la fecha y hora en formato legible
    char dateTime[100];
    strftime(dateTime, sizeof(dateTime), "%Y-%m-%d %H:%M:%S", localTime);

    // Guardar la fecha y hora en variables separadas
    string fecha = dateTime;
    fecha = fecha.substr(0, 10);
    string hora = dateTime + 11;
    return make_pair(fecha, hora);
}

string ValidarContrasenia(string& contra) {
    char c;
    while (true) {
        c = _getch();
        if (c == '\r') { // Enter
            break;
        } else if (c == '\b') { // Barra espaciadora
            if (!contra.empty()) {
                contra.pop_back();
                cout << "\b \b"; // Mover el cursor atras, imprimir espacio, mover el cursor atras de nuevo
            }
        } else {
            contra.push_back(c);
            cout << "*";
        }
    }
    cin.ignore(numeric_limits<streamsize>::max(), '\n'); // limpia el buffer del teclado
    return contra;
}

bool validarFechaNacimiento(string fechaNacimiento) {
    // Extraer año, mes y día
    int year, month, day;
    try {
        year = stoi(fechaNacimiento.substr(6, 9));
        month = stoi(fechaNacimiento.substr(3, 5));
        day = stoi(fechaNacimiento.substr(0, 2));
    } catch (invalid_argument& e) {
        QMessageBox::warning(nullptr, "Fecha de Nacimiento Inválida", "Error en la conversión.");
        return false;
    }

    // Validar los valores de año, mes y día
    if (year < 1900 || year > 2004 || month < 1 || month > 12 || day < 1 || day > 31) {
        QMessageBox::warning(nullptr, "Fecha de Nacimiento Inválida", "Valores fuera de rango.");
        return false;
    }
    return true;
}

bool validarCorreo(string correo) {
    // Verificar que el correo contenga un '@' y un '.'
    size_t atPos = correo.find('@');
    size_t dotPos = correo.find('.', atPos);

    if (atPos == string::npos || dotPos == string::npos || atPos > dotPos) {
        QMessageBox::warning(nullptr, "Correo electronico invalido", "Ingrese el correo nuevamente.");
        return false;
    }

    return true;
}

shared_ptr<ListaSE<Solicitud>> VerificarLista(const string& correo) {
    // Verificar si ya existe una lista para el usuario
    auto it = SolicitudesEnviadasPorUsuario.find(correo);
    if (it == SolicitudesEnviadasPorUsuario.end()) {
        // Si no existe, crear una nueva lista y agregarla al contenedor
        auto nuevaLista = make_shared<ListaSE<Solicitud>>(correo);
        SolicitudesEnviadasPorUsuario[correo] = nuevaLista;
        return nuevaLista;
    } else {
        // Si ya existe, retornar la lista existente
        return it->second;
    }
}

shared_ptr<Pila<Solicitud>> VerificarPila(const string& correo) {
    // Verificar si ya existe una pila para el usuario
    auto it = SoolicitudesRecibidasPorUsuario.find(correo);
    if (it == SoolicitudesRecibidasPorUsuario.end()) {
        // Si no existe, crear una nueva pila y agregarla al contenedor
        auto nuevaPila = make_shared<Pila<Solicitud>>();
        SoolicitudesRecibidasPorUsuario[correo] = nuevaPila;
        return nuevaPila;
    } else {
        // Si ya existe, retornar la pila existente
        return it->second;
    }
}

// Función para verificar si alguna cadena está vacía después de aplicar simplified()
bool verificarCamposVacios(const std::vector<QString>& campos) {
    for (const auto& campo : campos) {
        if (campo.simplified().isEmpty()) {
            return true;
        }
    }
    return false;
}

bool EliminarPila(const string& correo) {
    auto it = SoolicitudesRecibidasPorUsuario.find(correo);
    if (it != SoolicitudesRecibidasPorUsuario.end()) {
        SoolicitudesRecibidasPorUsuario.erase(it);
        return true;
    }
    return false;
}

bool EliminarPublicaciones(const string& correo){
    auto it = PublicacionesPorUsuario.find(correo);
    if (it != PublicacionesPorUsuario.end()) {
        PublicacionesPorUsuario.erase(it);
        return true;
    }
    return false;
}

string LeerArchivo(string filePath, int lista) {
    try {
        ifstream file(filePath);
        if (!file.is_open()) {
            throw runtime_error("No se pudo encontrar o abrir el archivo");
        }
            json jsonData;
            file >> jsonData;
            if(lista==1){
                for (const auto& user : jsonData) {
                    string nombres = user["nombres"];
                    string apellidos = user["apellidos"];
                    string fechaNacimiento = user["fecha_de_nacimiento"];
                    string correo = user["correo"];
                    string contra = user["contraseña"];
                    listausers.Insertar(Usuario(nombres, apellidos, fechaNacimiento, correo, contra));
                    VerificarPila(correo);
                    }
            }else if (lista==2){
                    /*for (const auto& pub : jsonData) {
                    string correo = pub["correo"];
                    string contenido = pub["contenido"];
                    string fecha = pub["fecha"];
                    string hora = pub["hora"];
                    listapub.Insertar(Publicacion(correo, contenido, fecha, hora));
                }*/
            }else if (lista==3){
                    for (const auto& pub : jsonData) {
                    string correo = pub["correo"];
                    string contenido = pub["contenido"];
                    string fecha = pub["fecha"];
                    string hora = pub["hora"];

                    // Crear la publicación
                    Publicacion publicacion(correo, contenido, fecha, hora);

                    // Iterar sobre los comentarios de la publicación
                    for (const auto& comentario : pub["comentarios"]) {
                        string correoComentario = comentario["correo"];
                        string contenidoComentario = comentario["comentario"];
                        string fechaComentario = comentario["fecha"];
                        string horaComentario = comentario["hora"];

                        // Crear un índice único concatenando la fecha y la hora del comentario
                        string fechayhoraComentario = fechaComentario + " " + horaComentario;

                        // Verificar que el comentario no esté vacío
                        if (!correoComentario.empty() && !contenidoComentario.empty() && !fechaComentario.empty() && !horaComentario.empty()) {
                            // Crear el comentario
                            Comentario comentarioObj(correoComentario, contenidoComentario, fechayhoraComentario);

                            // Insertar el comentario en el árbol B de comentarios de la publicación
                            publicacion.comentarios.insert(comentarioObj);
                        } else {
                            cout << "Comentario vacío encontrado y omitido." << endl;
                        }
                    }

                    // Insertar la publicación en la lista
                    listapub.Insertar(publicacion);

                    if (PublicacionesPorUsuario.find(correo) == PublicacionesPorUsuario.end()) {
                        // Si no existe, crear un nuevo árbol y agregarlo al unordered_map
                        std::cout << "Creando nuevo ArbolBB para el usuario: " << correo << std::endl;
                        auto arbolUsuario = std::make_shared<ArbolBB<Publicacion>>();
                        arbolUsuario->Insertar(publicacion);
                        PublicacionesPorUsuario[correo] = arbolUsuario;
                    } else {
                        // Si ya existe, agregar la publicación al árbol existente
                        std::cout << "Agregando publicación al ArbolBB existente para el usuario: " << correo << std::endl;
                        PublicacionesPorUsuario[correo]->Insertar(publicacion);
                    }
                    }
            }
                file.close();
            } catch (const exception& e) {
                cout << "Error: " << e.what() << endl;
            }
        return filePath;
}

void imprimirSolicitudesRecibidas() {
    for (const auto& [usuario, pilaSolicitudes] : SoolicitudesRecibidasPorUsuario) {
        std::cout << "Usuario: " << usuario << std::endl;

        // Usar una estructura auxiliar para almacenar temporalmente los elementos
        std::vector<Solicitud> solicitudes;

        // Transferir elementos de la pila a la estructura auxiliar sin modificar la pila original
        std::shared_ptr<Pila<Solicitud>> tempPila = pilaSolicitudes;
        while (!tempPila->PilaVacia()) {
            solicitudes.push_back(tempPila->Top());
            tempPila->Pop();
        }

        // Iterar sobre la estructura auxiliar
        for (const auto& solicitud : solicitudes) {
            std::cout << "  Solicitud de: " << solicitud.ObtenerCorreo()
            << ", Fecha: " << solicitud.fecha
            << ", Hora: " << solicitud.hora << std::endl;
        }

        // Restaurar la pila original
        for (const auto& solicitud : solicitudes) {
            pilaSolicitudes->Push(solicitud);
        }
    }
}

void limpiarConsola() {
    // ANSI escape code to clear the screen
    cout << "\033[2J\033[1;1H";
}
