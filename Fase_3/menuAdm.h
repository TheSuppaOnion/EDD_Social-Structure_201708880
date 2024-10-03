#ifndef MENUADM_H
#define MENUADM_H

#include <QPushButton>
#include <QVBoxLayout>
#include <QMessageBox>
#include <QFileDialog>
#include <QLabel>
#include <QWidget>
#include "ui_menuAdm.h"

QT_BEGIN_NAMESPACE
namespace Ui {
class MenuAdm;
}
QT_END_NAMESPACE

class MenuAdm : public QMainWindow {
    Q_OBJECT

public:
    explicit MenuAdm(const QString &correo, QWidget *parent = nullptr);
    ~MenuAdm();

private slots:
    void cargaUsuarios();
    void cargaRelaciones();
    void cargaPublicaciones();
    void reportes();

public slots:
    void cerrarSesion();

signals:
    void windowClosed();

private:
    Ui::MenuAdm *ui;
};

#endif // MENUADM_H
