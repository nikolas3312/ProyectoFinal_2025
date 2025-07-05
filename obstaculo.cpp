#include "Obstaculo.h"
#include <cmath> // Necesario para la función sin()

// Valores constantes para el movimiento sinusoidal.
// Se definen aquí para no tener "números mágicos" en el código.
constexpr float FRECUENCIA_SINUSOIDAL = 3.0f;
constexpr float AMPLITUD_MAXIMA = 50.0f;

/**
 * @brief Constructor de Obstaculo.
 * Inicializa los atributos base de Entidad y los específicos de Obstaculo.
 */
Obstaculo::Obstaculo(float x, float y, TipoObstaculo tipo, bool esSinusoidal)
    : Entidad(x, y, 30.0f, 30.0f), // Tamaño por defecto, podría variar por tipo
    tipo(tipo),
    movimientoSinusoidal(esSinusoidal),
    angulo(0.0f),
    posXOriginal(x),
    amplitud(AMPLITUD_MAXIMA)
{
    // Se podrían ajustar el 'ancho' y 'alto' según el 'tipo' si es necesario.
}

/**
 * @brief Destructor de la clase Obstaculo.
 */
Obstaculo::~Obstaculo()
{
}

/**
 * @brief Actualiza la posición del obstáculo.
 * La velocidad vertical (velocidadY) será establecida externamente por la clase Nivel1,
 * que controla la aceleración global. Este método solo se encarga de aplicar
 * esa velocidad y el movimiento lateral si corresponde.
 */
void Obstaculo::actualizar(float deltaTiempo)
{
    // Movimiento vertical (común a todos los obstáculos).
    // La velocidadY es controlada por Nivel1 y su aceleración global.
    posY += velocidadY * deltaTiempo;

    // Movimiento horizontal (solo si es sinusoidal).
    if (movimientoSinusoidal) {
        // Actualiza el ángulo basado en el tiempo y una frecuencia.
        angulo += FRECUENCIA_SINUSOIDAL * deltaTiempo;

        // Calcula el desplazamiento en X usando la función seno.
        // posXOriginal mantiene el obstáculo centrado en su carril de caída.
        posX = posXOriginal + (amplitud * sin(angulo));
    }
}

/**
 * @brief Devuelve el tipo de obstáculo.
 * @return El tipo, para que la capa de renderizado sepa qué sprite usar.
 */
TipoObstaculo Obstaculo::getTipo() const
{
    return tipo;
}
