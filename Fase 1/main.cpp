#include <iostream>
#include "Listas.cpp"
#include <regex>
#include <conio.h>
#include <limits>
#include "Menu.cpp"

using namespace std;

int main() {
    int opcion;
    listadmin.Insertar(Usuario("Admin", "Romero", "14/09/1998", "admin@gmail.com", "EDD2S2024"));
    //listadmin.Imprimir();
    do {
        system("cls");
        cout << "Social Structure - Bismarck Romero 201708880" << endl;
        cout << "1. Iniciar Sesion" << endl;
        cout << "2. Registrarse" << endl;
        cout << "3. Informacion" << endl;
        cout << "4. Salir" << endl;
        cout << "Eliga la opcion deseada: ";
        cin >> opcion;

        switch (opcion) {
            case 1:{
                // Iniciar Sesión
                string usuario;
                string contra;

                cout << "Ingrese su nombre de usuario: ";
                cin >> usuario;
                char c;
                cout << "Ingrese su contrasenia: ";
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
                cout << endl;
                //cout << "Contrasenia ingresada: " << contra << endl;

                // Buscar nombre y contraseña en las listas
                if (listadmin.buscar(usuario, contra) || listausers.buscar(usuario, contra)) {
                    cout << "Inicio de sesion exitoso. Bienvenido" << endl;
                    this_thread::sleep_for(chrono::seconds(3));
                    // Menu de usuario
                    Usuarios(listadmin.buscar(usuario, contra));
                } else {
                    cout << "Error en el usuario o contrasenia, por favor intente de nuevo" << endl;
                    this_thread::sleep_for(chrono::seconds(3));
                    }
                }  break;
            case 2:{
                // Registrarse
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
                // Información
                break;
            case 4:
                // Salir
                cout << "Que tenga buen dia..." << endl;
                this_thread::sleep_for(chrono::seconds(2));
                system("cls");
                break;
            default:
                cout << "Por favor seleccione una opcion de la lista." << endl;
                this_thread::sleep_for(chrono::seconds(2));
                break;
        }
    } while (opcion != 4);

    return 0;
}