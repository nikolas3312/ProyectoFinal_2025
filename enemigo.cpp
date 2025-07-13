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

    // Limitar bordes
    if (posX < 0)
        posX = 0;
    if (posX > 800 - ancho)
        posX = 800 - ancho;
}

void Enemigo::decidirAccion() {
    int decision = rand() % 3;
    if (decision == 0) {
        estadoIA = EstadoIA::Esperar;
        velocidadX = 0;
    } else if (decision == 1) {
        estadoIA = EstadoIA::Atacar;
        int tipoAtaque = rand() % 2;
        if (tipoAtaque == 0)
            atacarPuño();
        else
            atacarPatada();
    }

     else {
        estadoIA = EstadoIA::Defender;
        // lógica futura: reducir daño
    }
}


void Enemigo::atacarPuño() {
    if (cooldownAtaque <= 0) {
        estaAtacando = true;
        cooldownAtaque = 1.0f;
        dañoBase = 10.0f;
    }
}

void Enemigo::atacarPatada() {
    if (cooldownAtaque <= 0) {
        estaAtacando = true;
        cooldownAtaque = 1.2f;
        dañoBase = 20.0f;
    }
}
