#include "reportes.h"
#include "Utilidades.h"
#include "ui_reportes.h"
#include <QMessageBox>
#include <QPixmap>
#include <QWheelEvent>

Reportes::Reportes(QWidget *parent) : QMainWindow(parent), ui(new Ui::Reportes){
    ui->setupUi(this);

    // Set up connections
    connect(ui->actionMostrarGraficas, &QAction::triggered, this, &Reportes::mostrarGraficas);
    connect(ui->actionBuscarCorreo, &QAction::triggered, this, &Reportes::mostrarBuscarCorreo);
    connect(ui->buscarCorreoButton, &QPushButton::clicked, this, &Reportes::buscarCorreo);
    connect(ui->actualizarButton, &QPushButton::clicked, this, &Reportes::updateUserList);
    connect(ui->preordenButton, &QPushButton::clicked, this, &Reportes::preordenButton);
    connect(ui->inordenButton, &QPushButton::clicked, this, &Reportes::inordenButton);
    connect(ui->postordenButton, &QPushButton::clicked, this, &Reportes::postordenButton);
    connect(ui->regresarButton, &QPushButton::clicked, this, &Reportes::regresarButton);

    ui->resultadosTableWidget->setColumnCount(6);
    QStringList headers = {"Nombre", "Apellido", "Fecha de Nacimiento", "Correo Electrónico", "Contraseña", "Acciones"};
    ui->resultadosTableWidget->setHorizontalHeaderLabels(headers);
    ui->resultadosTableWidget->setSelectionBehavior(QAbstractItemView::SelectRows); // Allow row selection
    ui->resultadosTableWidget->setSelectionMode(QAbstractItemView::SingleSelection); // Single row selection
    updateUserList();
}

Reportes::~Reportes(){
    delete ui;
}

void Reportes::updateUserList(){
    ui->resultadosTableWidget->setRowCount(0); // Clear existing rows
    vector<string> usuarios = listausers.ObtenerUsuarios();
    for (const string& usuarioStr : usuarios) {
        QStringList usuarioData = QString::fromStdString(usuarioStr).split(",");
        int row = ui->resultadosTableWidget->rowCount();
        ui->resultadosTableWidget->insertRow(row);

        for (int col = 0; col < usuarioData.size(); ++col) {
            QTableWidgetItem *item = new QTableWidgetItem(usuarioData[col]);
            if (col == 3) { // Deshabilitar edición solo para la columna 3
                item->setFlags(item->flags() & ~Qt::ItemIsEditable);
            } else {
                item->setFlags(item->flags() | Qt::ItemIsEditable);
            }
            ui->resultadosTableWidget->setItem(row, col, item);
        }
        // Add buttons for each row
        QWidget *widget = new QWidget();
        QHBoxLayout *layout = new QHBoxLayout(widget);
        QPushButton *modifyButton = new QPushButton("Modificar");
        QPushButton *deleteButton = new QPushButton("Eliminar");
        layout->addWidget(modifyButton);
        layout->addWidget(deleteButton);
        layout->setAlignment(Qt::AlignCenter);
        layout->setContentsMargins(0, 0, 0, 0);
        widget->setLayout(layout);
        ui->resultadosTableWidget->setCellWidget(row, 5, widget);

        // Connect buttons to slots
        connect(modifyButton, &QPushButton::clicked, this, [this]() {
            int row = ui->resultadosTableWidget->currentRow();
            if (row >= 0) {
                modifyUser(row);
            }
        });
        connect(deleteButton, &QPushButton::clicked, this, [this, usuarioData]() { deleteUser(usuarioData, QString()); });
    }
    // Ajustar el ancho de las columnas al contenido
    ui->resultadosTableWidget->resizeColumnsToContents();
}

void Reportes::deleteUser(const QStringList &usuarioData, const QString &correo){
    QString userEmail;

    if (!correo.isNull()) {
        userEmail = correo;
    } else {
        userEmail = usuarioData[3]; // Correo Electrónico está en la columna 3
    }

    listausers.borrar(userEmail.toStdString());
    bool resultPila = EliminarPila(userEmail.toStdString());
    bool resultPubli = EliminarPublicaciones(userEmail.toStdString());
    SolicitudesEnviadasPorUsuario.erase(userEmail.toStdString());
    SoolicitudesRecibidasPorUsuario.erase(userEmail.toStdString());
    QString cadena = resultPila ? "true" : "false";
    QString cadena1 = resultPubli ? "true" : "false";
    QMessageBox::information(this, "Eliminar Usuario", "Usuario " + correo + " eliminado." + "solicitudes " + cadena + "Publicaciones " + cadena1);
    updateUserList(); // Refresh the table
}

void Reportes::modifyUser(int row){
    // Desconectar cualquier señal previa para evitar múltiples conexiones
    disconnect(ui->resultadosTableWidget, &QTableWidget::itemChanged, this, nullptr);

    // Connect a signal to save changes when editing is finished
    connect(ui->resultadosTableWidget, &QTableWidget::itemChanged, this, [this, row](QTableWidgetItem *item) {
        if (item->row() == row) {
            // Get the updated user data from the table
            QString nombre = ui->resultadosTableWidget->item(row, 0)->text();
            QString apellido = ui->resultadosTableWidget->item(row, 1)->text();
            QString fechaNacimiento = ui->resultadosTableWidget->item(row, 2)->text();
            QString correo = ui->resultadosTableWidget->item(row, 3)->text();
            QString contrasena = ui->resultadosTableWidget->item(row, 4)->text();

            // Crear un objeto Usuario con los nuevos datos
            Usuario nuevosDatos(nombre.toStdString(), apellido.toStdString(), fechaNacimiento.toStdString(), correo.toStdString(), contrasena.toStdString());

            // Update the user in the AVL tree
            bool result = listausers.Modificar(correo.toStdString(), nuevosDatos);
            QString cadena = result ? "true" : "false";
            QMessageBox::information(this, "Modificar Usuario", "Usuario " + correo + " modificado." + cadena);

            // Desconectar la señal para evitar bucles infinitos y deshabilitar la edición
            disconnect(ui->resultadosTableWidget, &QTableWidget::itemChanged, this, nullptr);
        }
    });
}

void Reportes::mostrarGraficas(){
    mostrarGraficaArbolAVL();
    mostrarGraficaPublicaciones();
    ui->stackedWidget->setCurrentWidget(ui->paginaGraficas);

    // Ajustar la imagen al tamaño del QGraphicsView
    ui->graficaAVL->fitInView(ui->graficaAVL->scene()->itemsBoundingRect(), Qt::KeepAspectRatio);
}

void Reportes::mostrarBuscarCorreo(){
    ui->stackedWidget->setCurrentWidget(ui->paginaBuscar);
}

void Reportes::agregarFilaTabla(const Usuario& usuario) {
    int row = ui->resultadosTableWidget->rowCount();
    ui->resultadosTableWidget->insertRow(row);

    QTableWidgetItem *nombreItem = new QTableWidgetItem(QString::fromStdString(usuario.nombre));
    QTableWidgetItem *apellidoItem = new QTableWidgetItem(QString::fromStdString(usuario.apellido));
    QTableWidgetItem *fechaNacimientoItem = new QTableWidgetItem(QString::fromStdString(usuario.fechaNac));
    QTableWidgetItem *correoItem = new QTableWidgetItem(QString::fromStdString(usuario.correoElectronico));
    QTableWidgetItem *contrasenaItem = new QTableWidgetItem(QString::fromStdString(usuario.contrasenia));

    // Hacer que la columna de correo no sea editable
    correoItem->setFlags(correoItem->flags() & ~Qt::ItemIsEditable);

    ui->resultadosTableWidget->setItem(row, 0, nombreItem);
    ui->resultadosTableWidget->setItem(row, 1, apellidoItem);
    ui->resultadosTableWidget->setItem(row, 2, fechaNacimientoItem);
    ui->resultadosTableWidget->setItem(row, 3, correoItem);
    ui->resultadosTableWidget->setItem(row, 4, contrasenaItem);

    // Add buttons for the row
    QWidget *widget = new QWidget();
    QHBoxLayout *layout = new QHBoxLayout(widget);
    QPushButton *modifyButton = new QPushButton("Modificar", this);
    QPushButton *deleteButton = new QPushButton("Eliminar");
    layout->addWidget(modifyButton);
    layout->addWidget(deleteButton);
    layout->setAlignment(Qt::AlignCenter);
    layout->setContentsMargins(0, 0, 0, 0);
    widget->setLayout(layout);
    ui->resultadosTableWidget->setCellWidget(row, 5, widget);

    // Connect buttons to slots
    connect(modifyButton, &QPushButton::clicked, this, [this]() {
        int row = ui->resultadosTableWidget->currentRow();
        if (row >= 0) {
            modifyUser(row);
        }
    });
    connect(deleteButton, &QPushButton::clicked, this, [this, correo = QString::fromStdString(usuario.correoElectronico)]() { deleteUser(QStringList(), correo); });

    // Ajustar el ancho de las columnas al contenido
    ui->resultadosTableWidget->resizeColumnsToContents();
}


void Reportes::buscarCorreo() {
    QString correo = ui->correoLineEdit->text();
    if(validarCorreo(correo.toStdString())){
        // Buscar el usuario en el árbol AVL
        NodoAVL<Usuario>* nodoEncontrado = listausers.Buscar(correo.toStdString());

        // Limpiar la tabla antes de agregar los resultados de la búsqueda
        ui->resultadosTableWidget->setRowCount(0);

        if (nodoEncontrado != nullptr) {
            Usuario usuarioEncontrado = nodoEncontrado->dato;
            agregarFilaTabla(usuarioEncontrado);
        } else {
            QMessageBox::information(this, "Buscar Usuario", "Usuario con correo " + correo + " no encontrado.");
        }
    }
}

void Reportes::preordenButton() {
    vector<Usuario> usuarios;
    listausers.preorden(usuarios);

    // Limpiar la tabla antes de agregar los resultados del recorrido preorden
    ui->resultadosTableWidget->setRowCount(0);

    for (const Usuario& usuario : usuarios) {
        agregarFilaTabla(usuario);
    }
}

void Reportes::inordenButton() {
    vector<Usuario> usuarios;
    listausers.inorden(usuarios);

    // Limpiar la tabla antes de agregar los resultados del recorrido inorden
    ui->resultadosTableWidget->setRowCount(0);

    for (const Usuario& usuario : usuarios) {
        agregarFilaTabla(usuario);
    }
}

void Reportes::postordenButton() {
    vector<Usuario> usuarios;
    listausers.postorden(usuarios);

    // Limpiar la tabla antes de agregar los resultados del recorrido postorden
    ui->resultadosTableWidget->setRowCount(0);

    for (const Usuario& usuario : usuarios) {
        agregarFilaTabla(usuario);
    }
}

void Reportes::regresarButton(){
    this->hide();
    emit windowClosed();
}

void Reportes::resizeEvent(QResizeEvent* event) {
    QMainWindow::resizeEvent(event); // Llama al método base para manejar el evento de redimensionamiento

    // Ajustar la imagen al tamaño del QGraphicsView
    if (ui->graficaAVL->scene()) {
        ui->graficaAVL->fitInView(ui->graficaAVL->scene()->itemsBoundingRect(), Qt::KeepAspectRatio);
    }
}

void Reportes::zoomIn() {
    ui->graficaAVL->scale(1.2, 1.2); // Escalar la vista para hacer zoom in
    ui->graficaListaDE->scale(1.2, 1.2);
}

void Reportes::zoomOut() {
    ui->graficaAVL->scale(1 / 1.2, 1 / 1.2); // Escalar la vista para hacer zoom out
    ui->graficaListaDE->scale(1 / 1.2, 1 / 1.2);
}

void Reportes::wheelEvent(QWheelEvent* event) {
    if (event->modifiers() & Qt::ControlModifier) {
        if (event->angleDelta().y() > 0) {
            zoomIn();
        } else {
            zoomOut();
        }
        event->accept();
    } else {
        QMainWindow::wheelEvent(event);
    }
}

void Reportes::mostrarGraficaArbolAVL(){
    // Generar el archivo .png usando el método renderGraphviz
    string pngFilePath = listausers.renderGraphviz("usuarios");

    if (pngFilePath.empty()) {
        QMessageBox::warning(this, "Error", "No se pudo generar la imagen del árbol AVL.");
        return;
    }

    // Crear una escena y agregar la imagen
    QGraphicsScene *scene = new QGraphicsScene(this);
    QPixmap pixmap(QString::fromStdString(pngFilePath));
    if (pixmap.isNull()) {
        QMessageBox::warning(this, "Error", "No se pudo cargar la imagen: " + QString::fromStdString(pngFilePath));
        delete scene; // Liberar la memoria de la escena
        return;
    }
    scene->addPixmap(pixmap);

    // Asignar la escena al QGraphicsView
    ui->graficaAVL->setScene(scene);
}

void Reportes::mostrarGraficaPublicaciones(){
    // Generar el archivo .png usando el método renderGraphviz
    listapub.generarDot("publicaciones.dot");
    string pngFilePath = listapub.renderGraphviz("publicaciones.dot", "publicaciones.png");

    if (pngFilePath.empty()) {
        QMessageBox::warning(this, "Error", "No se pudo generar la imagen de la lista doblemente enlazada.");
        return;
    }

    // Crear una escena y agregar la imagen
    QGraphicsScene *scene = new QGraphicsScene(this);
    QPixmap pixmap(QString::fromStdString(pngFilePath));
    if (pixmap.isNull()) {
        QMessageBox::warning(this, "Error", "No se pudo cargar la imagen: " + QString::fromStdString(pngFilePath));
        delete scene; // Liberar la memoria de la escena
        return;
    }
    scene->addPixmap(pixmap);

    // Asignar la escena al QGraphicsView
    ui->graficaListaDE->setScene(scene);
}
