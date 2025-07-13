#pragma once

#include "Entidad.h"

// Declaración adelantada para evitar incluir la cabecera completa de Luchador.
class Luchador;

/**
 * @class Hitbox
 * @brief Representa un área de ataque temporal y activa.
 *
 * Es una Entidad invisible de corta duración que se crea cuando un Luchador
 * ataca. Es responsable de detectar la colisión con otros luchadores.
 */
class Hitbox : public Entidad {
public:
    /**
     * @brief Constructor de la clase Hitbox.
     * @param x Posición X inicial.
     * @param y Posición Y inicial.
     * @param ancho Ancho de la hitbox.
     * @param alto Alto de la hitbox.
     * @param dano Cantidad de daño que inflige.
     * @param duracion Tiempo en segundos que la hitbox permanecerá activa.
     */
    Hitbox(float x, float y, float ancho, float alto, float dano, float duracion, Entidad* duenio);

    // Destructor.
    ~Hitbox();

    // --- Implementación del método virtual de Entidad ---
    void actualizar(float deltaTiempo) override;

    /**
     * @brief Comprueba si la hitbox ha expirado.
     * @return true si su tiempo de vida ha terminado, false en caso contrario.
     */
    bool haExpirado() const;

    float getDanoQueProvoca() const { return danoQueProvoca; }
    Entidad* getDuenio() const { return duenio; }


private:
    float danoQueProvoca;
    float duracionVida; // El tiempo que le queda de vida a la hitbox.
    Entidad* duenio;
};
