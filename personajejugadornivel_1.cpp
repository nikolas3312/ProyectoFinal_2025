#include "personajejugadornivel_1.h"
#include <QKeyEvent>

// Velocidad constante de movimiento del jugador
constexpr float VELOCIDAD_JUGADOR = 350.0f;

/**
 * @brief Constructor que llama al constructor de la clase base Entidad.
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
 * @brief Actualiza la posición del jugador y aplica los límites de la pantalla.
 * @param deltaTiempo El tiempo transcurrido desde el último fotograma.
 */
void PersonajeJugadorNivel1::actualizar(float deltaTiempo)
{
    // Aplica el movimiento en ambos ejes
    posX += velocidadX * deltaTiempo;
    posY += velocidadY * deltaTiempo;

    // --- LÍMITES HORIZONTALES (LA VÍA) ---
    if (posX < 225) {
        posX = 225;
    }
    if (posX + ancho > 615) {
        posX = 615 - ancho;
    }

    // --- LÍMITES VERTICALES (PANTALLA) ---
    if (posY < 0) {
        posY = 0;
    }
    if (posY + alto > 600) { // Asumiendo ventana de 600px de alto
        posY = 600 - alto;
    }
}

/**
 * @brief Asigna la velocidad cuando se presiona una tecla de movimiento.
 */
void PersonajeJugadorNivel1::procesarTeclaPresionada(QKeyEvent* evento)
{
    switch (evento->key()) {
    case Qt::Key_A:
        velocidadX = -VELOCIDAD_JUGADOR;
        break;
    case Qt::Key_D:
        velocidadX = VELOCIDAD_JUGADOR;
        break;
    case Qt::Key_W:
        velocidadY = -VELOCIDAD_JUGADOR; // Y negativo es hacia arriba
        break;
    case Qt::Key_S:
        velocidadY = VELOCIDAD_JUGADOR;
        break;
    }
}

/**
 * @brief Detiene el movimiento cuando se suelta una tecla.
 * @note Maneja el caso de teclas opuestas para no cancelar el movimiento si la otra sigue presionada.
 */
void PersonajeJugadorNivel1::procesarTeclaLiberada(QKeyEvent* evento)
{
    switch (evento->key()) {
    case Qt::Key_A:
        if (velocidadX < 0) velocidadX = 0; // Si se movía a la izquierda, para
        break;
    case Qt::Key_D:
        if (velocidadX > 0) velocidadX = 0; // Si se movía a la derecha, para
        break;
    case Qt::Key_W:
        if (velocidadY < 0) velocidadY = 0; // Si se movía hacia arriba, para
        break;
    case Qt::Key_S:
        if (velocidadY > 0) velocidadY = 0; // Si se movía hacia abajo, para
        break;
    }
}


