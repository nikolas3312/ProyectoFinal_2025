#include "PersonajeJugadorNivel_1.h"
#include <QKeyEvent>

// Se define una velocidad de movimiento constante para el jugador.
constexpr float VELOCIDAD_HORIZONTAL = 350.0f;

/**
 * @brief Constructor que llama al constructor de la clase padre Entidad.
 */
PersonajeJugadorNivel1::PersonajeJugadorNivel1(float x, float y, float ancho, float alto)
    : Entidad(x, y, ancho, alto)
{
}

/**
 * @brief Destructor de la clase.
 */
PersonajeJugadorNivel1::~PersonajeJugadorNivel1()
{
}

/**
 * @brief Actualiza la posición del jugador en cada fotograma.
 * @param deltaTiempo El tiempo transcurrido desde el último fotograma.
 */
// En PersonajeJugadorNivel1.cpp

/**
 * @brief Actualiza la posición del jugador y aplica los límites de la pantalla.
 */
void PersonajeJugadorNivel1::actualizar(float deltaTiempo)
{
    // Aplica el movimiento en ambos ejes.
    posX += velocidadX * deltaTiempo;
    posY += velocidadY * deltaTiempo;

    // --- LÍMITES HORIZONTALES (LA VÍA) ---
    if (posX < 225) {
        posX = 225;
    }
    if (posX + ancho > 615) { // Límite derecho de la vía
        posX = 615 - ancho;
    }

    // --- LÍMITES VERTICALES (PARA QUE NO SE SALGA DE LA PANTALLA) ---
    if (posY < 0) {
        posY = 0;
    }
    if (posY + alto > 600) { // Suponiendo una ventana de 600px de alto
        posY = 600 - alto;
    }
}

/**
 * @brief Asigna la velocidad cuando se presiona una tecla de movimiento.
 */
void PersonajeJugadorNivel1::procesarTeclaPresionada(QKeyEvent* evento)
{
    switch (evento->key()) {
    case Qt::Key_Left:
        velocidadX = -VELOCIDAD_HORIZONTAL;
        break;
    case Qt::Key_Right:
        velocidadX = VELOCIDAD_HORIZONTAL;
        break;
    case Qt::Key_Up:
        velocidadY = -VELOCIDAD_HORIZONTAL; // Y negativo es hacia arriba
        break;
    case Qt::Key_Down:
        velocidadY = VELOCIDAD_HORIZONTAL;
        break;
    }
}

/**
 * @brief Detiene el movimiento cuando se suelta una tecla.
 */
void PersonajeJugadorNivel1::procesarTeclaLiberada(QKeyEvent* evento)
{
    // Si se suelta una tecla de movimiento horizontal, detiene la velocidad en X.
    if (evento->key() == Qt::Key_Left || evento->key() == Qt::Key_Right) {
        velocidadX = 0;
    }
    // Si se suelta una tecla de movimiento vertical, detiene la velocidad en Y.
    if (evento->key() == Qt::Key_Up || evento->key() == Qt::Key_Down) {
        velocidadY = 0;
    }
}
