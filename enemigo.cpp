#include "enemigo.h"
#include <cstdlib>

Enemigo::Enemigo(float x, float y, float ancho, float alto)
    : Luchador(x, y, ancho, alto),
    estadoIA(EstadoIA::Esperar), temporizadorEstado(2.0f)
{}

void Enemigo::actualizar(float deltaTiempo) {
    Luchador::actualizar(deltaTiempo);

    temporizadorEstado -= deltaTiempo;
    if (temporizadorEstado <= 0) {
        decidirAccion();
        temporizadorEstado = 2.0f + (rand() % 2);
    }
}

void Enemigo::decidirAccion() {
    int decision = rand() % 3;
    if (decision == 0) {
        estadoIA = EstadoIA::Esperar;
        velocidadX = 0;
    } else if (decision == 1) {
        estadoIA = EstadoIA::Atacar;
        atacar();
    } else {
        estadoIA = EstadoIA::Defender;
        // lógica futura: reducir daño
    }
}

void Enemigo::atacar() {
    if (cooldownAtaque <= 0) {
        estaAtacando = true;
        cooldownAtaque = 1.0f;
    }
}
