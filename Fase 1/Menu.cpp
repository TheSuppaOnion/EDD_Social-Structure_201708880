#include <iostream>
#include <chrono>
#include <thread>
#include <fstream>
#include <nlohmann/json.hpp>
#include <ctime>

using namespace std;
using json = nlohmann::json;

void Menu(bool admin, string correo){
    if(admin){
        // Menu Administrador

        int opcion;
        do{
        system("cls");
        cout << "Bienvenido " << correo << endl;
        cout << "1. Carga de usuarios" << endl;
        cout << "2. Carga de relaciones" << endl;
        cout << "3. Carga de publicaciones" << endl;
        cout << "4. Gestionar usuarios" << endl;
        cout << "5. Reportes" << endl;
        cout << "6. Cerrar sesion" << endl;

        cout << "Eliga la opcion deseada: ";
        while (!(cin >> opcion)) {
            // Si la entrada no es un número, limpiar el error y el buffer de entrada
            cin.clear(); // Limpia el estado de error de cin
            cin.ignore(numeric_limits<streamsize>::max(), '\n'); // Ignora el resto de la línea
            cout << "Opcion invalida, por favor intente de nuevo: ";
        }

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
            break;
            default:
            cout << "Por favor seleccione una opcion de la lista." << endl;
            this_thread::sleep_for(chrono::seconds(3));
            break;
            }
        } while(opcion!=6); 
    } else {
        // Menu de Usuario

        int opcion;
        do{
        system("cls");
        cout << "Bienvenido(a) " << correo << endl;
        cout << "1. Perfil" << endl;
        cout << "2. Solicitudes" << endl;
        cout << "3. Publicaciones" << endl;
        cout << "4. Reportes" << endl;
        cout << "5. Cerrar sesion" << endl;

        cout << "Eliga la opcion deseada: ";
        while (!(cin >> opcion)) {
            // Si la entrada no es un carácter, limpiar el error y el buffer de entrada
            cin.clear(); // Limpia el estado de error de cin
            cin.ignore(numeric_limits<streamsize>::max(), '\n'); // Ignora el resto de la línea
            cout << "Opcion invalida, por favor intente de nuevo: ";
        }

        switch(opcion) {
            case 1:
            // Perfil
            break;
            case 2:
            // Solicitudes
            break;
            case 3:
                // Publicaciones
                {
                    
                    int opcionPublicaciones;
                    do{
                    system("cls");
                    cout << "Publicaciones de " << correo << endl;
                    cout << "1. Ver todas" << endl;
                    cout << "2. Crear" << endl;
                    cout << "3. Eliminar" << endl;
                    cout << "4. Regresar" << endl;
                    cout << "Eliga la opcion deseada: ";

                    while (!(cin >> opcionPublicaciones)) {
                        // Si la entrada no es un carácter, limpiar el error y el buffer de entrada
                        cin.clear(); // Limpia el estado de error de cin
                        cin.ignore(numeric_limits<streamsize>::max(), '\n'); // Ignora el resto de la línea
                        cout << "Opcion invalida, por favor intente de nuevo: ";
                    }
                    
                    switch(opcionPublicaciones) {
                        case 1:{
                            // Ver todas
                            system("cls");
                            listapub.CopiarPorCorreo(correo, listapubtemp);
                            listapubtemp.Imprimir();
                            listapubtemp.Vaciar();
                            system("pause");
                        }break;
                        case 2:{
                            // Crear
                            string contenido;
                            cout << "Ingrese el contenido de la publicacion: ";
                            cin.ignore(); // Ignora cualquier salto de línea que haya quedado en el buffer
                            getline(cin, contenido);
                            
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

                            //cout << "Fecha y hora actual: " << dateTime << endl;
                            listapub.Insertar(Publicacion(correo, contenido, fecha, hora));
                            //listapub.Imprimir();
                            cout << "Publicacion creada exitosamente" << endl;
                            this_thread::sleep_for(chrono::seconds(3));
                            // Aquí puedes hacer algo con el contenido de la publicación, como guardarlo en una estructura de datos o mostrarlo en pantalla.
                            }break;
                        case 3:
                            // Eliminar
                            break;
                        case 4:
                            // Regresar
                            break;
                        default:
                            cout << "Por favor seleccione una opcion de la lista." << endl;
                            this_thread::sleep_for(chrono::seconds(3));
                            break;
                        }
                    } while(opcionPublicaciones!=4); 
                } 
                break;
            // Publicaciones
            
            break;
            case 4:
            // Reportes
            break;
            case 5:
            // Cerrar sesion
            cout << "Que tenga buen dia..." << endl;
            this_thread::sleep_for(chrono::seconds(3));
            break;
            break;
            default:
            cout << "Por favor seleccione una opcion de la lista." << endl;
            this_thread::sleep_for(chrono::seconds(3));
            break;
        }
    } while(opcion!=5);
    return;
  }
}