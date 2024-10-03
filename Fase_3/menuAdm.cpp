#include "menuAdm.h"
#include "ui_menuAdm.h"
#include "reportes.h"
#include "Utilidades.h"

MenuAdm::MenuAdm(const QString &correo, QWidget *parent) : QMainWindow(parent), ui(new Ui::MenuAdm){
    ui->setupUi(this);
    ui->label->setText("Bienvenido(a) " + correo);

    // Conectar las señales de los botones a las ranuras correspondientes
    connect(ui->cargaUsuariosButton, &QPushButton::clicked, this, &MenuAdm::cargaUsuarios);
    connect(ui->cargaRelacionesButton, &QPushButton::clicked, this, &MenuAdm::cargaRelaciones);
    connect(ui->cargaPublicacionesButton, &QPushButton::clicked, this, &MenuAdm::cargaPublicaciones);
    connect(ui->reportesButton, &QPushButton::clicked, this, &MenuAdm::reportes);
    connect(ui->cerrarSesionButton, &QPushButton::clicked, this, &MenuAdm::cerrarSesion);
}

MenuAdm::~MenuAdm() {
    delete ui;
}

void MenuAdm::cargaUsuarios() {
    QString filePath = QFileDialog::getOpenFileName(this, "Seleccionar archivo de usuarios", "", "Archivos JSON (*.json)");
    if (filePath.endsWith(".json", Qt::CaseInsensitive)) {
        LeerArchivo(filePath.toStdString(), 1);
        QMessageBox::information(this, "Carga de usuarios", "Archivo de usuarios cargado: " + filePath);
    } else {
        QMessageBox::warning(this, "Error de archivo", "Por favor, seleccione un archivo con extensión .json");
    }
}

void MenuAdm::cargaRelaciones() {
    // Lógica para cargar relaciones
    QMessageBox::information(this, "Carga de relaciones", "Relaciones cargadas.");
}

void MenuAdm::cargaPublicaciones() {
    QString filePath = QFileDialog::getOpenFileName(this, "Seleccionar archivo de publicaciones", "", "Archivos JSON (*.json)");
    if (!filePath.isEmpty()) {
        if (filePath.endsWith(".json", Qt::CaseInsensitive)) {
            LeerArchivo(filePath.toStdString(), 3);
            QMessageBox::information(this, "Carga de publicaciones", "Archivo de publicaciones cargado: " + filePath);
        } else {
            QMessageBox::warning(this, "Error de archivo", "Por favor, seleccione un archivo con extensión .json");
        }
    }
}

void MenuAdm::reportes() {
    Reportes *reporte = new Reportes();
    connect(reporte, &Reportes::windowClosed, this, &MenuAdm::show);
    reporte->show();
    this->hide();
}

void MenuAdm::cerrarSesion() {
    this->deleteLater();
    emit windowClosed();
}
