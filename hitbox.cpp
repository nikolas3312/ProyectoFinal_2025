#include "Hitbox.h"
#include "Luchador.h" // Se incluye aquí, no en el .h

/**
 * @brief Constructor de Hitbox.
 * Llama al constructor de Entidad y luego inicializa sus propios atributos.
 */
Hitbox::Hitbox(float x, float y, float ancho, float alto, float dano, float duracion, Entidad* duenio)
    // Llama al constructor de la clase padre 'Entidad'.
    : Entidad(x, y, ancho, alto),
    danoQueProvoca(dano),
    duracionVida(duracion),
    duenio(duenio)
{
    // El cuerpo del constructor puede estar vacío.
}

/**
 * @brief Destructor de la clase Hitbox.
 */
Hitbox::~Hitbox()
{
}

/**
 * @brief Actualiza el estado de la hitbox, principalmente su duración.
 * @param deltaTiempo El tiempo transcurrido desde el último fotograma.
 */
void Hitbox::actualizar(float deltaTiempo)
{
    // La hitbox no se mueve, solo su tiempo de vida se reduce.
    duracionVida -= deltaTiempo;
}

/**
 * @brief Comprueba si la hitbox ya no debe estar activa.
 * @return true si el tiempo de vida es menor o igual a cero.
 */
bool Hitbox::haExpirado() const
{
    return duracionVida <= 0;
}

