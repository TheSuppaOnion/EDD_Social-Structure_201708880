#include <chrono>
#include <thread>
#include "Utilidades.h"
using namespace std;

void Menu(bool admin, string correo){
    if(admin){
        // Menu Administrador
        int opcion;
        do{
        limpiarConsola();
        cout << "Bienvenido " << correo << endl;
        cout << "1. Carga de usuarios" << endl;
        cout << "2. Carga de relaciones" << endl;
        cout << "3. Carga de publicaciones" << endl;
        cout << "4. Eliminar usuarios" << endl;
        cout << "5. Reportes" << endl;
        cout << "6. Cerrar sesion" << endl;

        cout << "Eliga la opcion deseada: ";
        ValidarOpcion(opcion);

        switch(opcion) {
            case 1:{
            // Carga de usuarios
            string filePath;
            LeerArchivo(filePath, 1);
            }
            break;
            case 2:
            // Cargo de relaciones
            /*matrizrel.insert(1,1,Relaciones("user1", "user2", "amigo"));
            matrizrel.print();*/
            break;
            case 3:{
            // Carga de publicaciones
            string filePath;
            LeerArchivo(filePath, 3);   
            }break;
            case 4:
            // Eliminar usuarios
            {
                limpiarConsola();
                string correo;
                cout << "Lista de usuarios" << endl;
                cout << "-------------------------------------" << endl;
                do{
                cout << "Ingrese el correo del usuario que desea eliminar: ";
                cin >> correo;
                if(listausers.buscar(correo)){
                    listausers.Borrar(correo);
                    cout << "Usuario eliminado exitosamente" << endl;
                    this_thread::sleep_for(chrono::seconds(3));
                }else{
                    cout << "Usuario no encontrado" << endl;
                    this_thread::sleep_for(chrono::seconds(3));
                }
                } while(correo!="0");
            }
            break;
            case 5:
            {
            // Reportes
            int opcionReportes;
            do{
                limpiarConsola();
                cout << "1. Usuarios" << endl;
                cout << "2. Relaciones de amistad" << endl;
                cout << "3. Publicaciones" << endl;
                cout << "4. Top" << endl;
                cout << "5. Regresar" << endl;
                cout << "Eliga la opcion deseada: ";
                ValidarOpcion(opcionReportes);
                switch(opcionReportes) {
                    case 1:
                    // Reporte de usuarios
                    {
                        limpiarConsola();
                        cout << "Reporte de usuarios" << endl;
                        listausers.generarDot("usuarios.dot");
                        listausers.renderGraphviz("usuarios.dot", "usuarios.png");
                        cout << "-------------------------------------" << endl;
                        cout << "Exito al generar el reporte de usuarios..." << endl;
                        this_thread::sleep_for(chrono::seconds(3));
                    }break;
                    case 2:
                    // Reporte de relaciones de amistad
                    {
                        /*limpiarConsola();
                        cout << "Reporte de relaciones de amistad" << endl;
                        listausers.ImprimirRelaciones();
                        cout << "-------------------------------------" << endl;
                        cout << "Presione cualquier tecla para continuar..." << endl;
                        system("pause");*/
                    }break;
                    case 3:
                    // Reporte de publicaciones
                    {
                        limpiarConsola();
                        cout << "Reporte de publicaciones" << endl;
                        listapub.generarDot("publicaciones.dot");
                        listapub.renderGraphviz("publicaciones.dot", "publicaciones.png");
                        cout << "-------------------------------------" << endl;
                        cout << "Exito al generar el reporte de publicaciones..." << endl;
                        this_thread::sleep_for(chrono::seconds(3));
                    }break;
                    case 4:
                    // Top
                    {
                        limpiarConsola();
                        cout << "Top" << endl;
                        vector<string> usuarios = listapub.obtenerCorreos();
                        unordered_map<string, int> ConteoUsuarios;
                        for (const string& user : usuarios) {
                           ConteoUsuarios[user]++;
                        }
                        vector<pair<string, int>> usuariosordenados(ConteoUsuarios.begin(), ConteoUsuarios.end());
                        sort(usuariosordenados.begin(), usuariosordenados.end(), [](const pair<string, int>& a, const pair<string, int>& b) {
                            return a.second > b.second;
                        });
                        int linea = 1;
                        for (int i = 0; i < min(5, static_cast<int>(usuariosordenados.size())); i++) {
                            cout << linea << ". " << "Usuario: " << usuariosordenados[i].first << ", Repeticiones: " << usuariosordenados[i].second << endl;
                            linea++;
                        }
                        cout << "-------------------------------------" << endl;
                        cout << "Top 5 usuarios con mas publicaciones..." << endl;
                        system("pause");
                    }break;
                    case 5:
                    // Regresar
                    break;
                    default:
                    cout << "Por favor seleccione una opcion de la lista." << endl;
                    this_thread::sleep_for(chrono::seconds(3));
                    break;
            }
            } while(opcionReportes!=5);
            }break;
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
        auto listasolicitudesenviadas = VerificarLista(correo);
        auto pilasolicitudesrecibidas = VerificarPila(correo);
        int opcion;
        do{
        limpiarConsola();
        cout << "Bienvenido(a) " << correo << endl;
        cout << "1. Perfil" << endl;
        cout << "2. Solicitudes" << endl;
        cout << "3. Publicaciones" << endl;
        cout << "4. Reportes" << endl;
        cout << "5. Cerrar sesion" << endl;

        cout << "Eliga la opcion deseada: ";
        ValidarOpcion(opcion);

        switch(opcion) {
            case 1:
            // Perfil
            {
                int opcionPerfil;
                do{
                    limpiarConsola();
                    cout << "1. Ver perfil" << endl;
                    cout << "2. Eliminar cuenta" << endl;
                    cout << "3. Regresar" << endl;

                    ValidarOpcion(opcionPerfil);

                switch (opcionPerfil) {
                    case 1:
                        // Ver perfil
                        limpiarConsola();
                        cout << "Perfil de " << correo << endl;
                        listausers.ImprimirPerfil(correo);
                        system("pause");
                        break;
                    case 2:
                        // Eliminar cuenta
                        {
                        limpiarConsola();
                        cout << "¿Está seguro que desea eliminar su cuenta? (S/N): ";
                        char respuesta;
                        ValidarRespuesta(respuesta);
                        if (respuesta == 'S' || respuesta == 's') {
                        listausers.Borrar(correo);
                        cout << "Cuenta eliminada exitosamente" << endl;
                        this_thread::sleep_for(chrono::seconds(3));
                        return;
                        }
                        else if (respuesta == 'N' || respuesta == 'n'){
                            cout << "Operacion cancelada" << endl;
                            this_thread::sleep_for(chrono::seconds(3));
                        }
                        else{
                            cout << "Opcion invalida, por favor intente de nuevo" << endl;
                            this_thread::sleep_for(chrono::seconds(3));
                        }
                    }break;
                    case 3:
                        // Regresar
                        break;
                    default:
                        cout << "Por favor seleccione una opcion de la lista." << endl;
                        this_thread::sleep_for(chrono::seconds(3));
                        break;
                    }
                } while(opcionPerfil!=3);
            }break;
            case 2:
            {
                // Solicitudes
                    int opcionSolicitudes;
                    do{
                    limpiarConsola();
                    cout << "Solicitudes de " << correo << endl;
                    cout << "1. Enviar" << endl;
                    cout << "2. Rechazar" << endl;
                    cout << "3. Aceptar" << endl;
                    cout << "4. Regresar" << endl;
                    cout << "Eliga la opcion deseada: ";

                    ValidarOpcion(opcionSolicitudes);
                    
                    switch(opcionSolicitudes) {
                        case 1:
                            // Enviar
                            {
                            string correoDestino;
                            cout << "Ingrese el correo del usuario al que desea enviar la solicitud: ";
                            cin >> correoDestino;
                            if (listausers.buscar(correoDestino)) {
                                if (!listasolicitudesenviadas->buscar(correoDestino) && correo != correoDestino) {
                                    auto pilausuariodestino = VerificarPila(correoDestino);
                                    pair<string, string> fechaHora = obtenerFechaHora();
                                    string fecha = fechaHora.first;
                                    string hora = fechaHora.second;
                                    listasolicitudesenviadas->Insertar(Solicitud(correo, correoDestino, fecha, hora));
                                    pilausuariodestino->Push(Solicitud(correoDestino, correo, fecha, hora));
                                    //listasolicitudesenviadas->Imprimir();
                                    //pilausuariodestino->ImprimirPila();
                                    cout << "Solicitud enviada exitosamente" << endl;
                                } else if(listasolicitudesenviadas->buscar(correoDestino)){
                                    cout << "Ya se ha enviado una solicitud a este usuario." << endl;
                                } else {
                                    cout << "No puede enviarse una solicitud a si mismo." << endl;
                                }
                            } else {
                                cout << "Usuario no encontrado" << endl;
                            }
                            this_thread::sleep_for(chrono::seconds(3));
                            }break;
                        case 2:
                            // Rechazar
                            {
                            if(!pilasolicitudesrecibidas->PilaVacia()){
                                limpiarConsola();
                                cout << "Solicitudes recibidas" << endl;
                                pilasolicitudesrecibidas->ImprimirTope();
                                cout << "-------------------------------------" << endl;
                                cout << "¿Seguro que quiere rechazar esta solicitud? (S/N)" << endl;
                                cout << "-------------------------------------" << endl;
                                char respuesta;
                                ValidarRespuesta(respuesta);
                                if (respuesta == 'S' || respuesta == 's') {
                                    string correoOrigen = pilasolicitudesrecibidas->Top().ObtenerCorreo();
                                    cout << "Correo origen: " << correoOrigen << endl;
                                    auto listacorreoorigen = VerificarLista(correoOrigen);
                                    listacorreoorigen->Borrar(correo);
                                    pilasolicitudesrecibidas->Pop();
                                    //listasolicitudesenviadas->Imprimir();
                                    //listacorreoorigen->Imprimir();
                                    //pilasolicitudesrecibidas->ImprimirPila();
                                    cout << "Solicitud rechazada exitosamente" << endl;
                                    this_thread::sleep_for(chrono::seconds(3));
                                }
                                else if (respuesta == 'N' || respuesta == 'n'){
                                    cout << "Operacion cancelada" << endl;
                                    this_thread::sleep_for(chrono::seconds(3));
                                }
                                else{
                                    cout << "Opcion invalida, por favor intente de nuevo" << endl;
                                    this_thread::sleep_for(chrono::seconds(3));
                                }
                            }
                            }break;
                        case 3:
                            // Aceptar
                            {
                            /*string correoOrigen;
                            cout << "Solicitudes de " << correo << endl;
                            listausers.ImprimirSolicitudes(correo);
                            cout << "-------------------------------------" << endl;
                            cout << "Ingrese el correo del usuario que desea aceptar: ";
                            cin >> correoOrigen;
                            if (listausers.buscarSolicitud(correo, correoOrigen)) {
                                listausers.BorrarSolicitud(correo, correoOrigen);
                                listausers.InsertarRelacion(correo, correoOrigen);
                                cout << "Solicitud aceptada exitosamente" << endl;
                                this_thread::sleep_for(chrono::seconds(3));
                            } else {
                                cout << "Usuario no encontrado" << endl;
                                this_thread::sleep_for(chrono::seconds(3));
                            }*/
                            }break;
                        case 4:
                            // Regresar
                            break;
                        default:
                            cout << "Por favor seleccione una opcion de la lista." << endl;
                            this_thread::sleep_for(chrono::seconds(3));
                            break;
                    }
                } while(opcionSolicitudes!=4);   
            } break;
            case 3:
                // Publicaciones
                {
                    
                    int opcionPublicaciones;
                    do{
                    limpiarConsola();
                    cout << "Publicaciones de " << correo << endl;
                    cout << "1. Ver todas" << endl;
                    cout << "2. Crear" << endl;
                    cout << "3. Eliminar" << endl;
                    cout << "4. Regresar" << endl;
                    cout << "Eliga la opcion deseada: ";

                    ValidarOpcion(opcionPublicaciones);
                    
                    switch(opcionPublicaciones) {
                        case 1:{
                            // Ver todas
                            limpiarConsola();
                            cout << "Publicaciones de " << correo << endl;
                            cout << "-------------------------------------" << endl;
                            listapub.CopiarPorCorreo(correo, listapubtemp);
                            listapubtemp.conversionListaDEaListaCDE(listapubtemp, listapubcircular);
                            // Navegar en las publicaciones
                            char direccion;
                            cout << "Presione 'I' para ir a la publicacion anterior o 'D' para ir a la siguiente: ";
                            do{
                            ValidarRespuesta(direccion);
                            if (direccion == 'I' || direccion == 'i') {
                                cout << "-----------------------------------------------------------------------------" << endl;
                                listapubcircular.Navegar(direccion);
                                cout << "Presione 'I' para ir a la publicacion anterior o 'D' para ir a la siguiente: ";
                            } else if (direccion == 'D' || direccion == 'd') {
                                cout << "-----------------------------------------------------------------------------" << endl;
                                listapubcircular.Navegar(direccion);
                                cout << "Presione 'I' para ir a la publicacion anterior o 'D' para ir a la siguiente: ";
                            }
                            }while(direccion!='0');
                            listapubtemp.Vaciar();
                            listapubcircular.Vaciar();
                            limpiarConsola();
                        }break;
                        case 2:{
                            // Crear
                            string contenido;
                            cout << "Ingrese el contenido de la publicacion: ";
                            cin.ignore(); // Ignora cualquier salto de línea que haya quedado en el buffer
                            getline(cin, contenido);
                            
                            pair<string, string> fechaHora = obtenerFechaHora();
                            string fecha = fechaHora.first;
                            string hora = fechaHora.second;

                            //cout << "Fecha y hora actual: " << dateTime << endl;
                            listapub.Insertar(Publicacion(correo, contenido, fecha, hora));
                            //listapub.Imprimir();
                            cout << "Publicacion creada exitosamente" << endl;
                            this_thread::sleep_for(chrono::seconds(3));
                            // Aquí puedes hacer algo con el contenido de la publicación, como guardarlo en una estructura de datos o mostrarlo en pantalla.
                            }break;
                        case 3:{
                            // Eliminar
                            limpiarConsola();
                            listapub.CopiarPorCorreo(correo, listapubtemp);
                            cout << "Publicaciones de " << correo << endl;
                            cout << "-------------------------------------" << endl;
                            listapubtemp.Imprimir();
                            vector<string> publicaciones = listapubtemp.getContenido(correo);
                            cout << "-------------------------------------" << endl;
                            int num;
                            if(publicaciones.size() == 0){
                                cout << "No hay publicaciones para eliminar" << endl;
                                this_thread::sleep_for(chrono::seconds(3));
                                break;
                            }
                            else{
                                do{
                                    cout << "Numero de publicaciones de" << correo << " es: " << publicaciones.size() <<endl;
                                    cout << "-------------------------------------" << endl;
                                    cout << "Ingrese el numero de la publicacion que desea eliminar: ";
                                    ValidarOpcion(num);
                                } while(num!=0); 
                                if(num!=0){
                                    listapub.Borrar(publicaciones[num-1]);
                                    listapubtemp.Vaciar();
                                }else{break;}
                            }
                           }break;
                        case 4:
                            // Regresar
                            break;
                        default:
                            cout << "Por favor seleccione una opcion de la lista." << endl;
                            this_thread::sleep_for(chrono::seconds(3));
                            break;
                        }
                    } while(opcionPublicaciones!=4); 
                }break;
            case 4:
            // Reportes
            break;
            case 5:
            // Cerrar sesion
            cout << "Que tenga buen dia..." << endl;
            this_thread::sleep_for(chrono::seconds(3));
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