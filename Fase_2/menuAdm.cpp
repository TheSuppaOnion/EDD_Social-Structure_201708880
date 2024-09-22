#include "menuAdm.h"
#include "ui_menuAdm.h"
#include <iostream>

MenuAdm::MenuAdm(const QString &correo, QWidget *parent , QMainWindow *previousWindow) : QMainWindow(parent), ui(new Ui::MenuAdm), previousWindow(previousWindow) {
    ui->setupUi(this);
    ui->label->setText("Bienvenido(a) " + correo);

    // Conectar las señales de los botones a las ranuras correspondientes
    connect(ui->cargaUsuariosButton, &QPushButton::clicked, this, &MenuAdm::cargaUsuarios);
    connect(ui->cargaRelacionesButton, &QPushButton::clicked, this, &MenuAdm::cargaRelaciones);
    connect(ui->cargaPublicacionesButton, &QPushButton::clicked, this, &MenuAdm::cargaPublicaciones);
    connect(ui->eliminarUsuariosButton, &QPushButton::clicked, this, &MenuAdm::eliminarUsuarios);
    connect(ui->reportesButton, &QPushButton::clicked, this, &MenuAdm::reportes);
    connect(ui->cerrarSesionButton, &QPushButton::clicked, this, &MenuAdm::cerrarSesion);
}

MenuAdm::~MenuAdm() {
    delete ui;
}

void MenuAdm::cargaUsuarios() {
    QString filePath = QFileDialog::getOpenFileName(this, "Seleccionar archivo de usuarios");
    if (!filePath.isEmpty()) {
        LeerArchivo(filePath.toStdString(), 1);
        QMessageBox::information(this, "Carga de usuarios", "Archivo de usuarios cargado: " + filePath);
    }
}

void MenuAdm::cargaRelaciones() {
    // Lógica para cargar relaciones
    QMessageBox::information(this, "Carga de relaciones", "Relaciones cargadas.");
}

void MenuAdm::cargaPublicaciones() {
    QString filePath = QFileDialog::getOpenFileName(this, "Seleccionar archivo de publicaciones");
    if (!filePath.isEmpty()) {
        LeerArchivo(filePath.toStdString(), 3);
        QMessageBox::information(this, "Carga de publicaciones", "Archivo de publicaciones cargado: " + filePath);
    }
}

void MenuAdm::eliminarUsuarios() {
    limpiarConsola();
    std::string correo;
    std::cout << "Lista de usuarios" << std::endl;
    std::cout << "-------------------------------------" << std::endl;
    do {
        std::cout << "Ingrese el correo del usuario que desea eliminar: ";
        std::cin >> correo;
        // if (listausers.buscar(correo)) {
        //     listausers.Borrar(correo);
        //     std::cout << "Usuario eliminado exitosamente" << std::endl;
        //     std::this_thread::sleep_for(std::chrono::seconds(3));
        // } else {
        //     std::cout << "Usuario no encontrado" << std::endl;
        //     std::this_thread::sleep_for(std::chrono::seconds(3));
        // }
    } while (correo != "0");
}

void MenuAdm::reportes() {
    int opcionReportes;
    do {
        limpiarConsola();
        std::cout << "1. Usuarios" << std::endl;
        std::cout << "2. Relaciones de amistad" << std::endl;
        std::cout << "3. Publicaciones" << std::endl;
        std::cout << "4. Top" << std::endl;
        std::cout << "5. Regresar" << std::endl;
        std::cout << "Eliga la opcion deseada: ";
        ValidarOpcion(opcionReportes);
        switch (opcionReportes) {
        case 1:
            // Lógica para reportes de usuarios
            break;
        case 2:
            // Lógica para reportes de relaciones de amistad
            break;
        case 3:
            // Lógica para reportes de publicaciones
            break;
        case 4:
            // Lógica para reportes de top
            break;
        case 5:
            return;
        }
    } while (opcionReportes != 5);
}

void MenuAdm::cerrarSesion() {
    if (previousWindow) {
        previousWindow->show(); // Mostrar la ventana anterior
    }
    this->close(); // Cerrar la ventana actual
}

void MenuAdm::limpiarConsola() {
    // Lógica para limpiar la consola
}

void MenuAdm::LeerArchivo(const std::string &filePath, int tipo) {
    // Lógica para leer el archivo
}

void MenuAdm::ValidarOpcion(int &opcion) {
    // Lógica para validar la opción
}
