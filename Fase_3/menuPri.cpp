#include "menuPri.h"
#include "menuAdm.h"
#include "menuUsr.h"
#include "registro.h"
#include "ui_menuPri.h"
#include "TDA.h"

MenuPri::MenuPri(QWidget *parent)
    : QMainWindow(parent), ui(new Ui::MenuPri) {
    ui->setupUi(this);
    // Configurar el campo de contraseña para mostrar asteriscos
    ui->inputContrasenia->setEchoMode(QLineEdit::Password);

    listadmin.Insertar(Usuario("Admin", "Romero", "14/09/1998", "admin@gmail.com", "EDD2S2024"));
    listausers.Insertar(Usuario("Test", "Romero", "14/09/1998", "test@ex.com", "123"));
    //VerificarPila("test@ex.com");
    listausers.Insertar(Usuario("Test", "Romero", "14/09/1998", "abc@ex.com", "123"));
    //VerificarPila("abc@ex.com");

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
        // Crear y mostrar la ventana del menú de administrador si es admin
        static MenuAdm *menuAdm = nullptr;
        static MenuUsr *menuUsr = nullptr;

        if (esAdmin) {
            menuAdm = new MenuAdm(correo);
            connect(menuAdm, &MenuAdm::windowClosed, this,&MenuPri::show);
            menuAdm->show();
            this->hide();
            ui->labelMensaje->setText("¡Que tenga un buen dia!");
            ui->inputCorreo->setText("");
            ui->inputContrasenia->setText("");
        } else {
            menuUsr = new MenuUsr(correo);
            connect(menuUsr, &MenuUsr::windowClosed, this, &MenuPri::show);
            menuUsr->show();
            this->hide();
            ui->labelMensaje->setText("¡Que tenga un buen dia!");
            ui->inputCorreo->setText("");
            ui->inputContrasenia->setText("");
        }

        this->close();
    } else {
        ui->labelMensaje->setText("Error en el correo o contraseña, por favor intente de nuevo");
    }
}

void MenuPri::registrarse() {
    registro *registro = new class registro();
    connect(registro, &registro::windowClosed, this, &MenuPri::show);
    registro->show();
    this->hide();
    ui->labelMensaje->setText("¡Gracias por registrarse! proceda con el inicio de sesión por favor.");
    ui->inputCorreo->setText("");
    ui->inputContrasenia->setText("");
}

void MenuPri::mostrarInformacion() {
    QMessageBox::information(this, "Informacion", "Social Structure es una red social creada por Bismarck Romero con carne 201708880, estudiante de la Universidad de San Carlos de Guatemala. \n" "La red social permite a los usuarios registrarse, iniciar sesion, crear publicaciones y hacer amigos.");
}

void MenuPri::salir() {
    QApplication::quit();
}
