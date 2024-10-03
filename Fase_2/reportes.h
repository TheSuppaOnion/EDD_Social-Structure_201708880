#ifndef REPORTES_H
#define REPORTES_H

#include "TDA.h"
#include <QPushButton>
#include <QMainWindow>
#include <QWidget>
#include <QListWidget>


namespace Ui {
class Reportes;
}

class Reportes : public QMainWindow
{
    Q_OBJECT

public:
    explicit Reportes(QWidget *parent = nullptr);
    ~Reportes();

private slots:
    void mostrarGraficas();
    void mostrarBuscarCorreo();
    void buscarCorreo();
    void preordenButton();
    void inordenButton();
    void postordenButton();
    void regresarButton();
    void updateUserList();
    void deleteUser(const QStringList &usuarioData, const QString &correo);
    void modifyUser(int row);
    void agregarFilaTabla(const Usuario& usuario);
    void resizeEvent(QResizeEvent* event);
    void zoomIn();
    void zoomOut();
    void wheelEvent(QWheelEvent* event);

signals:
    void windowClosed();

private:
    Ui::Reportes *ui;
    void mostrarGraficaArbolAVL();
    void mostrarGraficaPublicaciones();
};

#endif // REPORTES_H
