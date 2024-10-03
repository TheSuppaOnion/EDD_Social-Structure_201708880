#include "MenuUsr.h"
#include "Utilidades.h"
#include "ui_MenuUsr.h"
#include <QMessageBox>
#include <QTextEdit>

MenuUsr::MenuUsr(const QString &correo, QWidget *parent) : QMainWindow(parent), ui(new Ui::MenuUsr), correoUsuario(correo) {
    ui->setupUi(this);
    ui->label->setText("Bienvenido(a) " + correo);
    ui->lineEditContrasena->setEchoMode(QLineEdit::Password);
    // Crear un QIntValidator para aceptar solo números enteros
    QIntValidator *validator = new QIntValidator(0, 1000, this); // Rango de 0 a 1000, ajusta según tus necesidades
    ui->lineEditCantidad->setValidator(validator);
    connect(ui->pushButtonCerrarSesion, &QPushButton::clicked, this, &MenuUsr::pushButtonCerrarSesion);
    connect(ui->actionBuscar, &QAction::triggered, this, &MenuUsr::mostrarPaginaBuscar);
    connect(ui->actionPublicaciones, &QAction::triggered, this, &MenuUsr::mostrarPaginaPublicaciones);
    connect(ui->actionSolicitudes, &QAction::triggered, this, &MenuUsr::mostrarPaginaSolicitudes);
    connect(ui->actionReportes, &QAction::triggered, this, &MenuUsr::mostrarPaginaReportes);
    connect(ui->actionPerfil, &QAction::triggered, this, &MenuUsr::mostrarPaginaPerfil);
    connect(ui->pushButtonBuscar, &QPushButton::clicked, this, &MenuUsr::pushButtonBuscar);
    connect(ui->pushButtonModificarDatos, &QPushButton::clicked, this, &MenuUsr::pushButtonModificarDatos);
    connect(ui->pushButtonEliminarCuenta, &QPushButton::clicked, this, &MenuUsr::pushButtonEliminarCuenta);
    connect(ui->pushButtonAplicarFecha, &QPushButton::clicked, this, &MenuUsr::pushButtonAplicarFecha);
    connect(ui->pushButtonAplicarRecorrido, &QPushButton::clicked, this, &MenuUsr::pushButtonAplicarRecorrido);
    connect(ui->pushButtonCrearPublicacion, &QPushButton::clicked, this, &MenuUsr::pushButtonCrearPublicacion);
    connect(ui->pushButtonGenerarReportes, &QPushButton::clicked, this, &MenuUsr::pushButtonGenerarReportes);
    connect(ui->pushButtonGenerarBST, &QPushButton::clicked, this, &MenuUsr::pushButtonGenerarBST);
    ui->tableWidgetUsuarios->setEditTriggers(QAbstractItemView::NoEditTriggers);
    ui->tableWidgetSolicitudesEnviadas->setEditTriggers(QAbstractItemView::NoEditTriggers);
    ui->tableWidgetSolicitudesRecibidas->setEditTriggers(QAbstractItemView::NoEditTriggers);
    actualizarDatosUsuario();
}

MenuUsr::~MenuUsr() {
    delete ui;
}

void MenuUsr::pushButtonCerrarSesion() {
    // Emitir la señal de cierre de ventana antes de ocultar la instancia
    emit windowClosed();

    // Ocultar la instancia de la ventana
    this->deleteLater();
    imprimirSolicitudesRecibidas();
}

void MenuUsr::actualizarDatosUsuario() {
    // Actualizar las tablas y otros elementos de la interfaz con los datos del nuevo usuario
    rellenarTablaUsuarios();
    rellenarTablaSolicitudesRecibidas();
    rellenarTablaSolicitudesEnviadas();
    rellenarComboBoxFecha();
    llenarComboBoxBST(correoUsuario.toStdString());
}

void MenuUsr::mostrarPaginaBuscar(){
    ui->stackedWidget->setCurrentWidget(ui->pageBuscar);
}

void MenuUsr::pushButtonBuscar() {
    QString correo = ui->lineEditCorreo->text();
    if(validarCorreo(correo.toStdString())){
        if (listausers.Encontrar(correo.toStdString())) {
            NodoAVL<Usuario>* nodoEncontrado = listausers.Buscar(correo.toStdString());
            Usuario usuarioEncontrado = nodoEncontrado->dato;
            // Convertir std::string a QString
            QString nombres = QString::fromStdString(usuarioEncontrado.nombre);
            QString apellidos = QString::fromStdString(usuarioEncontrado.apellido);
            QString fechaNacimiento = QString::fromStdString(usuarioEncontrado.fechaNac);
            // Rellenar los campos con los datos del usuario
            ui->labelNombres->setText("Nombres: " + nombres);
            ui->labelApellidos->setText("Apellidos: " + apellidos);
            ui->labelCorreo->setText("Correo: " + correo);
            ui->labelFechaNacimiento->setText("Fecha de Nacimiento: " + fechaNacimiento);
        }
    }
}


void MenuUsr::mostrarPaginaPublicaciones(){
    ui->stackedWidget->setCurrentWidget(ui->pagePublicaciones);
}

// Método para rellenar el comboBoxFecha con fechas únicas
void MenuUsr::rellenarComboBoxFecha() {
    // Obtener todas las publicaciones
    std::vector<Publicacion> publicaciones = listapub.ObtenerPublicaciones();

    // Utilizar un conjunto para almacenar fechas únicas
    std::unordered_set<std::string> fechasUnicas;

    // Extraer las fechas de las publicaciones
    for (const auto& pub : publicaciones) {
        fechasUnicas.insert(pub.ObtenerFecha());
    }

    // Limpiar el comboBox antes de añadir nuevas fechas
    ui->comboBoxFecha->clear();

    // Añadir una opción para "Todas" las fechas
    ui->comboBoxFecha->addItem("Todas");

    // Añadir las fechas únicas al comboBox
    for (const auto& fecha : fechasUnicas) {
        ui->comboBoxFecha->addItem(QString::fromStdString(fecha));
    }
}

void MenuUsr::llenarComboBoxBST(const std::string& usuario) {
    // Verificar si el usuario existe en el mapa
    auto it = PublicacionesPorUsuario.find(usuario);
    if (it == PublicacionesPorUsuario.end()) {
        qDebug() << "Usuario no tiene publicaciones.";
        return;
    }

    // Obtener el árbol BST del usuario
    std::shared_ptr<ArbolBB<Publicacion>> arbolBST = it->second;

    // Recolectar las fechas del árbol BST
    std::set<std::string> fechas;
    arbolBST->collectDates(fechas);

    // Llenar el comboBoxBST con las fechas recolectadas
    ui->comboBoxBST->clear(); // Limpiar el comboBox
    ui->comboBoxBST->addItem("Todo"); // Agregar la opción "Todo"
    for (const auto& fecha : fechas) {
        ui->comboBoxBST->addItem(QString::fromStdString(fecha));
    }
}

void MenuUsr::pushButtonAplicarFecha() {
    QString filtroFecha = ui->comboBoxFecha->currentText();

    // Filtrar las publicaciones
    std::vector<Publicacion> publicacionesFiltradas = listapub.ObtenerPublicaciones();
    if (filtroFecha != "Todas") {
        auto it = std::remove_if(publicacionesFiltradas.begin(), publicacionesFiltradas.end(), [&](const Publicacion& pub) {
            return pub.ObtenerFecha() != filtroFecha.toStdString();
        });
        publicacionesFiltradas.erase(it, publicacionesFiltradas.end());
    }

    // Crear un layout para la scroll area
    QVBoxLayout* layout = new QVBoxLayout();

    // Mostrar las publicaciones en la scroll area
    for (const auto& pub : publicacionesFiltradas) {
        // Crear un contenedor para cada publicación
        QVBoxLayout* publicacionLayout = new QVBoxLayout();

        // Crear y añadir el label de la publicación
        QString textoPublicacion = QString("Usuario: %1\nFecha: %2\nContenido: %3")
                                       .arg(QString::fromStdString(pub.ObtenerCorreo()))
                                       .arg(QString::fromStdString(pub.ObtenerFecha()))
                                       .arg(QString::fromStdString(pub.ObtenerContenido()));
        QLabel* label = new QLabel(textoPublicacion);
        publicacionLayout->addWidget(label);

        // Crear un espacio para imágenes
        QLabel* imagenLabel = new QLabel("Espacio para imágenes");
        publicacionLayout->addWidget(imagenLabel);

        // Crear los botones
        QPushButton* comentarButton = new QPushButton("Comentar");
        QPushButton* verComentariosButton = new QPushButton("Ver comentarios");
        QPushButton* verArbolComentariosButton = new QPushButton("Ver árbol de comentarios");

        // Crear un layout horizontal para los botones
        QHBoxLayout* botonesLayout = new QHBoxLayout();
        botonesLayout->addWidget(comentarButton);
        botonesLayout->addWidget(verComentariosButton);
        botonesLayout->addWidget(verArbolComentariosButton);

        // Crear el botón de eliminar
        QPushButton* eliminarButton = new QPushButton("Eliminar");
        if (pub.ObtenerCorreo() != correoUsuario.toStdString()) {
            eliminarButton->setEnabled(false);
        }
        botonesLayout->addWidget(eliminarButton);

        // Añadir el layout de los botones al layout de la publicación
        publicacionLayout->addLayout(botonesLayout);

        // Crear un contenedor para la publicación y establecer su layout
        QWidget* publicacionWidget = new QWidget();
        publicacionWidget->setLayout(publicacionLayout);

        // Añadir el contenedor de la publicación al layout principal
        layout->addWidget(publicacionWidget);

        // Conectar los botones a los métodos correspondientes
        connect(comentarButton, &QPushButton::clicked, this, [this, comentarButton]() { pushButtonComentar(comentarButton); });
        connect(verComentariosButton, &QPushButton::clicked, this, [this, verComentariosButton]() { pushButtonVerComentarios(verComentariosButton); });
        connect(verArbolComentariosButton, &QPushButton::clicked, this, [this, verArbolComentariosButton]() { pushButtonVerArbolComentarios(verArbolComentariosButton); });
        connect(eliminarButton, &QPushButton::clicked, this, [this, eliminarButton]() { pushButtonEliminar(eliminarButton, "pushButtonAplicarFecha"); });
    }

    // Limpiar el contenido anterior de la scroll area y establecer el nuevo layout
    QWidget* container = new QWidget();
    container->setLayout(layout);
    ui->scrollAreaPublicaciones->setWidget(container);
}

void MenuUsr::pushButtonAplicarRecorrido() {
    // Obtener los datos de los filtros
    QString filtroOrden = ui->comboBoxOrden->currentText();
    int cantidad = ui->lineEditCantidad->text().toInt();

    // Crear un layout para la scroll area
    QVBoxLayout* layout = new QVBoxLayout();

    // Filtrar las publicaciones
    std::vector<Publicacion> publicacionesFiltradas;
    if (filtroOrden == "PreOrden") {
        publicacionesFiltradas = listapub.RecorridoPreorden();
    } else if (filtroOrden == "InOrden") {
        publicacionesFiltradas = listapub.RecorridoInorden();
    } else if (filtroOrden == "PostOrden") {
        publicacionesFiltradas = listapub.RecorridoPostorden();
    }

    // Mostrar las publicaciones en la scroll area, limitando la cantidad si es necesario
    int count = 0;
    for (const auto& pub : publicacionesFiltradas) {
        if (cantidad > 0 && count >= cantidad) {
            break;
        }

        // Crear un contenedor para cada publicación
        QVBoxLayout* publicacionLayout = new QVBoxLayout();

        // Crear y añadir el label de la publicación
        QString textoPublicacion = QString("Usuario: %1\nFecha y Hora: %2 %3\nContenido: %4")
                                       .arg(QString::fromStdString(pub.ObtenerCorreo()))
                                       .arg(QString::fromStdString(pub.ObtenerFecha()))
                                       .arg(QString::fromStdString(pub.ObtenerHora()))
                                       .arg(QString::fromStdString(pub.ObtenerContenido()));
        QLabel* label = new QLabel(textoPublicacion);
        publicacionLayout->addWidget(label);

        // Crear un espacio para imágenes
        QLabel* imagenLabel = new QLabel("Espacio para imágenes");
        publicacionLayout->addWidget(imagenLabel);

        // Crear los botones
        QPushButton* comentarButton = new QPushButton("Comentar");
        QPushButton* verComentariosButton = new QPushButton("Ver comentarios");
        QPushButton* verArbolComentariosButton = new QPushButton("Ver árbol de comentarios");

        // Crear un layout horizontal para los botones
        QHBoxLayout* botonesLayout = new QHBoxLayout();
        botonesLayout->addWidget(comentarButton);
        botonesLayout->addWidget(verComentariosButton);
        botonesLayout->addWidget(verArbolComentariosButton);

        // Crear el botón de eliminar
        QPushButton* eliminarButton = new QPushButton("Eliminar");
        if (pub.ObtenerCorreo() != correoUsuario.toStdString()) {
            eliminarButton->setEnabled(false);
        }
        botonesLayout->addWidget(eliminarButton);

        // Añadir el layout de los botones al layout de la publicación
        publicacionLayout->addLayout(botonesLayout);

        // Crear un contenedor para la publicación y establecer su layout
        QWidget* publicacionWidget = new QWidget();
        publicacionWidget->setLayout(publicacionLayout);

        // Añadir el contenedor de la publicación al layout principal
        layout->addWidget(publicacionWidget);

        // Conectar los botones a los métodos correspondientes
        connect(comentarButton, &QPushButton::clicked, this, [this, comentarButton]() { pushButtonComentar(comentarButton); });
        connect(verComentariosButton, &QPushButton::clicked, this, [this, verComentariosButton]() { pushButtonVerComentarios(verComentariosButton); });
        connect(verArbolComentariosButton, &QPushButton::clicked, this, [this, verArbolComentariosButton]() { pushButtonVerArbolComentarios(verArbolComentariosButton); });
        connect(eliminarButton, &QPushButton::clicked, this, [this, eliminarButton]() { pushButtonEliminar(eliminarButton, "pushButtonAplicarRecorrido"); });

        count++;
    }

    // Limpiar el contenido anterior de la scroll area y establecer el nuevo layout
    QWidget* container = new QWidget();
    container->setLayout(layout);
    ui->scrollAreaPublicaciones->setWidget(container);
}

void MenuUsr::pushButtonCrearPublicacion() {
    // Crear el diálogo
    QDialog dialog(this);
    dialog.setWindowTitle("Crear Publicación");

    QVBoxLayout* layout = new QVBoxLayout(&dialog);

    // Crear el QTextEdit para ingresar el contenido de la publicación
    QTextEdit* textEdit = new QTextEdit(&dialog);
    layout->addWidget(textEdit);

    // Crear los botones Publicar y Cancelar
    QPushButton* buttonPublicar = new QPushButton("Publicar", &dialog);
    QPushButton* buttonCancelar = new QPushButton("Cancelar", &dialog);

    // Conectar los botones a las acciones correspondientes
    connect(buttonPublicar, &QPushButton::clicked, &dialog, &QDialog::accept);
    connect(buttonCancelar, &QPushButton::clicked, &dialog, &QDialog::reject);

    // Añadir los botones al layout
    QHBoxLayout* buttonsLayout = new QHBoxLayout();
    buttonsLayout->addWidget(buttonPublicar);
    buttonsLayout->addWidget(buttonCancelar);
    layout->addLayout(buttonsLayout);

    // Mostrar el diálogo y obtener el resultado
    if (dialog.exec() == QDialog::Accepted) {
        QString contenido = textEdit->toPlainText();
        if (contenido.isEmpty()) {
            qDebug() << "El contenido de la publicación está vacío.";
            return;
        }

        // Obtener la fecha y hora actuales
        QString fechaActual = QDateTime::currentDateTime().toString("dd-MM-yyyy");
        QString horaActual = QDateTime::currentDateTime().toString("HH:mm:ss");

        // Crear una nueva publicación
        Publicacion nuevaPublicacion(correoUsuario.toStdString(), contenido.toStdString(), fechaActual.toStdString(), horaActual.toStdString());

        // Insertar la nueva publicación en la lista
        listapub.Insertar(nuevaPublicacion);

        // Mostrar un mensaje de éxito
        QMessageBox::information(this, "Éxito", "Publicación creada con éxito.");
    } else {
        qDebug() << "Se canceló la creación de la publicación.";
    }
}

void MenuUsr::pushButtonComentar(QPushButton* button) {
    if (!button) {
        qDebug() << "Button is null";
        return;
    }

    // Obtener el contenedor de la publicación (QWidget) que contiene el botón
    QWidget* publicacionWidget = button->parentWidget();
    while (publicacionWidget && !publicacionWidget->findChild<QLabel*>()) {
        publicacionWidget = publicacionWidget->parentWidget();
    }
    if (!publicacionWidget) {
        qDebug() << "Publication widget not found";
        return;
    }

    // Obtener el label de la publicación para extraer el contenido
    QLabel* label = publicacionWidget->findChild<QLabel*>();
    if (!label) {
        qDebug() << "Label not found in publication widget";
        return;
    }

    // Extraer el contenido de la publicación del label
    QString textoPublicacion = label->text();
    QStringList partes = textoPublicacion.split("\n");
    if (partes.size() < 3) {
        qDebug() << "Publication text format is incorrect";
        return;
    }

    // Extraer el contenido de la publicación
    QString contenido = partes[2].mid(11); // Asumiendo que el contenido empieza después de "Contenido: "

    // Buscar la publicación en la lista
    Nodo<Publicacion>* nodoPublicacion = listapub.getContenido(contenido.toStdString());
    if (!nodoPublicacion) {
        qDebug() << "Publication not found in list";
        return;
    }

    Publicacion* publicacion = &nodoPublicacion->dato;

    // Crear un diálogo para ingresar el comentario
    QDialog dialog(this);
    dialog.setWindowTitle("Agregar Comentario");

    QVBoxLayout* layout = new QVBoxLayout(&dialog);

    QLabel* labelContenido = new QLabel("Contenido:");
    QLineEdit* editContenido = new QLineEdit();
    layout->addWidget(labelContenido);
    layout->addWidget(editContenido);

    QPushButton* buttonAgregar = new QPushButton("Agregar", &dialog);
    connect(buttonAgregar, &QPushButton::clicked, &dialog, &QDialog::accept);
    layout->addWidget(buttonAgregar);

    // Mostrar el diálogo y esperar a que el usuario ingrese el comentario
    if (dialog.exec() == QDialog::Accepted) {
        std::string correo = correoUsuario.toStdString();
        std::string contenidoComentario = editContenido->text().toStdString();
        std::string fechaHora = QDateTime::currentDateTime().toString("dd-MM-yyyy HH:mm:ss").toStdString();

        // Crear el comentario y agregarlo al árbol B de comentarios de la publicación
        Comentario nuevoComentario(correo, contenidoComentario, fechaHora);
        publicacion->comentarios.insert(nuevoComentario);

        qDebug() << "Comentario agregado exitosamente";
    }
}

void MenuUsr::pushButtonEliminar(QPushButton* button, const QString& callerMethod) {
    if (!button) {
        qDebug() << "Button is null";
        return;
    }

    // Obtener el contenedor de la publicación (QWidget) que contiene el botón
    QWidget* publicacionWidget = button->parentWidget();
    while (publicacionWidget && !publicacionWidget->findChild<QLabel*>()) {
        publicacionWidget = publicacionWidget->parentWidget();
    }
    if (!publicacionWidget) {
        qDebug() << "Publication widget not found";
        return;
    }

    // Obtener el label de la publicación para extraer el contenido
    QLabel* label = publicacionWidget->findChild<QLabel*>();
    if (!label) {
        qDebug() << "Label not found in publication widget";
        return;
    }

    // Extraer el contenido de la publicación del label
    QString textoPublicacion = label->text();
    QStringList partes = textoPublicacion.split("\n");
    if (partes.size() < 3) {
        qDebug() << "Publication text format is incorrect";
        return;
    }

    // Extraer el contenido de la publicación
    QString contenido = partes[2].mid(11); // Asumiendo que el contenido empieza después de "Contenido: "

    // Eliminar la publicación de la lista
    listapub.Borrar(contenido.toStdString());

    // Actualizar la interfaz de usuario llamando al método correspondiente
    if (callerMethod == "pushButtonAplicarFecha") {
        pushButtonAplicarFecha();
    } else if (callerMethod == "pushButtonAplicarRecorrido") {
        pushButtonAplicarRecorrido();
    }
}

// Método para ver los comentarios de una publicación
void MenuUsr::pushButtonVerComentarios(QPushButton* button) {
    if (!button) {
        qDebug() << "Button is null";
        return;
    }

    // Obtener el contenedor de la publicación (QWidget) que contiene el botón
    QWidget* publicacionWidget = button->parentWidget();
    while (publicacionWidget && !publicacionWidget->findChild<QLabel*>()) {
        publicacionWidget = publicacionWidget->parentWidget();
    }
    if (!publicacionWidget) {
        qDebug() << "Publication widget not found";
        return;
    }

    // Obtener el label de la publicación para extraer el contenido
    QLabel* label = publicacionWidget->findChild<QLabel*>();
    if (!label) {
        qDebug() << "Label not found in publication widget";
        return;
    }

    // Extraer el contenido de la publicación del label
    QString textoPublicacion = label->text();
    QStringList partes = textoPublicacion.split("\n");
    if (partes.size() < 3) {
        qDebug() << "Publication text format is incorrect";
        return;
    }

    // Extraer el contenido de la publicación
    QString contenido = partes[2].mid(11); // Asumiendo que el contenido empieza después de "Contenido: "

    // Buscar la publicación en la lista
    Nodo<Publicacion>* nodoPublicacion = listapub.getContenido(contenido.toStdString());
    if (!nodoPublicacion) {
        qDebug() << "Publication not found in list";
        return;
    }

    Publicacion* publicacion = &nodoPublicacion->dato;

    // Crear el diálogo para mostrar los comentarios
    QDialog dialog(this);
    dialog.setWindowTitle("Comentarios");

    QVBoxLayout* layout = new QVBoxLayout(&dialog);

    // Mostrar los comentarios en el diálogo
    for (const auto& comentario : publicacion->comentarios.obtenerElementos()) {
        QString textoComentario = QString("Usuario: %1\nFecha y hora: %2\nContenido: %3")
        .arg(QString::fromStdString(comentario.ObtenerCorreo()))
            .arg(QString::fromStdString(comentario.ObtenerFechayHora()))
            .arg(QString::fromStdString(comentario.ObtenerContenido()));
        QLabel* labelComentario = new QLabel(textoComentario);
        layout->addWidget(labelComentario);
    }

    // Añadir un botón de cerrar
    QPushButton* buttonCerrar = new QPushButton("Cerrar", &dialog);
    connect(buttonCerrar, &QPushButton::clicked, &dialog, &QDialog::accept);
    layout->addWidget(buttonCerrar);

    // Mostrar el diálogo
    dialog.exec();
}

void MenuUsr::pushButtonVerArbolComentarios(QPushButton* button) {
    // Crear el diálogo
    QDialog dialog(this);
    dialog.setWindowTitle("Ver Árbol de Comentarios");

    // Crear el layout
    QVBoxLayout* layout = new QVBoxLayout(&dialog);

    // Crear el QGraphicsView y QGraphicsScene
    QGraphicsView* graphicsView = new QGraphicsView(&dialog);
    QGraphicsScene* scene = new QGraphicsScene(graphicsView);

    if (!button) {
        qDebug() << "Button is null";
        return;
    }

    // Obtener el contenedor de la publicación (QWidget) que contiene el botón
    QWidget* publicacionWidget = button->parentWidget();
    while (publicacionWidget && !publicacionWidget->findChild<QLabel*>()) {
        publicacionWidget = publicacionWidget->parentWidget();
    }
    if (!publicacionWidget) {
        qDebug() << "Publication widget not found";
        return;
    }

    // Obtener el label de la publicación para extraer el contenido
    QLabel* label = publicacionWidget->findChild<QLabel*>();
    if (!label) {
        qDebug() << "Label not found in publication widget";
        return;
    }

    // Extraer el contenido de la publicación del label
    QString textoPublicacion = label->text();
    QStringList partes = textoPublicacion.split("\n");
    if (partes.size() < 3) {
        qDebug() << "Publication text format is incorrect";
        return;
    }

    // Extraer el contenido de la publicación
    QString contenido = partes[2].mid(11); // Asumiendo que el contenido empieza después de "Contenido: "

    // Buscar la publicación en la lista
    Nodo<Publicacion>* nodoPublicacion = listapub.getContenido(contenido.toStdString());
    if (!nodoPublicacion) {
        qDebug() << "Publication not found in list";
        return;
    }

    Publicacion* publicacion = &nodoPublicacion->dato;

    // Generar el archivo .png usando el método renderGraphviz
    string pngFilePath = publicacion->comentarios.renderGraphviz("arbolB");

    if (pngFilePath.empty()) {
        QMessageBox::warning(this, "Error", "No se pudo generar la imagen del árbol B.");
        return;
    }

    // Crear una escena y agregar la imagen
    QPixmap pixmap(QString::fromStdString(pngFilePath));
    if (pixmap.isNull()) {
        QMessageBox::warning(this, "Error", "No se pudo cargar la imagen: " + QString::fromStdString(pngFilePath));
        return;
    }
    scene->addPixmap(pixmap);

    graphicsView->setScene(scene);

    // Agregar el QGraphicsView al layout
    layout->addWidget(graphicsView);

    // Crear y agregar el botón de cerrar
    QPushButton* buttonCerrar = new QPushButton("Cerrar", &dialog);
    connect(buttonCerrar, &QPushButton::clicked, &dialog, &QDialog::accept);
    layout->addWidget(buttonCerrar);

    // Mostrar el diálogo
    dialog.exec();
}


void MenuUsr::mostrarPaginaSolicitudes(){
    ui->stackedWidget->setCurrentWidget(ui->pageSolicitudes);
}

// Función para rellenar la tabla de usuarios
void MenuUsr::rellenarTablaUsuarios() {
    ui->tableWidgetUsuarios->setRowCount(0); // Limpiar la tabla
    vector<string> usuarios = listausers.ObtenerUsuarios();

    // Iterar sobre la lista de usuarios y añadir filas a la tabla
    for (const string& usuarioStr : usuarios) {
        QStringList usuarioData = QString::fromStdString(usuarioStr).split(",");
        QString correo = usuarioData[3];

        // Saltar el usuario logueado
        if (correo == correoUsuario) {
            continue;
        }

        int row = ui->tableWidgetUsuarios->rowCount();
        ui->tableWidgetUsuarios->insertRow(row);

        // Añadir información de usuario a las celdas correspondientes
        for (int col = 0; col < usuarioData.size(); ++col) {
            QTableWidgetItem *item = new QTableWidgetItem(usuarioData[col]);
            ui->tableWidgetUsuarios->setItem(row, col, item);
        }

        // Añadir botones de acción para cada fila
        QWidget *widget = new QWidget();
        QHBoxLayout *layout = new QHBoxLayout(widget);
        QPushButton *enviarSol = new QPushButton("Enviar Solicitud");
        layout->addWidget(enviarSol);
        layout->setAlignment(Qt::AlignCenter);
        layout->setContentsMargins(0, 0, 0, 0);
        widget->setLayout(layout);
        ui->tableWidgetUsuarios->setCellWidget(row, 4, widget); // Asumiendo que la columna 4 es para los botones

        // Conectar botones a las funciones correspondientes
        connect(enviarSol, &QPushButton::clicked, this, [this, correo]() {
            enviarSolicitud(correo.toStdString());
        });
    }

    // Ajustar el ancho de las columnas al contenido
    ui->tableWidgetUsuarios->resizeColumnsToContents();
}

// Función para enviar solicitud
void MenuUsr::enviarSolicitud(const string& correoDestino) {
    if (listausers.Buscar(correoDestino)) {
        // Verificar si el usuario actual tiene una lista de solicitudes enviadas
        auto it = SolicitudesEnviadasPorUsuario.find(correoUsuario.toStdString());
        if (it == SolicitudesEnviadasPorUsuario.end()) {
            // Si no existe, crear una nueva lista y agregarla al unordered_map
            std::cout << "Creando nueva lista de solicitudes enviadas para el usuario: " << correoUsuario.toStdString() << std::endl;
            auto listaSolicitudesEnviadas = std::make_shared<ListaSE<Solicitud>>();
            SolicitudesEnviadasPorUsuario[correoUsuario.toStdString()] = listaSolicitudesEnviadas;
            it = SolicitudesEnviadasPorUsuario.find(correoUsuario.toStdString());
        }

        auto listaSolicitudesEnviadas = it->second;

        if (!listaSolicitudesEnviadas->buscarPorCorreo(correoDestino)) {
            // Obtener la fecha y hora actuales
            pair<string, string> fechaHora = obtenerFechaHora();
            string fecha = fechaHora.first;
            string hora = fechaHora.second;

            // Crear la solicitud y agregarla a las estructuras correspondientes
            Solicitud solicitudEnviada(correoUsuario.toStdString(), correoDestino, fecha, hora);
            Solicitud solicitudRecibida(correoDestino, correoUsuario.toStdString(), fecha, hora);

            listaSolicitudesEnviadas->Insertar(solicitudEnviada);

            // Verificar si el usuario destino ya tiene una pila de solicitudes recibidas
            if (SoolicitudesRecibidasPorUsuario.find(correoDestino) == SoolicitudesRecibidasPorUsuario.end()) {
                // Si no existe, crear una nueva pila y agregarla al unordered_map
                std::cout << "Creando nueva pila de solicitudes para el usuario: " << correoDestino << std::endl;
                auto pilausuariodestino = std::make_shared<Pila<Solicitud>>();
                pilausuariodestino->Push(solicitudRecibida);
                SoolicitudesRecibidasPorUsuario[correoDestino] = pilausuariodestino;
            } else {
                // Si ya existe, agregar la solicitud a la pila existente
                std::cout << "Agregando solicitud a la pila existente para el usuario: " << correoDestino << std::endl;
                SoolicitudesRecibidasPorUsuario[correoDestino]->Push(solicitudRecibida);
            }

            // Mostrar mensaje de éxito
            QMessageBox::information(this, "Solicitud Enviada", "Solicitud enviada exitosamente");

            // Actualizar la tabla de solicitudes enviadas
            rellenarTablaSolicitudesEnviadas();
        } else {
            QMessageBox::information(this, "Solicitud Enviada", "Ya se ha enviado una solicitud a este usuario.");
        }
    } else {
        QMessageBox::information(this, "Error", "Usuario no encontrado");
    }
}

void MenuUsr::rellenarTablaSolicitudesRecibidas() {
    ui->tableWidgetSolicitudesRecibidas->setRowCount(0); // Limpiar la tabla

    // Verificar si el usuario actual tiene una pila de solicitudes recibidas
    auto it = SoolicitudesRecibidasPorUsuario.find(correoUsuario.toStdString());
    if (it != SoolicitudesRecibidasPorUsuario.end()) {
        // Usar una estructura auxiliar para almacenar temporalmente los elementos
        std::vector<Solicitud> solicitudes;

        // Transferir elementos de la pila a la estructura auxiliar sin modificar la pila original
        std::shared_ptr<Pila<Solicitud>> pilaSolicitudes = it->second;
        while (!pilaSolicitudes->PilaVacia()) {
            solicitudes.push_back(pilaSolicitudes->Top());
            pilaSolicitudes->Pop();
        }

        // Restaurar la pila original
        for (const auto& solicitud : solicitudes) {
            pilaSolicitudes->Push(solicitud);
        }

        // Iterar sobre la estructura auxiliar
        for (const auto& solicitud : solicitudes) {
            int row = ui->tableWidgetSolicitudesRecibidas->rowCount();
            ui->tableWidgetSolicitudesRecibidas->insertRow(row);

            // Añadir el correo a la tabla
            QTableWidgetItem* itemCorreo = new QTableWidgetItem(QString::fromStdString(solicitud.ObtenerCorreo()));
            ui->tableWidgetSolicitudesRecibidas->setItem(row, 0, itemCorreo);

            // Añadir botones de acción para cada fila
            QWidget *widget = new QWidget();
            QHBoxLayout *layout = new QHBoxLayout(widget);
            QPushButton *aceptarBtn = new QPushButton("Aceptar");
            QPushButton *rechazarBtn = new QPushButton("Rechazar");
            layout->addWidget(aceptarBtn);
            layout->addWidget(rechazarBtn);
            layout->setAlignment(Qt::AlignCenter);
            layout->setContentsMargins(0, 0, 0, 0);
            widget->setLayout(layout);
            ui->tableWidgetSolicitudesRecibidas->setCellWidget(row, 1, widget); // Asumiendo que la columna 1 es para los botones

            // Conectar botones a las funciones correspondientes
            connect(aceptarBtn, &QPushButton::clicked, this, [this, row]() {
                // Aquí puedes añadir la lógica para aceptar la solicitud
            });
            connect(rechazarBtn, &QPushButton::clicked, this, [this, solicitud]() {
                rechazarSolicitud(solicitud.ObtenerCorreo());
            });
        }

        // Ajustar el ancho de las columnas al contenido
        ui->tableWidgetSolicitudesRecibidas->resizeColumnsToContents();
    }
}

// Función para rechazar una solicitud
void MenuUsr::rechazarSolicitud(const string& correoOrigen) {
    // Verificar si la solicitud existe en la pila de solicitudes recibidas del usuario actual
    auto itRecibidas = SoolicitudesRecibidasPorUsuario.find(correoUsuario.toStdString());
    if (itRecibidas != SoolicitudesRecibidasPorUsuario.end() && itRecibidas->second->buscar(correoOrigen)) {
        QMessageBox::StandardButton respuesta = QMessageBox::question(this, "Confirmar Rechazo", "¿Seguro que quiere rechazar esta solicitud?", QMessageBox::Yes | QMessageBox::No);
        if (respuesta == QMessageBox::Yes) {
            try {
                // Eliminar la solicitud de la pila de solicitudes recibidas del usuario actual
                itRecibidas->second->Eliminar(correoOrigen);

                // Verificar si el usuario origen tiene una lista de solicitudes enviadas
                auto itEnviadas = SolicitudesEnviadasPorUsuario.find(correoOrigen);
                if (itEnviadas != SolicitudesEnviadasPorUsuario.end()) {
                    auto listaSolicitudesOrigen = itEnviadas->second;
                    listaSolicitudesOrigen->borrarPorCorreo(correoUsuario.toStdString());

                    // Si la lista de solicitudes enviadas del usuario origen está vacía, eliminarla del unordered_map
                    if (listaSolicitudesOrigen->ListaVacia()) {
                        SolicitudesEnviadasPorUsuario.erase(correoOrigen);
                    }
                }

                QMessageBox::information(this, "Solicitud Rechazada", "Solicitud rechazada exitosamente");
                rellenarTablaSolicitudesRecibidas(); // Actualizar la tabla de solicitudes recibidas
            } catch (const std::exception& e) {
                QMessageBox::information(this, "Error", QString::fromStdString("Error al eliminar la solicitud: " + std::string(e.what())));
            }
        } else if (respuesta == QMessageBox::No) {
            QMessageBox::information(this, "Operación Cancelada", "Operación cancelada");
        } else {
            QMessageBox::information(this, "Opción Inválida", "Opción inválida, por favor intente de nuevo");
        }
    } else {
        QMessageBox::information(this, "Error", "No se encontró la solicitud a rechazar");
    }
}

// Función para rellenar la tabla de solicitudes enviadas
void MenuUsr::rellenarTablaSolicitudesEnviadas() {
    ui->tableWidgetSolicitudesEnviadas->setRowCount(0); // Limpiar la tabla

    // Obtener la lista de solicitudes enviadas para el usuario logueado
    auto it = SolicitudesEnviadasPorUsuario.find(correoUsuario.toStdString());
    if (it != SolicitudesEnviadasPorUsuario.end()) {
        const shared_ptr<ListaSE<Solicitud>>& listaSolicitudesPtr = it->second;

        // Iterar sobre la lista de solicitudes
        auto nodo = listaSolicitudesPtr->obtenerPrimero();
        while (nodo != nullptr) {
            const Solicitud& solicitud = nodo->dato;

            int row = ui->tableWidgetSolicitudesEnviadas->rowCount();
            ui->tableWidgetSolicitudesEnviadas->insertRow(row);

            // Añadir el correo a la tabla
            QTableWidgetItem* itemCorreo = new QTableWidgetItem(QString::fromStdString(solicitud.ObtenerCorreo()));
            ui->tableWidgetSolicitudesEnviadas->setItem(row, 0, itemCorreo);

            // Añadir botón de acción para cada fila
            QWidget *widget = new QWidget();
            QHBoxLayout *layout = new QHBoxLayout(widget);
            QPushButton *cancelarBtn = new QPushButton("Cancelar");
            layout->addWidget(cancelarBtn);
            layout->setAlignment(Qt::AlignCenter);
            layout->setContentsMargins(0, 0, 0, 0);
            widget->setLayout(layout);
            ui->tableWidgetSolicitudesEnviadas->setCellWidget(row, 1, widget); // Asumiendo que la columna 1 es para el botón

            // Conectar botón a la función correspondiente
            connect(cancelarBtn, &QPushButton::clicked, this, [this, solicitud]() {
                cancelarSolicitud(solicitud.ObtenerCorreo());
            });

            nodo = nodo->siguiente;
        }
    }

    // Ajustar el ancho de las columnas al contenido
    ui->tableWidgetSolicitudesEnviadas->resizeColumnsToContents();
}

// Función para cancelar una solicitud
void MenuUsr::cancelarSolicitud(const string& correoDestino) {
    // Verificar si el usuario actual tiene una lista de solicitudes enviadas
    auto it = SolicitudesEnviadasPorUsuario.find(correoUsuario.toStdString());
    if (it != SolicitudesEnviadasPorUsuario.end()) {
        auto listaSolicitudesEnviadas = it->second;

        // Verificar si la solicitud existe en la lista de solicitudes enviadas del usuario actual
        if (listaSolicitudesEnviadas->buscarPorCorreo(correoDestino)) {
            QMessageBox::StandardButton respuesta = QMessageBox::question(this, "Confirmar Cancelación", "¿Seguro que quiere cancelar esta solicitud?", QMessageBox::Yes | QMessageBox::No);
            if (respuesta == QMessageBox::Yes) {
                // Eliminar la solicitud de la lista de solicitudes enviadas del usuario actual
                listaSolicitudesEnviadas->borrarPorCorreo(correoDestino);

                // Si la lista de solicitudes enviadas del usuario actual está vacía, eliminarla del unordered_map
                if (listaSolicitudesEnviadas->ListaVacia()) {
                    SolicitudesEnviadasPorUsuario.erase(correoUsuario.toStdString());
                }

                // Verificar si el usuario destinatario tiene una pila de solicitudes recibidas
                if (SoolicitudesRecibidasPorUsuario.find(correoDestino) != SoolicitudesRecibidasPorUsuario.end()) {
                    auto pilausuariodestino = SoolicitudesRecibidasPorUsuario[correoDestino];
                    pilausuariodestino->Eliminar(correoUsuario.toStdString());

                    // Si la pila de solicitudes recibidas del usuario destinatario está vacía, eliminarla del unordered_map
                    if (pilausuariodestino->PilaVacia()) {
                        SoolicitudesRecibidasPorUsuario.erase(correoDestino);
                    }
                }

                QMessageBox::information(this, "Solicitud Cancelada", "Solicitud cancelada exitosamente");
                rellenarTablaSolicitudesEnviadas(); // Actualizar la tabla de solicitudes enviadas
            } else if (respuesta == QMessageBox::No) {
                QMessageBox::information(this, "Operación Cancelada", "Operación cancelada");
            } else {
                QMessageBox::information(this, "Opción Inválida", "Opción inválida, por favor intente de nuevo");
            }
        } else {
            QMessageBox::information(this, "Error", "No se encontró la solicitud a cancelar");
        }
    } else {
        QMessageBox::information(this, "Error", "No se encontró la lista de solicitudes enviadas para el usuario actual");
    }
}


void MenuUsr::mostrarPaginaReportes(){
    ui->stackedWidget->setCurrentWidget(ui->pageReportes);
}

void MenuUsr::pushButtonGenerarReportes() {
    // Contar publicaciones por fecha
    std::map<std::string, int> publicacionesPorFecha;
    Nodo<Publicacion>* nodo = listapub.getPrimero();
    while (nodo) {
        std::string fecha = nodo->dato.ObtenerFecha();
        publicacionesPorFecha[fecha]++;
        nodo = nodo->siguiente;
    }

    // Contar comentarios por usuario
    std::map<std::string, int> comentariosPorUsuario;
    nodo = listapub.getPrimero();
    while (nodo) {
        const ArbolB<Comentario, 5>& comentarios = nodo->dato.ObtenerComentarios();
        // Usar el método obtenerElementos para obtener todos los comentarios
        std::vector<Comentario> todosLosComentarios = comentarios.obtenerElementos();
        for (const Comentario& comentario : todosLosComentarios) {
            std::string usuario = comentario.ObtenerCorreo();
            comentariosPorUsuario[usuario]++;
        }
        nodo = nodo->siguiente;
    }

    // Rellenar tableWidgetFechasMasPublicaciones
    ui->tableWidgetFechasMasPublicaciones->setRowCount(publicacionesPorFecha.size());
    int row = 0;
    for (const auto& entry : publicacionesPorFecha) {
         ui->tableWidgetFechasMasPublicaciones->setItem(row, 0, new QTableWidgetItem(QString::fromStdString(entry.first)));
         ui->tableWidgetFechasMasPublicaciones->setItem(row, 1, new QTableWidgetItem(QString::number(entry.second)));
        row++;
    }

    // Rellenar tableWidgetPublicacionesMasComentarios
    ui->tableWidgetPublicacionesMasComentarios->setRowCount(comentariosPorUsuario.size());
    row = 0;
    nodo = listapub.getPrimero();
    while (nodo) {
        std::string fecha = nodo->dato.ObtenerFecha();
        const ArbolB<Comentario, 5>& comentarios = nodo->dato.ObtenerComentarios();
        std::vector<Comentario> todosLosComentarios = comentarios.obtenerElementos();
        for (const Comentario& comentario : todosLosComentarios) {
            std::string usuario = comentario.ObtenerCorreo();
            int numComentarios = comentariosPorUsuario[usuario];
            ui->tableWidgetPublicacionesMasComentarios->setItem(row, 0, new QTableWidgetItem(QString::fromStdString(fecha)));
            ui->tableWidgetPublicacionesMasComentarios->setItem(row, 1, new QTableWidgetItem(QString::fromStdString(usuario)));
            ui->tableWidgetPublicacionesMasComentarios->setItem(row, 2, new QTableWidgetItem(QString::number(numComentarios)));
            row++;
        }
        nodo = nodo->siguiente;
    }
}

void MenuUsr::pushButtonGenerarBST() {
    // Verificar si el usuario existe en el mapa
    auto it = PublicacionesPorUsuario.find(correoUsuario.toStdString());
    if (it == PublicacionesPorUsuario.end()) {
        QMessageBox::warning(this, "Error", "Usuario no encontrado.");
        return;
    }

    // Obtener el árbol BST del usuario
    std::shared_ptr<ArbolBB<Publicacion>> arbolBST = it->second;

    // Generar el archivo .png usando el método renderGraphviz
    std::string pngFilePath = arbolBST->renderGraphviz("arbolBST_" + correoUsuario.toStdString());

    if (pngFilePath.empty()) {
        QMessageBox::warning(this, "Error", "No se pudo generar la imagen del árbol BST.");
        return;
    }

    // Crear una escena y agregar la imagen
    QGraphicsScene* scene = new QGraphicsScene(this);
    QPixmap pixmap(QString::fromStdString(pngFilePath));
    if (pixmap.isNull()) {
        QMessageBox::warning(this, "Error", "No se pudo cargar la imagen: " + QString::fromStdString(pngFilePath));
        delete scene; // Liberar la memoria de la escena
        return;
    }
    scene->addPixmap(pixmap);

    // Asignar la escena al QGraphicsView
    ui->graphicsViewBST->setScene(scene);
}

void MenuUsr::mostrarPaginaPerfil(){
    ui->stackedWidget->setCurrentWidget(ui->pagePerfil);
}

void MenuUsr::pushButtonModificarDatos() {
    QString nombre = ui->lineEditNombres->text().simplified();
    QString apellido = ui->lineEditApellidos->text().simplified();
    QString fechaNacimiento = ui->dateEditFechaNacimiento->date().toString("dd/MM/yyyy");
    QString correo = ui->lineEditCorreo1->text().simplified();
    QString contrasena = ui->lineEditContrasena->text().simplified();

    // Verificar si los campos están vacíos después de simplificar
    vector<QString> campos = {nombre, apellido};
    if(!verificarCamposVacios(campos) && validarFechaNacimiento(fechaNacimiento.toStdString())){
        // Crear un objeto Usuario con los nuevos datos
        NodoAVL<Usuario>* nodoEncontrado = listausers.Buscar(correoUsuario.toStdString());
        Usuario usuarioEncontrado = nodoEncontrado->dato;
        if(contrasena.isEmpty()){
            contrasena = QString::fromStdString(usuarioEncontrado.contrasenia);
        }
        if(correo.isEmpty()){
            correo = QString::fromStdString(usuarioEncontrado.correoElectronico);
            if(validarCorreo(correo.toStdString())){
                Usuario nuevosDatos(nombre.toStdString(), apellido.toStdString(), fechaNacimiento.toStdString(), correo.toStdString(), contrasena.toStdString());
                // Update the user in the AVL tree
                bool result = listausers.Modificar(correoUsuario.toStdString(), nuevosDatos);
                QString cadena = result ? "true" : "false";
                QMessageBox::information(this, "Modificar Usuario", "Usuario " + correo + " modificado." + cadena);
                return;
            }
        }
        if(!listausers.Encontrar(correo.toStdString())){
            if(validarCorreo(correo.toStdString())){
                Usuario nuevosDatos(nombre.toStdString(), apellido.toStdString(), fechaNacimiento.toStdString(), correo.toStdString(), contrasena.toStdString());
                // Update the user in the AVL tree
                bool result = listausers.Modificar(correoUsuario.toStdString(), nuevosDatos);
                QString cadena = result ? "true" : "false";
                QMessageBox::information(this, "Modificar Usuario", "Usuario " + correo + " modificado." + cadena);
                return;
            }
        } else{QMessageBox::warning(this, "Modificar Usuario", "Este correo ya esta registrado, por favor utilice otro.");};
    } else{QMessageBox::warning(this, "Modificar Usuario", "Solo puede dejar vacio contraseña o correo si no desea cambiarlos.");};
}

void MenuUsr::pushButtonEliminarCuenta() {
    QMessageBox::StandardButton reply;
    reply = QMessageBox::question(this, "Eliminar Cuenta", "¿Estás seguro de que deseas eliminar tu cuenta?", QMessageBox::Yes | QMessageBox::No);
    if (reply == QMessageBox::Yes) {
        listausers.borrar(correoUsuario.toStdString());
        bool resultPila = EliminarPila(correoUsuario.toStdString());
        bool resultPubli = EliminarPublicaciones(correoUsuario.toStdString());
        SolicitudesEnviadasPorUsuario.erase(correoUsuario.toStdString());
        SoolicitudesRecibidasPorUsuario.erase(correoUsuario.toStdString());
        QString cadena = resultPila ? "eliminado." : "error";
        QString cadena1 = resultPubli ? "eliminado." : "error";
        QMessageBox::information(this, "Eliminar Usuario", "Usuario " + correoUsuario + " eliminado." + " Solicitudes " + cadena + " Publicaciones " + cadena1);
        pushButtonCerrarSesion();
    }
}
