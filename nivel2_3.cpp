#include "nivel2_3.h"
#include <cmath>
#include <QDebug>

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


    // Victoria
    audioVictoria = new QAudioOutput();
    playerVictoria = new QMediaPlayer();
    playerVictoria->setAudioOutput(audioVictoria);
    playerVictoria->setSource(QUrl("qrc:/Sonidos/Victoria.mp3"));
    audioVictoria->setVolume(0.8f);

    // Derrota
    audioDerrota = new QAudioOutput();
    playerDerrota = new QMediaPlayer();
    playerDerrota->setAudioOutput(audioDerrota);
    playerDerrota->setSource(QUrl("qrc:/Sonidos/Derrota.mp3"));
    audioDerrota->setVolume(0.8f);

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
    qDebug() << "Ejecutando Nivel2_3::inicializar()...";

    // --- Crear jugador ---
    jugador = new PersonajeJugador(100, 400, 50, 80);
    jugador->setDireccion(1);  // Inicialmente mira a la derecha

    // --- Crear enemigo según el número de nivel ---
    switch (numeroNivel) {
    case 2:
        enemigo = new Enemigo(500, 400, 50, 80);
        enemigo->setDireccion(-1);  // Inicialmente mira a la izquierda
        // TODO: Asignar estadísticas específicas para Ten Shin Han
        qDebug() << "Enemigo: Ten Shin Han creado.";
        break;

    case 3:
        enemigo = new Enemigo(500, 400, 50, 80);
        enemigo->setDireccion(-1);  // Inicialmente mira a la izquierda
        qDebug() << "Enemigo: Piccolo creado.";
        enemigo->setVida(150.0f);          // Más vida
        enemigo->setCooldownAtaque(0.5f);  // Más rápido para atacar
        static_cast<Enemigo*>(enemigo)->resistencia = 0.5f;  // Recibe solo el 50% del daño
        break;

    default:
        qDebug() << "¡ERROR! Número de nivel inválido:" << numeroNivel;
        enemigo = nullptr;
        break;
    }

    // --- Verificación final ---
    if (jugador && enemigo) {
        qDebug() << "Jugador y enemigo creados y asignados correctamente.";
    } else {
        qDebug() << "¡ERROR! Uno o ambos punteros a personajes son nullptr.";
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
        tiempoFinalizacion -= deltaTiempo;
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

    }

    // El resto de la función permanece igual.
    for (auto h : hitboxesActivas) {
        h->actualizar(deltaTiempo);
    }

    revisarColisiones();
    limpiarHitboxes();


    // Cronómetro
    tiempoRestante -= deltaTiempo;
    if (tiempoRestante <= 0.0f) {
        estadoActual = Estado::DERROTA;
        sonidoDerrota.play();
        tiempoFinalizacion = 3.0f;
    }
    if (!jugador->estaVivo()) {
        estadoActual = Estado::DERROTA;
        sonidoDerrota.play();
        tiempoFinalizacion = 3.0f;
    }
    else if (!enemigo->estaVivo()) {
        estadoActual = Estado::VICTORIA;
        sonidoVictoria.play();
        tiempoFinalizacion = 3.0f;
    }
}


void Nivel2_3::dibujar(QPainter* painter, const QRectF& ventanaRect, const std::map<std::string, QPixmap>& sprites)
{
    // --- 1. DIBUJAR EL FONDO ---
    auto itFondo = sprites.find("fondo_torneo");
    if (itFondo != sprites.end()) {
        const QPixmap& fondo = itFondo->second;
        painter->drawPixmap(ventanaRect, fondo, fondo.rect());
    }

    // --- 2. DIBUJAR LOS PERSONAJES (SPRITES) ---
    // Jugador
    if (jugador) {
        std::string claveSpriteJugador;

        if (personajeElegido == PersonajeSeleccionado::GOKU) {
            if (jugador->getEstaAtacando()) {
                if (jugador->getTipoAtaque() == TipoAtaque::Puno) {
                    if (jugador->getDireccion() == 1)
                        claveSpriteJugador = "goku_puno_derecha";
                    else
                        claveSpriteJugador = "goku_puno_izquierda";
                } else if (jugador->getTipoAtaque() == TipoAtaque::Patada) {
                    if (jugador->getDireccion() == 1)
                        claveSpriteJugador = "goku_patada_derecha";
                    else
                        claveSpriteJugador = "goku_patada_izquierda";
                }
            } else if (jugador->getVelocidadX() != 0) {
                if (jugador->getDireccion() == 1)
                    claveSpriteJugador = "goku_derecha";
                else
                    claveSpriteJugador = "goku_izquierda";
            } else {
                if (jugador->getDireccion() == 1)
                    claveSpriteJugador = "goku_derecha";
                else
                    claveSpriteJugador = "goku_izquierda";
            }
        }
        else if (personajeElegido == PersonajeSeleccionado::KRILIN) {
            if (jugador->getEstaAtacando()) {
                if (jugador->getTipoAtaque() == TipoAtaque::Puno) {
                    if (jugador->getDireccion() == 1)
                        claveSpriteJugador = "krilin_puno_derecha";
                    else
                        claveSpriteJugador = "krilin_puno_izquierda";
                } else if (jugador->getTipoAtaque() == TipoAtaque::Patada) {
                    if (jugador->getDireccion() == 1)
                        claveSpriteJugador = "krilin_patada_derecha";
                    else
                        claveSpriteJugador = "krilin_patada_izquierda";
                }
            } else if (jugador->getVelocidadX() != 0) {
                if (jugador->getDireccion() == 1)
                    claveSpriteJugador = "krilin_derecha";
                else
                    claveSpriteJugador = "krilin_izquierda";
            } else {
                if (jugador->getDireccion() == 1)
                    claveSpriteJugador = "krilin_derecha";
                else
                    claveSpriteJugador = "krilin_izquierda";
            }
        }
        else if (personajeElegido == PersonajeSeleccionado::YAMCHA) {
            if (jugador->getEstaAtacando()) {
                if (jugador->getTipoAtaque() == TipoAtaque::Puno) {
                    if (jugador->getDireccion() == 1)
                        claveSpriteJugador = "yamcha_puno_derecha";
                    else
                        claveSpriteJugador = "yamcha_puno_izquierda";
                } else if (jugador->getTipoAtaque() == TipoAtaque::Patada) {
                    if (jugador->getDireccion() == 1)
                        claveSpriteJugador = "yamcha_patada_derecha";
                    else
                        claveSpriteJugador = "yamcha_patada_izquierda";
                }
            } else if (jugador->getVelocidadX() != 0) {
                if (jugador->getDireccion() == 1)
                    claveSpriteJugador = "yamcha_derecha";
                else
                    claveSpriteJugador = "yamcha_izquierda";
            } else {
                if (jugador->getDireccion() == 1)
                    claveSpriteJugador = "yamcha_derecha";
                else
                    claveSpriteJugador = "yamcha_izquierda";
            }
        }

        auto itJugador = sprites.find(claveSpriteJugador);
        if (itJugador != sprites.end()) {
            const QPixmap& spriteJugador = itJugador->second;
            painter->drawPixmap(jugador->getBoundingRect(), spriteJugador, spriteJugador.rect());
        }
    }


    // Enemigo
    if (enemigo) {
        std::string claveSpriteEnemigo;
        std::string baseEnemigo;

        if (numeroNivel == 2)
            baseEnemigo = "ten";
        else if (numeroNivel == 3)
            baseEnemigo = "picoro";
        else
            baseEnemigo = "ten"; // Fallback
        // Determinar nombre base (Ten o Picoro)
        if (enemigo->getEstaAtacando()) {
            if (enemigo->getTipoAtaque() == TipoAtaque::Puno) {
                if (enemigo->getDireccion() == 1)
                    claveSpriteEnemigo = baseEnemigo + "_puno_derecha";
                else
                    claveSpriteEnemigo = baseEnemigo + "_puno_izquierda";
            } else if (enemigo->getTipoAtaque() == TipoAtaque::Patada) {
                if (enemigo->getDireccion() == 1)
                    claveSpriteEnemigo = baseEnemigo + "_patada_derecha";
                else
                    claveSpriteEnemigo = baseEnemigo + "_patada_izquierda";
            }
        } else {
            if (enemigo->getDireccion() == 1)
                claveSpriteEnemigo = baseEnemigo + "_derecha";
            else
                claveSpriteEnemigo = baseEnemigo + "_izquierda";
        }

        auto itEnemigo = sprites.find(claveSpriteEnemigo);
        if (itEnemigo != sprites.end()) {
            const QPixmap& spriteEnemigo = itEnemigo->second;
            painter->drawPixmap(enemigo->getBoundingRect(), spriteEnemigo, spriteEnemigo.rect());
        }
    }


    // --- 3. DIBUJAR LA INTERFAZ DE USUARIO (UI) ---
    // Barras de vida
    painter->setBrush(Qt::green);
    painter->drawRect(50, 50, static_cast<int>(jugador->getVida()) * 2, 20);

    painter->setBrush(Qt::red);
    painter->drawRect(450, 50, static_cast<int>(enemigo->getVida()) * 2, 20);

    // Temporizador
    painter->setPen(Qt::white);
    painter->setFont(QFont("Arial", 24, QFont::Bold));
    painter->drawText(370, 70, QString::number(static_cast<int>(tiempoRestante)));

    // Cuenta regresiva inicial
    if (estadoActual == Estado::CUENTA_REGRESIVA) {
        painter->setFont(QFont("Arial", 72, QFont::Bold));
        int num = static_cast<int>(ceil(tiempoCuentaRegresiva));
        painter->drawText(ventanaRect, Qt::AlignCenter, QString::number(num));
    }

    // Texto de fin de partida
    if (estadoActual == Estado::VICTORIA) {
        painter->setFont(QFont("Arial", 48, QFont::Bold));
        painter->drawText(ventanaRect, Qt::AlignCenter, "¡Victoria!");
    } else if (estadoActual == Estado::DERROTA) {
        painter->setFont(QFont("Arial", 48, QFont::Bold));
        painter->drawText(ventanaRect, Qt::AlignCenter, "Derrota");
    }
}

void Nivel2_3::procesarInput(QKeyEvent* evento) {
    teclasPresionadas.insert(evento->key());
    jugador->procesarInput(teclasPresionadas);
}

void Nivel2_3::procesarInputLiberado(QKeyEvent* evento) {
    teclasPresionadas.remove(evento->key());
    jugador->procesarInput(teclasPresionadas);
}
void Nivel2_3::recibirInput(const QSet<int>& teclas) {
    teclasPresionadas = teclas;
}
bool Nivel2_3::estaTerminado() const {
    return (estadoActual == Estado::VICTORIA || estadoActual == Estado::DERROTA) && tiempoFinalizacion <= 0.0f;
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


