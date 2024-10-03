#ifndef MENUPRI_H
#define MENUPRI_H

#include <QMainWindow>
#include <QPushButton>
#include <QLineEdit>
#include <QLabel>
#include <QVBoxLayout>
#include <QWidget>

QT_BEGIN_NAMESPACE
namespace Ui {
class MenuPri;
}
QT_END_NAMESPACE

class MenuPri : public QMainWindow
{
    Q_OBJECT

public:
    MenuPri(QWidget *parent = nullptr);
    ~MenuPri();

private slots:
    void iniciarSesion();
    void registrarse();
    void mostrarInformacion();
    void salir();

signals:
    void windowClosed();

private:
    Ui::MenuPri *ui;
    void restaurarVentana();
};

#endif // MENUPRI_H
