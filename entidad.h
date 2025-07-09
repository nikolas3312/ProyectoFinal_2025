#ifndef ENTIDAD_H
#define ENTIDAD_H

#pragma once

#include <QPointF>
#include <QRectF>
#include <QPainter>

/**
 * @class Entidad
 * @brief Clase base abstracta para todos los objetos del juego.
 *
 * Define las propiedades y comportamientos comunes de cualquier objeto que
 * pueda existir y ser renderizado en el mundo del juego, como la posición,
 * el tamaño y la velocidad. Al ser abstracta, no se pueden crear instancias
 * directas de esta clase.
 */
class Entidad {
public:
    /**
     * @brief Constructor de la clase Entidad.
     * @param x Posición inicial en el eje X.
     * @param y Posición inicial en el eje Y.
     * @param ancho Ancho inicial del objeto.
     * @param alto Alto inicial del objeto.
     */
    Entidad(float x, float y, float ancho, float alto);

    // Destructor virtual para asegurar la correcta destrucción de objetos derivados.
    virtual ~Entidad();

    /**
     * @brief Actualiza el estado lógico de la entidad en cada fotograma.
     * @param deltaTiempo El tiempo transcurrido desde el último fotograma, en segundos.
     * @note Es un método virtual puro y debe ser implementado por todas las clases hijas concretas.
     */
    virtual void actualizar(float deltaTiempo) = 0;

    /**
     * @brief Dibuja la entidad en la pantalla.
     * @param painter Puntero al objeto QPainter que se utilizará para el dibujo.
     * @note Las clases hijas pueden sobreescribir este método para un renderizado personalizado.
     */
    virtual void dibujar(QPainter* painter);

    /**
     * @brief Obtiene el rectángulo de colisión del objeto.
     * @return Un QRectF que representa el área del objeto para la detección de colisiones.
     * @note Método const, no modifica el estado del objeto.
     */
    QRectF getBoundingRect() const;

    /**
     * @brief Obtiene la posición actual de la esquina superior izquierda del objeto.
     * @return Un QPointF que representa la posición (x, y).
     * @note Método const, no modifica el estado del objeto.
     */
    QPointF getPosicion() const;
    void setVelocidadY(float vy);
    float getVelocidadY() const;
protected:
    // Atributos protegidos para permitir el acceso directo por parte de las clases derivadas
    // en sus cálculos de física y movimiento, lo cual es más eficiente que usar setters.

    float posX, posY;       // Posición actual en el mundo del juego.
    float ancho, alto;      // Dimensiones del rectángulo de colisión.
    float velocidadX, velocidadY; // Componentes de la velocidad actual.
};
#endif // ENTIDAD_H
