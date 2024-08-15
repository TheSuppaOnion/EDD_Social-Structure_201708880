#include <iostream>
#include "Listas.cpp"
#include <regex>
using namespace std;

struct Usuario {
    string nombre;
    string apellido;
    string fechaNac; 
    string correoElectronico;
    string contrasenia;
    Usuario(string nombre, string apellido, string fechaNac, string correoElectronico, string contrasenia) : nombre(nombre), apellido(apellido), fechaNac(fechaNac), correoElectronico(correoElectronico), contrasenia(contrasenia){}
    friend ostream& operator<<(ostream& os, const Usuario& u) {
        os << u.nombre << " " << u.apellido << " " << u.fechaNac << " " << u.correoElectronico << " " << u.contrasenia << " ";
        return os;
        }
    };
    
struct Publicacion {
    string dato;
    Publicacion(string dato) : dato(dato) {}
    /*friend ostream& operator<<(ostream& os, const Publicacion& p) {
        os << u.nombre << " " << u.apellido << " " << u.fechaNac << " " << u.correoElectronico << " " << u.contrasenia << " ";
        return os;
        }*/
    };

int main() {
    ListaSE<Usuario> listadmin;
    ListaSE<Usuario> listausers;
    int opcion;
    listadmin.Insertar(Usuario("Admin", "Romero", "14/09/1998", "admin@gmail.com", "EDD2S2024"));
    //listadmin.Imprimir();
    do {
        cout << "Social Structure - Bismarck Romero 201708880" << endl;
        cout << "1. Iniciar Sesion" << endl;
        cout << "2. Registrarse" << endl;
        cout << "3. Informacion" << endl;
        cout << "4. Salir" << endl;
        cout << "Eliga la opcion deseada: ";
        cin >> opcion;

        switch (opcion) {
            case 1:
                // Code for "Iniciar Sesión"
                break;
            case 2:{

                string nombres;
                string apellidos;
                string fechaNacimiento;
                string correo;
                string contra;

                cout << "Ingrese los siguientes datos para registrarse:" << endl;
                cout << "Nombres: ";
                cin >> nombres;
                cout << "Apellidos: ";
                cin >> apellidos;

                // Validate fechaNacimiento to only have date of birth values
                bool validFechaNacimiento = false;
                while (!validFechaNacimiento) {
                    cout << "Fecha de nacimiento (dd/mm/yyyy): ";
                    cin >> fechaNacimiento;
                
                    // validacion de fecha
                    regex dateRegex("\\d{2}/\\d{2}/\\d{4}");
                    if (!regex_match(fechaNacimiento, dateRegex)) {
                        cout << "Fecha de nacimiento invalida. Ingrese la fecha nuevamente." << endl;
                        continue;
                    }
                    // Validacion, dia, mes y año
                    int day, month, year;
                    sscanf(fechaNacimiento.c_str(), "%d/%d/%d", &day, &month, &year);
                    if (day < 1 || day > 31 || month < 1 || month > 12 || year < 1900 || year > 2022) {
                        cout << "Fecha de nacimiento invalida. Ingrese la fecha nuevamente." << endl;
                        continue;
                    }

                    validFechaNacimiento = true;
                }
                // Validate correo to only have email
                bool validCorreo = false;
                while (!validCorreo) {
                    cout << "Correo electronico: ";
                    cin >> correo;
                    // Validacion de correo
                    regex emailRegex(R"(\b[A-Za-z0-9._%+-]+@[A-Za-z0-9.-]+\.[A-Za-z]{2,}\b)");
                    if (!regex_match(correo, emailRegex)) {
                        cout << "Correo electronico invalido. Ingrese el correo nuevamente." << endl;
                        continue;
                    }
                    validCorreo = true;
                }

                cout << "Contrasenia: ";
                cin >> contra;

                // Añadir los datos del usuario a la lista
                listausers.Insertar(Usuario(nombres, apellidos, fechaNacimiento, correo, contra));
                listausers.Imprimir();
                } break;
            case 3:
                // Code for "Información"
                break;
            case 4:
                cout << "Que tenga buen dia..." << endl;
                break;
            default:
                cout << "Por favor seleccione una opcion de la lista." << endl;
                break;
        }
    } while (opcion != 4);

    return 0;
}