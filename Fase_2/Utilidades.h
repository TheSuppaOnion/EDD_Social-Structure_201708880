#ifndef UTILIDADES_H
#define UTILIDADES_H

#include "TDA.cpp"
#include <chrono>
#include <iostream>
#include <limits>
#include <thread>
#include <utility>
#include <ctime>
#include <string>
#include <conio.h>
#include <fstream>
#include <memory>
#include <unordered_map>
#include <nlohmann/json.hpp>

using namespace std;
using json = nlohmann::json;
unordered_map<string, shared_ptr<ListaSE<Solicitud>>> SolicitudesEnviadasPorUsuario;
unordered_map<string, shared_ptr<Pila<Solicitud>>> SoolicitudesRecibidasPorUsuario;

inline int ValidarOpcion(int& opcion) {
    while (!(cin >> opcion)) {
        // Si la entrada no es un carácter, limpiar el error y el buffer de entrada
        cin.clear(); // Limpia el estado de error de cin
        cin.ignore(numeric_limits<streamsize>::max(), '\n'); // Ignora el resto de la línea
        cout << "Opcion invalida, por favor intente de nuevo: ";
    }
    return opcion;
}

inline char ValidarRespuesta(char& respuesta) {
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

inline pair<string, string> obtenerFechaHora() {
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

inline string ValidarContrasenia(string& contra) {
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

inline string validarFechaNacimiento(string& fechaNacimiento) {
    bool validFechaNacimiento = false;
    while (!validFechaNacimiento) {
        cout << "Fecha de nacimiento (yyyy/mm/dd): ";
        cin >> fechaNacimiento;

        // Verificar longitud de la cadena
        if (fechaNacimiento.length() != 10) {
            cout << "Fecha de nacimiento invalida. Longitud incorrecta." << endl;
            continue;
        }

        // Verificar los caracteres en las posiciones correctas
        if (fechaNacimiento[4] != '/' || fechaNacimiento[7] != '/') {
            cout << "Fecha de nacimiento invalida. Formato incorrecto." << endl;
            continue;
        }

        // Extraer año, mes y día
        int year, month, day;
        try {
            year = stoi(fechaNacimiento.substr(0, 4));
            month = stoi(fechaNacimiento.substr(5, 2));
            day = stoi(fechaNacimiento.substr(8, 2));
        } catch (invalid_argument& e) {
            cout << "Fecha de nacimiento invalida. Error en la conversión." << endl;
            continue;
        }

        // Validar los valores de año, mes y día
        if (year < 1900 || year > 2004 || month < 1 || month > 12 || day < 1 || day > 31) {
            cout << "Fecha de nacimiento invalida. Valores fuera de rango." << endl;
            continue;
        }

        validFechaNacimiento = true;
    }
    return fechaNacimiento;
}

inline string validarCorreo(string& correo) {
    bool validCorreo = false;
    while (!validCorreo) {
        cout << "Correo electronico: ";
        cin >> correo;

        // Verificar que el correo contenga un '@' y un '.'
        size_t atPos = correo.find('@');
        size_t dotPos = correo.find('.', atPos);

        if (atPos == string::npos || dotPos == string::npos || atPos > dotPos) {
            cout << "Correo electronico invalido. Ingrese el correo nuevamente." << endl;
            continue;
        }

        validCorreo = true;
    }
    return correo;
}

inline shared_ptr<ListaSE<Solicitud>> VerificarLista(const string& correo) {
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

inline shared_ptr<Pila<Solicitud>> VerificarPila(const string& correo) {
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

inline string LeerArchivo(string filePath, int lista) {
    cout << "Ingrese la direccion del archivo JSON (incluya la extension .json): ";
    cin >> filePath;
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
                    listapub.Insertar(Publicacion(correo, contenido, fecha, hora));
                }
            }
                cout << "Exito al cargar el archivo" << endl;
                this_thread::sleep_for(chrono::seconds(3));
                file.close();
            } catch (const exception& e) {
                cout << "Error: " << e.what() << endl;
                this_thread::sleep_for(chrono::seconds(3));
            }
        return filePath;
}

inline void limpiarConsola() {
    // ANSI escape code to clear the screen
    cout << "\033[2J\033[1;1H";
}

#endif //UTILIDADES_H
