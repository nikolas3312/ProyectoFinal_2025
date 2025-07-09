#include "mainwindow.h"
#include <QPainter>
#include <QKeyEvent>

/**
 * @brief Constructor de MainWindow.
 * Configura el tamaño de la ventana y crea la instancia del juego.
 */
MainWindow::MainWindow(QWidget *parent)
    : QMainWindow(parent)
{
    // Establece un título y un tamaño fijo para la ventana del juego.
    this->setWindowTitle("Proyecto Final - Dragon Ball");
    this->setFixedSize(800, 600);

    // Crea la instancia principal de la lógica del juego, pasándole un puntero a esta ventana.
    juego = new Juego(this);

    // Inicia el bucle principal del juego (el QTimer interno de la clase Juego).
    juego->iniciar();

    // --- LÍNEA DE PRUEBA ---
    // Para probar directamente el Nivel 1 sin un menú, podemos llamar a esto.
    // Elige un personaje para la prueba.
    juego->iniciarNuevaPartida(PersonajeSeleccionado::GOKU);
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
 * @brief Evento de pintado.
 * Delega toda la responsabilidad del dibujo a la clase Juego.
 */
void MainWindow::paintEvent(QPaintEvent *event)
{
    Q_UNUSED(event); // Le decimos al compilador que no nos importa no usar este parámetro.

    QPainter painter(this); // Crea el "pincel" para dibujar en esta ventana.

    // Llama al método de dibujo principal del juego, pasándole el pincel
    // y el rectángulo de la ventana para los cálculos de centrado.
    if (juego != nullptr) {
        juego->dibujar(&painter, this->rect());
    }
}

/**
 * @brief Evento de pulsación de tecla.
 * Delega el evento a la clase Juego para que lo procese.
 */
void MainWindow::keyPressEvent(QKeyEvent *event)
{
    if (juego != nullptr) {
        juego->procesarInput(event);
    }
}
