#include "hitbox.h"

Hitbox::Hitbox(const QRectF& r, float d, float dur)
    : rect(r), daño(d), duracion(dur), tiempoActual(0)
{}

bool Hitbox::estaActiva() const {
    return tiempoActual < duracion;
}

void Hitbox::actualizar(float deltaTiempo) {
    tiempoActual += deltaTiempo;
}
