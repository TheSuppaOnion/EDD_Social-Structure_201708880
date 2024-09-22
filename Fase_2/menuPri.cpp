#include "menuPri.h"
#include "menuAdm.h"
#include "ui_menuPri.h"
#include "Utilidades.h"
#include <QMessageBox>

MenuPri::MenuPri(QWidget *parent)
    : QMainWindow(parent), ui(new Ui::MenuPri) {
    ui->setupUi(this);
    // Configurar el campo de contraseña para mostrar asteriscos
    ui->inputContrasenia->setEchoMode(QLineEdit::Password);

    listadmin.Insertar(Usuario("Admin", "Romero", "14/09/1998", "admin@gmail.com", "EDD2S2024"));
    listausers.Insertar(Usuario("Test", "Romero", "14/09/1998", "test@ex.com", "123"));
    VerificarPila("test@ex.com");
    listausers.Insertar(Usuario("Test", "Romero", "14/09/1998", "123@ex.com", "123"));
    VerificarPila("123@ex.com");

    connect(ui->btnIniciarSesion, &QPushButton::clicked, this, &MenuPri::iniciarSesion);
    connect(ui->btnRegistrarse, &QPushButton::clicked, this, &MenuPri::registrarse);
    connect(ui->btnInformacion, &QPushButton::clicked, this, &MenuPri::mostrarInformacion);
    connect(ui->btnSalir, &QPushButton::clicked, this, &MenuPri::salir);
}

MenuPri::~MenuPri()
{
    delete ui;
}

void MenuPri::iniciarSesion() {
    QString correo = ui->inputCorreo->text();
    QString contra = ui->inputContrasenia->text();

    // Validación de inicio de sesión
    bool esAdmin = listadmin.validarLogin(correo.toStdString(), contra.toStdString());
    bool esUsuario = listausers.validarLogin(correo.toStdString(), contra.toStdString());

    if (esAdmin || esUsuario) {
        std::this_thread::sleep_for(std::chrono::seconds(3));

        // Crear y mostrar la ventana del menú de administrador si es admin
        if (esAdmin) {
            MenuAdm *menuAdm = new MenuAdm(correo, nullptr, this);
            menuAdm->show();
        } else {
            // Aquí puedes agregar la lógica para mostrar el menú de usuario si no es admin
        }

        this->close(); // Cerrar la ventana de inicio de sesión
    } else {
        ui->labelMensaje->setText("Error en el correo o contraseña, por favor intente de nuevo");
        std::this_thread::sleep_for(std::chrono::seconds(3));
    }
}

void MenuPri::registrarse() {
    // Implementar lógica de registro
}

void MenuPri::mostrarInformacion() {
    QMessageBox::information(this, "Informacion", "Social Structure es una red social creada por Bismarck Romero con carne 201708880, estudiante de la Universidad de San Carlos de Guatemala. \n" "La red social permite a los usuarios registrarse, iniciar sesion, crear publicaciones y hacer amigos.");
}

void MenuPri::salir() {
    QApplication::quit();
}
