#include "nivel2_3.h"

Nivel2_3::Nivel2_3() {
    jugador = new PersonajeJugador(100, 400, 50, 80);
    enemigo = new Enemigo(500, 400, 50, 80);
    estado = EstadoJuego::Jugando;
}

Nivel2_3::~Nivel2_3() {
    delete jugador;
    delete enemigo;
    for (auto h : hitboxesActivas) delete h;
}

void Nivel2_3::actualizar(float deltaTiempo, const QSet<int>& teclas) {
    if (estado != EstadoJuego::Jugando) return;

    jugador->procesarInput(teclas);
    jugador->actualizar(deltaTiempo);
    enemigo->actualizar(deltaTiempo);

    if (jugador->estaAtacando) {
        hitboxesActivas.push_back(new Hitbox(jugador->getBoundingRect(), jugador->dañoBase, 0.2f));
        jugador->estaAtacando = false;
    }

    if (enemigo->estaAtacando) {
        hitboxesActivas.push_back(new Hitbox(enemigo->getBoundingRect(), enemigo->dañoBase, 0.2f));
        enemigo->estaAtacando = false;
    }

    for (auto h : hitboxesActivas)
        h->actualizar(deltaTiempo);

    revisarColisiones();
    limpiarHitboxes();

    if (!jugador->estaVivo())
        estado = EstadoJuego::Perdido;
    else if (!enemigo->estaVivo())
        estado = EstadoJuego::Ganado;
}

void Nivel2_3::dibujar(QPainter* painter) {
    painter->setBrush(Qt::blue);
    painter->drawRect(jugador->getBoundingRect());

    painter->setBrush(Qt::red);
    painter->drawRect(enemigo->getBoundingRect());

    painter->setBrush(Qt::yellow);
    for (auto h : hitboxesActivas) {
        if (h->estaActiva())
            painter->drawRect(h->rect);
    }
}

EstadoJuego Nivel2_3::getEstadoJuego() const {
    return estado;
}

void Nivel2_3::revisarColisiones() {
    for (auto h : hitboxesActivas) {
        if (!h->estaActiva()) continue;

        if (h->rect.intersects(jugador->getBoundingRect())) {
            jugador->recibirDaño(h->daño);
        }

        if (h->rect.intersects(enemigo->getBoundingRect())) {
            enemigo->recibirDaño(h->daño);
        }
    }
}

void Nivel2_3::limpiarHitboxes() {
    auto it = hitboxesActivas.begin();
    while (it != hitboxesActivas.end()) {
        if (!(*it)->estaActiva()) {
            delete *it;
            it = hitboxesActivas.erase(it);
        } else {
            ++it;
        }
    }
}
