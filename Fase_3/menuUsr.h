#ifndef MENUUSR_H
#define MENUUSR_H

#include <QMainWindow>
#include "ui_MenuUsr.h"

namespace Ui {
class MenuUsr;
}

class MenuUsr : public QMainWindow {
    Q_OBJECT

public:
    explicit MenuUsr(const QString &correo, QWidget *parent = nullptr);
    ~MenuUsr();

private slots:
    void pushButtonBuscar();
    void pushButtonAplicarFecha();
    void pushButtonAplicarRecorrido();
    void pushButtonCrearPublicacion();
    void pushButtonComentar(QPushButton* button);
    void pushButtonEliminar(QPushButton* button, const QString& callerMethod);
    void pushButtonVerComentarios(QPushButton* button);
    void pushButtonVerArbolComentarios(QPushButton* button);
    void pushButtonGenerarReportes();
    void pushButtonGenerarBST();
    void pushButtonModificarDatos();
    void pushButtonEliminarCuenta();
    void pushButtonCerrarSesion();

signals:
    void windowClosed();

private:
    Ui::MenuUsr *ui;
    QString correoUsuario;
    void mostrarPaginaBuscar();
    void mostrarPaginaPublicaciones();
    void mostrarPaginaSolicitudes();
    void mostrarPaginaReportes();
    void mostrarPaginaPerfil();
    void rellenarTablaUsuarios();
    void enviarSolicitud(const std::string& correoDestino);
    void rellenarTablaSolicitudesRecibidas();
    void cancelarSolicitud(const std::string& correoDestino);
    void rechazarSolicitud(const std::string& correoOrigen);
    void rellenarTablaSolicitudesEnviadas();
    void actualizarDatosUsuario();
    void rellenarComboBoxFecha();
    void llenarComboBoxBST(const std::string& usuario);
};

#endif // MENUUSR_H
