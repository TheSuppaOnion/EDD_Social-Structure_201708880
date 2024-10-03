#ifndef REGISTRO_H
#define REGISTRO_H

#include <QDialog>
#include "ui_registro.h"

QT_BEGIN_NAMESPACE
namespace Ui {
class registro;
}
QT_END_NAMESPACE

class registro : public QDialog {
    Q_OBJECT

public:
    explicit registro(QWidget *parent = nullptr);
    ~registro();

private slots:
    void registrarButton();
    void regresar();

signals:
    void windowClosed();

private:
    Ui::registro *ui;
};

#endif // REGISTRO_H
