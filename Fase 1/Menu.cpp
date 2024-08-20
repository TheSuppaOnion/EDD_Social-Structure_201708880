#include <iostream>
#include <chrono>
#include <thread>
#include <fstream>
#include <nlohmann/json.hpp>

using namespace std;
using json = nlohmann::json;

void Usuarios(bool admin){
    if(admin){
        // Menu Administrador
        system("cls");
        cout << "Admin menu" << endl;
        cout << "1. Carga de usuarios" << endl;
        cout << "2. Carga de relaciones" << endl;
        cout << "3. Carga de publicaciones" << endl;
        cout << "4. Gestionar usuarios" << endl;
        cout << "5. Reportes" << endl;
        cout << "6. Cerrar sesion" << endl;

        int opcion;
        cout << "Eliga la opcion deseada: ";
        cin >> opcion;
        switch(opcion) {
            case 1:{
            // Carga de usuarios
            string filePath;
            cout << "Ingrese la direccion del archivo JSON: ";
            cin >> filePath;
            try {
                ifstream file(filePath);
                if (!file.is_open()) {
                    throw runtime_error("No se pudo encontrar o abrir el archivo");
                }
                json jsonData;
                file >> jsonData;
                for (const auto& user : jsonData) {
                    string nombres = user["nombres"];
                    string apellidos = user["apellidos"];
                    string fechaNacimiento = user["fecha_de_nacimiento"];
                    string correo = user["correo"];
                    string contra = user["contraseña"];
                    listausers.Insertar(Usuario(nombres, apellidos, fechaNacimiento, correo, contra));
                }
                cout << "Exito al cargar el archivo" << endl;
                this_thread::sleep_for(chrono::seconds(3));
                file.close();
            } catch (const exception& e) {
                cout << "Error: " << e.what() << endl;
                this_thread::sleep_for(chrono::seconds(3));
            }
            }
            break;
            case 2:
            // Cargo de relaciones
            break;
            case 3:
            // Carga de publicaciones
            break;
            case 4:
            // Gestionar usuarios
            break;
            case 5:
            // Reportes
            break;
            case 6:
            // Cerrar sesion
            cout << "Que tenga buen dia..." << endl;
            this_thread::sleep_for(chrono::seconds(3));
            return;
            default:
            cout << "Invalid choice" << endl;
            break;
        }
    } else {
        // Menu de Usuario
        system("cls");
        cout << "User menu" << endl;
        cout << "1. Perfil" << endl;
        cout << "2. Solicitudes" << endl;
        cout << "3. Publicaciones" << endl;
        cout << "4. Reportes" << endl;
        cout << "5. Cerrar sesion" << endl;

        int opcion;
        cout << "Eliga la opcion deseada: ";
        cin >> opcion;
        switch(opcion) {
            case 1:
            // Perfil
            break;
            case 2:
            // Solicitudes
            break;
            case 3:
            // Publicaciones
            break;
            case 4:
            // Reportes
            break;
            case 5:
            // Cerrar sesion
            cout << "Que tenga buen dia..." << endl;
            this_thread::sleep_for(chrono::seconds(3));
            return;
            break;
            default:
            cout << "Opcion invalida" << endl;
            break;
        }
    }
}