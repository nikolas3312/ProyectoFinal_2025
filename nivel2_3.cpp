#include "nivel2_3.h"
#include <cmath>

Nivel2_3::Nivel2_3(PersonajeSeleccionado personaje, int numeroNivel)
    : estadoActual(Estado::CUENTA_REGRESIVA),
    personajeElegido(personaje),
    jugador(nullptr),
    enemigo(nullptr),
    tiempoCuentaRegresiva(3.0f),
    tiempoRestante(99.0f),
    tiempoFinalizacion(3.0f),
    numeroNivel(numeroNivel),
    fondoEscenario("images/Fondo_torneo.jpeg")
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
    jugador->setDireccion(1);  // Inicialmente mira a la derecha

    // Según el nivel, crear enemigo
    if (numeroNivel == 2) {
        enemigo = new Enemigo(500, 400, 50, 80);
        enemigo->setDireccion(-1);  // Inicialmente mira a la izquierda
        // poner stats específicos de Ten Shin Han
    } else if (numeroNivel == 3) {
        enemigo = new Enemigo(500, 400, 50, 80);
        enemigo->setDireccion(-1);  // Inicialmente mira a la izquierda
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
        if (tiempoFinalizacion <=0.0f) {

        break;
    }
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
    // Actualizar dirección (mirada)
    if (jugador->getPosX() < enemigo->getPosX())
        jugador->setDireccion(1);
    else
        jugador->setDireccion(-1);

    if (enemigo->getPosX() < jugador->getPosX())
        enemigo->setDireccion(1);
    else
        enemigo->setDireccion(-1);


    jugador->procesarInput(teclas);
    jugador->actualizar(deltaTiempo);

    // Movimiento simple enemigo: se acerca al jugador
    if (enemigo->getPosX() > jugador->getPosX() + 60)
        enemigo->setVelocidadX(-80.0f);
    else if (enemigo->getPosX() < jugador->getPosX() - 60)
        enemigo->setVelocidadX(80.0f);
    else
        enemigo->setVelocidadX(0.0f);

    enemigo->actualizar(deltaTiempo);

    // Revisar colisión para que no se atraviesen
    QRectF rectJugador = jugador->getBoundingRect();
    QRectF rectEnemigo = enemigo->getBoundingRect();

    if (rectJugador.intersects(rectEnemigo)) {
        if (jugador->getPosX() < enemigo->getPosX()) {
            jugador->setPosX(jugador->getPosX() - 5);
            enemigo->setPosX(enemigo->getPosX() + 5);
        } else {
            jugador->setPosX(jugador->getPosX() + 5);
            enemigo->setPosX(enemigo->getPosX() - 5);
        }
    }

    // --- Creación de Hitbox para el Jugador ---
    if (jugador->getEstaAtacando()) {
        float hitboxX;
        // Obtenemos el rectángulo del jugador para calcular la posición de la hitbox.
        QRectF rectJugador = jugador->getBoundingRect();

        // NOTA: Aquí se debería calcular una posición y tamaño adecuados para el puño/patada.
        // Por ahora, para que compile, usamos los datos del rectángulo del jugador.
        if (jugador->getDireccion() == 1)
            hitboxX = rectJugador.x() + rectJugador.width();
        else
            hitboxX = rectJugador.x() - 40.0f;

        float hitboxY = rectJugador.y() + 20;                  // Ejemplo: a la altura del torso
        float hitboxAncho = 40.0f;
        float hitboxAlto = 20.0f;

        // Se llama al constructor de Hitbox con los 7 argumentos correctos.
        hitboxesActivas.push_back(new Hitbox(hitboxX, hitboxY, hitboxAncho, hitboxAlto, jugador->getDañoBase(), 0.2f, jugador));

        jugador->setEstaAtacando(false);
    }

    // --- Creación de Hitbox para el Enemigo ---
    if (enemigo->getEstaAtacando()) {
        float hitboxX;
        // Hacemos lo mismo para el enemigo.
        QRectF rectEnemigo = enemigo->getBoundingRect();

        if (enemigo->getDireccion() == 1)
            hitboxX = rectEnemigo.x() + rectEnemigo.width();
        else
            hitboxX = rectEnemigo.x() - 40.0f;

        float hitboxY = rectEnemigo.y() + 20;
        float hitboxAncho = 40.0f;
        float hitboxAlto = 20.0f;

        // Se llama al constructor con los 7 argumentos correctos.
        hitboxesActivas.push_back(new Hitbox(hitboxX, hitboxY, hitboxAncho, hitboxAlto, enemigo->getDañoBase(), 0.2f, enemigo));

        enemigo->setEstaAtacando(false);
    }

    // El resto de la función permanece igual.
    for (auto h : hitboxesActivas) {
        h->actualizar(deltaTiempo);
    }

    revisarColisiones();
    limpiarHitboxes();


    // Cronómetro
    tiempoRestante -= deltaTiempo;
    if (tiempoRestante <= 0.0f)
        estadoActual = Estado::DERROTA;

    if (!jugador->estaVivo())
        estadoActual = Estado::DERROTA;
    else if (!enemigo->estaVivo())
        estadoActual = Estado::VICTORIA;
}


void Nivel2_3::dibujar(QPainter* painter, const QRectF& ventanaRect, const std::map<std::string, QPixmap>& sprites)
{
    // Fondo
    painter->drawPixmap(ventanaRect.toRect(), fondoEscenario);

    //Jugador
    painter->setBrush(Qt::blue);
    painter->drawRect(jugador->getBoundingRect());
    //Enemigo
    painter->setBrush(Qt::red);
    painter->drawRect(enemigo->getBoundingRect());
    //dibujar hitboxes
    painter->setBrush(Qt::yellow);
    for (auto h : hitboxesActivas) {
        // Asumiendo que Hitbox tiene un método para saber si está activa
        // y para obtener su rectángulo. En nuestro diseño sería h->getBoundingRect().
        if (!h->haExpirado())
            painter->drawRect(h->getBoundingRect());
    }
    // Barras de vida
    painter->setBrush(Qt::green);
    painter->drawRect(50, 50, jugador->getVida() * 2, 20);

    painter->setBrush(Qt::red);
    painter->drawRect(550, 50, enemigo->getVida() * 2, 20);

    // Temporizador
    painter->setPen(Qt::white);
    painter->setFont(QFont("Arial", 24, QFont::Bold));
    painter->drawText(370, 50, QString::number(static_cast<int>(tiempoRestante)));

    // El estado del nivel debe tener su propia lógica de cuenta regresiva si es necesaria.
    if (estadoActual == Estado::CUENTA_REGRESIVA) {
        int num = static_cast<int>(ceil(tiempoCuentaRegresiva));
        painter->drawText(300, 200, QString::number(num));
    }
    //Mostrar texto final (victoria o derrota)
    if (estadoActual == Estado::VICTORIA) {
        painter->setPen(Qt::white);
        painter->setFont(QFont("Arial", 48, QFont::Bold));
        painter->drawText(200, 300, "¡Victoria!");
    }
    else if (estadoActual == Estado::DERROTA) {
        painter->setPen(Qt::white);
        painter->setFont(QFont("Arial", 48, QFont::Bold));
        painter->drawText(200, 300, "Derrota");
    }

}
void Nivel2_3::procesarInput(QKeyEvent* evento) { Q_UNUSED(evento); }
void Nivel2_3::procesarInputLiberado(QKeyEvent* evento) { Q_UNUSED(evento); }
bool Nivel2_3::estaTerminado() const {
    return estadoActual == Estado::VICTORIA || estadoActual == Estado::DERROTA;
}

void Nivel2_3::revisarColisiones() {
    for (auto h : hitboxesActivas) {
        if (!h->haExpirado())
         continue;

        if (h->getDuenio() != jugador && h->getBoundingRect().intersects(jugador->getBoundingRect())) {
            jugador->recibirDaño(h->getDanoQueProvoca());
        }

        if (h->getDuenio() != enemigo && h->getBoundingRect().intersects(enemigo->getBoundingRect())) {
            enemigo->recibirDaño(h->getDanoQueProvoca());
        }
    }
}

void Nivel2_3::limpiarHitboxes() {
    auto it = hitboxesActivas.begin();
    while (it != hitboxesActivas.end()) {
        if ((*it)->haExpirado()) {
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
