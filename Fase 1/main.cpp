#include "TDA.cpp"
#include <regex>
#include "Menu.cpp"
#include "Utilidades.h"

using namespace std;

int main() {
    int opcion;
    setlocale(LC_ALL, "en_US.UTF-8");
    listadmin.Insertar(Usuario("Admin", "Romero", "14/09/1998", "admin@gmail.com", "EDD2S2024"));
    listausers.Insertar(Usuario("Test", "Romero", "14/09/1998", "test@ex.com", "123"));
    VerificarPila("test@ex.com");
    listausers.Insertar(Usuario("Test", "Romero", "14/09/1998", "123@ex.com", "123"));
    VerificarPila("123@ex.com");
    //listadmin.Imprimir();
    do {
        limpiarConsola();
        cout << "Social Structure - Bismarck Romero 201708880" << endl;
        cout << "1. Iniciar Sesion" << endl;
        cout << "2. Registrarse" << endl;
        cout << "3. Informacion" << endl;
        cout << "4. Salir" << endl;
        cout << "Eliga la opcion deseada: ";
        
        ValidarOpcion(opcion);

        switch (opcion) {
            case 1:{
                // Iniciar Sesión
                string correo;
                string contra;

                cout << "Ingrese su correo electronico: ";
                cin >> correo;
                cout << "Ingrese su contrasenia: ";
                ValidarContrasenia(contra);
                cout << endl;                
                //cout << "Contrasenia ingresada: " << contra << endl;

                // Buscar nombre y contraseña en las listas
                if (listadmin.validarLogin(correo, contra) || listausers.validarLogin(correo, contra)) {
                    cout << "Inicio de sesion exitoso. Bienvenido(a) " << correo << endl;
                    this_thread::sleep_for(chrono::seconds(3));
                    // Menu de usuario
                    Menu(listadmin.validarLogin(correo, contra), correo);
                } else {
                    cout << "Error en el correo o contrasenia, por favor intente de nuevo" << endl;
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

                // Validacion de fecha 
                validarFechaNacimiento(fechaNacimiento);
                // Validacion del formato correo
                validarCorreo(correo);
                
                cout << "Contrasenia: ";
                cin >> contra;

                // Añadir los datos del usuario a la lista
                listausers.Insertar(Usuario(nombres, apellidos, fechaNacimiento, correo, contra));
                VerificarPila(correo);
                //listausers.Imprimir();
                } break;
            case 3:
                // Información
                limpiarConsola();
                cout << "Social Structure es una red social creada por Bismarck Romero con carne 201708880, estudiante de la Universidad de San Carlos de Guatemala." << endl;
                cout << "La red social permite a los usuarios registrarse, iniciar sesion, crear publicaciones y hacer amigos." << endl;
                system("pause");
                break;
            case 4:
                // Salir
                cout << "Que tenga buen dia..." << endl;
                this_thread::sleep_for(chrono::seconds(2));
                break;
            default:
                cout << "Por favor seleccione una opcion de la lista." << endl;
                this_thread::sleep_for(chrono::seconds(3));
                break;
        }
    } while (opcion != 4);

    return 0;
}