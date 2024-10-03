#include "registro.h"
#include "Utilidades.h"
#include <QMessageBox>

registro::registro(QWidget *parent) : QDialog(parent), ui(new Ui::registro){
    ui->setupUi(this);
    ui->contraseniaLineEdit->setEchoMode(QLineEdit::Password);
    connect(ui->registrarButton, &QPushButton::clicked, this, &registro::registrarButton);
    connect(ui->regresar, &QPushButton::clicked, this, &registro::regresar);
}

registro::~registro() {
    delete ui;
}

void registro::registrarButton() {
    QString nombres = ui->nombresLineEdit->text().simplified();
    QString apellidos = ui->apellidosLineEdit->text().simplified();
    string fechaNacimiento = ui->fechaNacimiento->date().toString("dd/MM/yyyy").toStdString();
    string correo = ui->correoLineEdit->text().simplified().toStdString();
    QString contra = ui->contraseniaLineEdit->text().simplified();

    // Verificar si los campos están vacíos después de simplificar
    vector<QString> campos = {nombres, apellidos, QString::fromStdString(correo), contra};
    if (verificarCamposVacios(campos)) {
        QMessageBox::warning(this, "Registro", "Por favor, complete todos los campos.");
        return;
    }
    // Añadir los datos del usuario a la lista
    if(validarFechaNacimiento(fechaNacimiento) && validarCorreo(correo)){
        if(!listausers.Encontrar(correo)){
            listausers.Insertar(Usuario(nombres.toStdString(), apellidos.toStdString(), fechaNacimiento, correo, contra.toStdString()));
            VerificarPila(correo);
            QMessageBox::information(this, "Registro", "Usuario registrado exitosamente.");
        } else { QMessageBox::warning(nullptr, "Usuario ya existente", "El correo electronico ya existe en nuestro sistema."); }
    }
}

void registro::regresar() {
    this->hide();
    emit windowClosed();
}
