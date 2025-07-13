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
void PersonajeJugadorNivel1::actualizar(float deltaTiempo)
{
    // Aplica el movimiento horizontal basado en la velocidad actual.
    posX += velocidadX * deltaTiempo;

    // Lógica simple para evitar que el jugador se salga de la pantalla.
    // Se asume una ventana de 800px de ancho.
    if (posX < 0) {
        posX = 0;
    }
    if (posX + ancho > 800) {
        posX = 800 - ancho;
    }
}

/**
 * @brief Asigna la velocidad cuando se presiona una tecla de movimiento.
 */
void PersonajeJugadorNivel1::procesarTeclaPresionada(QKeyEvent* evento)
{
    if (evento->key() == Qt::Key_Left || evento->key() == Qt::Key_A) {
        velocidadX = -VELOCIDAD_HORIZONTAL;
    } else if (evento->key() == Qt::Key_Right || evento->key() == Qt::Key_D) {
        velocidadX = VELOCIDAD_HORIZONTAL;
    }
}

/**
 * @brief Detiene el movimiento cuando se suelta una tecla.
 */
void PersonajeJugadorNivel1::procesarTeclaLiberada(QKeyEvent* evento)
{
    // Si se suelta la tecla izquierda o derecha, y la otra no está presionada, se detiene.
    // Una implementación simple es detener el movimiento siempre.
    if (evento->key() == Qt::Key_Left || evento->key() == Qt::Key_A ||
        evento->key() == Qt::Key_Right || evento->key() == Qt::Key_D)
    {
        velocidadX = 0;
    }
}
