#include "nivel2_3.h"
#include <cmath>

Nivel2_3::Nivel2_3(PersonajeSeleccionado personaje, int numeroNivel)
    : estadoActual(Estado::CUENTA_REGRESIVA),
    personajeElegido(personaje),
    jugador(nullptr),
    enemigo(nullptr),
    tiempoCuentaRegresiva(3.0f),
    numeroNivel(numeroNivel)
{
}

Nivel2_3::~Nivel2_3() {
    delete jugador;
    delete enemigo;
    for (auto h : hitboxesActivas)
        delete h;
    hitboxesActivas.clear();
}

void Nivel2_3::inicializar()
{
    // Crear jugador
    jugador = new PersonajeJugador(100, 400, 50, 80);

    // Según el nivel, crear enemigo
    if (numeroNivel == 2) {
        enemigo = new Enemigo(500, 400, 50, 80);
        // poner stats específicos de Ten Shin Han
    } else if (numeroNivel == 3) {
        enemigo = new Enemigo(500, 400, 50, 80);
        // poner stats para Piccolo
    }
}
void Nivel2_3::actualizar(float deltaTiempo) {

    switch (estadoActual) {
    case Estado::CUENTA_REGRESIVA:
        actualizarCuentaRegresiva(deltaTiempo);
        break;
    case Estado::JUGANDO:
        actualizarCombate(deltaTiempo, teclasPresionadas);
        break;
    case Estado::VICTORIA:
    case Estado::DERROTA:
        break;
    }
}
void Nivel2_3::actualizarCuentaRegresiva(float deltaTiempo) {
    tiempoCuentaRegresiva -= deltaTiempo;
    if (tiempoCuentaRegresiva <= 0.0f) {
        estadoActual = Estado::JUGANDO;
    }
}

void Nivel2_3::actualizarCombate(float deltaTiempo, const QSet<int>& teclas)
{
    jugador->procesarInput(teclas);
    jugador->actualizar(deltaTiempo);
    enemigo->actualizar(deltaTiempo);

    if (jugador->getEstaAtacando()) {
        hitboxesActivas.push_back(new Hitbox(jugador->getBoundingRect(), jugador->getDañoBase(), 0.2f));
        jugador->setEstaAtacando(false);
    }

    if (enemigo->getEstaAtacando()) {
        hitboxesActivas.push_back(new Hitbox(enemigo->getBoundingRect(), enemigo->getDañoBase(), 0.2f));
        enemigo->setEstaAtacando(false);
    }


    for (auto h : hitboxesActivas)
        h->actualizar(deltaTiempo);

    revisarColisiones();
    limpiarHitboxes();

    if (!jugador->estaVivo())
        estadoActual = Estado::DERROTA;
    else if (!enemigo->estaVivo())
        estadoActual = Estado::VICTORIA;
}

void Nivel2_3::dibujar(QPainter* painter) {
    painter->setBrush(Qt::blue);
    painter->drawRect(jugador->getBoundingRect());

    painter->setBrush(Qt::red);
    painter->drawRect(enemigo->getBoundingRect());
    //dibujar hitboxes
    painter->setBrush(Qt::yellow);
    for (auto h : hitboxesActivas) {
        if (h->estaActiva())
            painter->drawRect(h->rect);
    }
    //dibujar UI
    painter->setPen(Qt::white);
    painter->setFont(QFont("Arial", 24, QFont::Bold));

    if (estadoActual == Estado::CUENTA_REGRESIVA) {
        int num = static_cast<int>(ceil(tiempoCuentaRegresiva));
        painter->drawText(300, 200, QString::number(num));
    }
}

bool Nivel2_3::estaTerminado() const {
    return estadoActual == Estado::VICTORIA || estadoActual == Estado::DERROTA;
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

void Nivel2_3::recibirInput(const QSet<int>& teclas) {
    teclasPresionadas = teclas;
}
