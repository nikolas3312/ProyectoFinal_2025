#include "Entidad.h"
#include <QColor>

/**
 * @brief Constructor de la clase Entidad.
 * Inicializa los atributos de posición y tamaño de la entidad,
 * y establece la velocidad inicial en cero.
 */
Entidad::Entidad(float x, float y, float ancho, float alto)
    : posX(x),
    posY(y),
    ancho(ancho),
    alto(alto),
    velocidadX(0.0f),
    velocidadY(0.0f)
{
    // El cuerpo del constructor está vacío porque toda la inicialización
    // se realiza en la lista de inicializadores de miembro de arriba.
}

/**
 * @brief Destructor virtual de la clase Entidad.
 * No realiza ninguna acción específica, pero su presencia como virtual
 * es crucial para la correcta liberación de memoria de las clases derivadas.
 */
Entidad::~Entidad()
{
}

/**
 * @brief Dibuja una representación visual por defecto para la entidad.
 * Este método dibuja un rectángulo rojo semi-transparente que coincide
 * con el BoundingRect del objeto. Es útil para depuración visual.
 * Las clases hijas pueden (y deberían) sobreescribir este método.
 * @param painter Puntero al QPainter que se usará para el dibujo.
 */
void Entidad::dibujar(QPainter* painter)
{
    // Dibuja el rectángulo de colisión con un color de depuración.
    // Esto es útil para ver el área de colisión de cualquier entidad
    // que no haya implementado su propio método de dibujo.
    QColor colorDeDepuracion(255, 0, 0, 100); // Rojo, semi-transparente
    painter->fillRect(getBoundingRect(), colorDeDepuracion);
}

/**
 * @brief Obtiene el rectángulo de colisión del objeto.
 * @return Un QRectF que representa el área y posición del objeto.
 */
QRectF Entidad::getBoundingRect() const
{
    return QRectF(posX, posY, ancho, alto);
}

/**
 * @brief Obtiene la posición actual (esquina superior izquierda) del objeto.
 * @return Un QPointF que representa la posición (x, y).
 */
QPointF Entidad::getPosicion() const
{
    return QPointF(posX, posY);
}
