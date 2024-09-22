#ifndef MENUADM_H
#define MENUADM_H

#include <QMainWindow>
#include <QPushButton>
#include <QVBoxLayout>
#include <QMessageBox>
#include <QFileDialog>
#include <QLabel>
#include <QWidget>
#include <string>
#include <thread>
#include <chrono>
#include "ui_menuAdm.h" // Archivo generado por uic a partir del .ui

QT_BEGIN_NAMESPACE
namespace Ui {
class MenuAdm;
}
QT_END_NAMESPACE

class MenuAdm : public QMainWindow {
    Q_OBJECT

public:
    explicit MenuAdm(const QString &correo, QWidget *parent = nullptr, QMainWindow *previousWindow = nullptr);
    ~MenuAdm();

private slots:
    void cargaUsuarios();
    void cargaRelaciones();
    void cargaPublicaciones();
    void eliminarUsuarios();
    void reportes();

public slots:
    void cerrarSesion();

private:
    Ui::MenuAdm *ui;
    QMainWindow *previousWindow;
    //ListaUsuarios listausers; // Suponiendo que tienes una instancia de ListaUsuarios
    //MatrizRelaciones matrizrel; // Suponiendo que tienes una instancia de MatrizRelaciones

    void limpiarConsola();
    void LeerArchivo(const std::string &filePath, int tipo);
    void ValidarOpcion(int &opcion);
};

#endif // MENUADM_H
