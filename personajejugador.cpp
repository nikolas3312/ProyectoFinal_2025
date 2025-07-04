#include "personajejugador.h"
#include <Qt>

PersonajeJugador::PersonajeJugador(float x, float y, float ancho, float alto)
    : Luchador(x, y, ancho, alto)
{}

void PersonajeJugador::procesarInput(const QSet<int>& teclas) {
    velocidadX = 0;

    if (teclas.contains(Qt::Key_Left)) {
        velocidadX = -200.0f;
    }
    if (teclas.contains(Qt::Key_Right)) {
        velocidadX = 200.0f;
    }
    if (teclas.contains(Qt::Key_Up)) {
        saltar();
    }
    if (teclas.contains(Qt::Key_Space)) {
        atacar();
    }
}

void PersonajeJugador::atacar() {
    if (cooldownAtaque <= 0) {
        estaAtacando = true;
        cooldownAtaque = 0.5f;
        // Aquí crearías la hitbox real en Nivel2_3
    }
}
