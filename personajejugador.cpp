#include "personajejugador.h"
#include <Qt>

PersonajeJugador::PersonajeJugador(float x, float y, float ancho, float alto)
    : Luchador(x, y, ancho, alto)
{}

void PersonajeJugador::actualizar(float deltaTiempo)
{
    Luchador::actualizar(deltaTiempo);
    // Limitar bordes
    if (posX < 0)
        posX = 0;
    if (posX > 800 - ancho)
        posX = 800 - ancho;
}

void PersonajeJugador::dibujar(QPainter* painter)
{
    if(tiempoDaño > 0)
        painter->setBrush(Qt::red);
    else
        painter->setBrush(Qt::blue);

    painter->drawRect(getBoundingRect());
}


void PersonajeJugador::procesarInput(const QSet<int>& teclas) {
    velocidadX = 0.0f;

    if (teclas.contains(Qt::Key_A)) {
        velocidadX = -150.0f;
    }
    if (teclas.contains(Qt::Key_D)) {
        velocidadX = 150.0f;
    }
    if (teclas.contains(Qt::Key_W) && estaEnElSuelo()) {
        saltar();
    }
    // --- Ataque puño ---
    if (teclas.contains(Qt::Key_J))
        atacarPuño();

    // --- Ataque patada ---
    if (teclas.contains(Qt::Key_K))
        atacarPatada();
    if (teclas.contains(Qt::Key_L)) {
        setDefensa(true);
    } else {
        setDefensa(false);
    }
}

void PersonajeJugador::atacarPuño()
{
    if (!estaAtacando && cooldownAtaque <= 0.0f) {
        estaAtacando = true;
        tipoAtaque = TipoAtaque::Puno;
        dañoBase = 10.0f;  // daño para puño
        cooldownAtaque = 0.5f; // tiempo para volver a atacar
        tiempoAtaque = 0.2f;
    }

}
void PersonajeJugador::atacarPatada()
{
    if (!estaAtacando && cooldownAtaque <= 0.0f) {
        estaAtacando = true;
        tipoAtaque = TipoAtaque::Patada;
        dañoBase = 20.0f;  // daño para patada
        cooldownAtaque = 0.7f; // tiempo para volver a atacar
        tiempoAtaque = 0.2f;
    }
}
