#pragma once

#include "Entidad.h"

/**
 * @enum TipoObstaculo
 * @brief Enumera los diferentes tipos de obstáculos que pueden aparecer.
 * Se utiliza para determinar el sprite a dibujar y, potencialmente,
 * comportamientos específicos.
 */
enum class TipoObstaculo {
    VEHICULO,
    PAJARO,
    CAPSULA
    // Se pueden añadir más tipos aquí en el futuro.
};

/**
 * @class Obstaculo
 * @brief Representa un obstáculo en el Nivel 1.
 *
 * Esta clase hereda de Entidad y añade la lógica específica para los
 * obstáculos, como su tipo y su patrón de movimiento (recto o sinusoidal).
 */
class Obstaculo : public Entidad {
public:
    /**
     * @brief Constructor de la clase Obstaculo.
     * @param x Posición inicial en X.
     * @param y Posición inicial en Y.
     * @param tipo El tipo de obstáculo a crear (VEHICULO, PAJARO, etc.).
     * @param esSinusoidal 'true' si el obstáculo debe tener movimiento lateral.
     */
    Obstaculo(float x, float y, TipoObstaculo tipo, bool esSinusoidal);

    // Destructor.
    ~Obstaculo();

    /**
     * @brief Actualiza la posición del obstáculo en cada fotograma.
     * Implementa la lógica de movimiento recto o sinusoidal.
     * @param deltaTiempo El tiempo transcurrido desde el último fotograma.
     */
    void actualizar(float deltaTiempo) override;

    /**
     * @brief Obtiene el tipo de este obstáculo.
     * @return El valor del enum TipoObstaculo.
     * @note Se usará para determinar qué sprite dibujar.
     */
    TipoObstaculo getTipo() const;

private:
    TipoObstaculo tipo;   // Almacena el tipo de obstáculo que es.
    bool movimientoSinusoidal; // Flag para activar el movimiento lateral.

    // Atributos para el movimiento sinusoidal
    float angulo;         // Ángulo actual de la fase de la onda seno.
    float posXOriginal;   // Posición X central sobre la que oscilará.
    float amplitud;       // Distancia máxima de oscilación lateral.
};
