#include "mainwindow.h"
#include "Juego.h"
#include <QPainter>
#include <QKeyEvent>
#include <QIcon>
#include <QFont>
#include <QPushButton>

/**
 * @brief Constructor de MainWindow.
 * Configura la ventana, crea la instancia del juego y la UI.
 */
MainWindow::MainWindow(QWidget *parent)
    : QMainWindow(parent)
{
    // 1. Configuración de la ventana principal
    this->setWindowTitle("Proyecto Final - Dragon Ball");
    this->setFixedSize(800, 600); // Tamaño fijo para el juego

    // 2. Creación de la instancia del juego
    juego = new Juego(this);

    // 3. Configuración de la Interfaz de Usuario (botones)
    configurarUI();

    // 4. Inicio del bucle principal del juego
    juego->iniciar();
}

/**
 * @brief Destructor de MainWindow.
 * Libera la memoria de la instancia del juego.
 */
MainWindow::~MainWindow()
{
    delete juego;
}

/**
 * @brief Organiza la creación y configuración de todos los botones.
 */
void MainWindow::configurarUI()
{
    // --- Creación del Menú de Selección de Personaje ---
    gokuButton = new QPushButton(this);
    gokuButton->setIcon(QIcon(":/portadaGoku.png"));
    gokuButton->setIconSize(QSize(150, 150));
    gokuButton->setFixedSize(160, 160);
    gokuButton->move(100, 200);

    krilinButton = new QPushButton(this);
    krilinButton->setIcon(QIcon(":/portadaKrilin.png"));
    krilinButton->setIconSize(QSize(150, 150));
    krilinButton->setFixedSize(160, 160);
    krilinButton->move(320, 200);

    yamchaButton = new QPushButton(this);
    yamchaButton->setIcon(QIcon(":/portadaYamcha.png"));
    yamchaButton->setIconSize(QSize(150, 150));
    yamchaButton->setFixedSize(160, 160);
    yamchaButton->move(540, 200);

    // --- Botón de Reintentar (inicialmente oculto) ---
    retryButton = new QPushButton("Reintentar", this);
    retryButton->setFixedSize(200, 50);
    retryButton->move(300, 400);
    retryButton->hide();

    // --- Conexión de señales y slots ---
    connect(gokuButton, &QPushButton::clicked, this, [=]() {
        juego->iniciarNuevaPartida(PersonajeSeleccionado::GOKU);
        ocultarBotonesSeleccion();
    });

    connect(krilinButton, &QPushButton::clicked, this, [=]() {
        juego->iniciarNuevaPartida(PersonajeSeleccionado::KRILIN);
        ocultarBotonesSeleccion();
    });

    connect(yamchaButton, &QPushButton::clicked, this, [=]() {
        juego->iniciarNuevaPartida(PersonajeSeleccionado::YAMCHA);
        ocultarBotonesSeleccion();
    });

    connect(retryButton, &QPushButton::clicked, this, [=]() {
        juego->iniciarNuevaPartida(juego->getPersonajeActual());
        retryButton->hide();
    });
}

/**
 * @brief Oculta los botones de selección de personaje.
 */
void MainWindow::ocultarBotonesSeleccion()
{
    gokuButton->hide();
    krilinButton->hide();
    yamchaButton->hide();
}

/**
 * @brief Evento de pintado. Delega el dibujo a la clase Juego.
 */
void MainWindow::paintEvent(QPaintEvent *event)
{
    Q_UNUSED(event);
    QPainter painter(this);

    if (juego) {
        juego->dibujar(&painter, rect(), juego->getSprites());
    }

    // Mostrar pantalla de derrota y botón de reintentar
    if (juego && juego->getEstado() == Juego::GameState::DERROTA) {
        painter.fillRect(rect(), QColor(0, 0, 0, 150));
        painter.setPen(Qt::white);
        painter.setFont(QFont("Arial", 48, QFont::Bold));
        painter.drawText(rect(), Qt::AlignCenter, "GAME OVER");
        retryButton->show();
    }
}

/**
 * @brief Evento de tecla presionada. Lo delega a la clase Juego.
 */
void MainWindow::keyPressEvent(QKeyEvent *event)
{
    if (juego) {
        juego->procesarInput(event);
    }
}

/**
 * @brief Evento de tecla liberada. Lo delega a la clase Juego.
 */
void MainWindow::keyReleaseEvent(QKeyEvent *event)
{
    if (juego) {
        juego->procesarInputLiberado(event);
    }
}
