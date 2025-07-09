#pragma once

#include <QPainter>

/**
 * @class Nivel
 * @brief Clase base abstracta que define la interfaz para todos los niveles del juego.
 *
 * Actúa como un contrato que cualquier nivel concreto debe seguir, asegurando
 * que la clase principal 'Juego' pueda gestionarlos de forma polimórfica sin
 * conocer los detalles específicos de cada uno.
 */
class Nivel {
public:
    // Destructor virtual para garantizar la limpieza de memoria de las clases hijas.
    virtual ~Nivel() {}

    /**
     * @brief Configura el estado inicial del nivel.
     *
     * Debe ser implementado por las clases hijas para crear y posicionar
     * los objetos iniciales (jugador, enemigos, obstáculos, etc.).
     */
    virtual void inicializar() = 0;

    /**
     * @brief Actualiza la lógica del nivel para un fotograma.
     * @param deltaTiempo El tiempo transcurrido desde el último fotograma.
     */
    virtual void actualizar(float deltaTiempo) = 0;

    /**
     * @brief Dibuja todos los elementos del nivel en la pantalla.
     * @param painter Puntero al QPainter que se usará para las operaciones de dibujo.
     */
    virtual void dibujar(QPainter* painter, const QRectF& ventanaRect) = 0;

    /**
     * @brief Comprueba si la condición de finalización del nivel se ha cumplido.
     * @return true si el nivel ha terminado, false en caso contrario.
     * @note Método const, no modifica el estado del nivel.
     */
    virtual bool estaTerminado() const = 0;
};
