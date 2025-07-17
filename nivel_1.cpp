#include "Nivel_1.h"
#include <cstdlib>  // rand()
#include <ctime>    // time()
#include <cmath>    // ceil()
#include <QDebug>
// --- Constantes de configuración del Nivel ---
constexpr float TIEMPO_A_SOBREVIVIR = 60.0f;
constexpr float TIEMPO_INICIAL_CUENTA_REGRESIVA = 3.0f;
constexpr float INTERVALO_GENERACION_OBSTACULO = 0.5f;
constexpr float ACELERACION_INICIAL = 0.2f;

/**
 * @brief Constructor. Inicializa el estado y guarda el personaje elegido.
 */
Nivel_1::Nivel_1(PersonajeSeleccionado personaje)
    : estadoActual(Estado::CUENTA_REGRESIVA),
    personajeElegido(personaje),
    jugador(nullptr),
    tiempoObjetivo(TIEMPO_A_SOBREVIVIR),
    tiempoRestante(TIEMPO_A_SOBREVIVIR),
    aceleracionGlobal(ACELERACION_INICIAL),
    tiempoParaSiguienteObstaculo(0.0f),
    tiempoCuentaRegresiva(TIEMPO_INICIAL_CUENTA_REGRESIVA)
{
    srand(time(0));
}

/**
 * @brief Destructor. Libera la memoria de todos los objetos dinámicos.
 */
Nivel_1::~Nivel_1()
{
    delete jugador;
    for (Obstaculo* obs : obstaculos) {
        delete obs;
    }
    obstaculos.clear();
}

/**
 * @brief Prepara el nivel para ser jugado.
 */
void Nivel_1::inicializar()
{
    jugador = new PersonajeJugadorNivel1(380.0f, 500.0f, 40.0f, 40.0f);
}

/**
 * @brief Bucle principal de lógica del nivel.
 */
void Nivel_1::actualizar(float deltaTiempo)
{
    switch (estadoActual) {
    case Estado::CUENTA_REGRESIVA:
        actualizarCuentaRegresiva(deltaTiempo);
        break;
    case Estado::JUGANDO:
        actualizarJugando(deltaTiempo);
        break;
    case Estado::VICTORIA:
    case Estado::DERROTA:
        // No se hace nada aquí.
        break;
    }
}

/**
 * @brief Lógica de la cuenta regresiva.
 */
void Nivel_1::actualizarCuentaRegresiva(float deltaTiempo)
{
    tiempoCuentaRegresiva -= deltaTiempo;
    if (tiempoCuentaRegresiva <= 0.0f) {
        estadoActual = Estado::JUGANDO;
    }
}

/**
 * @brief Lógica principal de juego.
 */
void Nivel_1::actualizarJugando(float deltaTiempo)
{
    if (jugador) jugador->actualizar(deltaTiempo);

    for (Obstaculo* obs : obstaculos) {
        float nuevaVelocidadY = obs->getVelocidadY() + (aceleracionGlobal * deltaTiempo);
        obs->setVelocidadY(nuevaVelocidadY);
        obs->actualizar(deltaTiempo);
    }

    aceleracionGlobal += 0.5f * deltaTiempo;

    generarObstaculos(deltaTiempo);

    revisarColisiones();

    tiempoRestante -= deltaTiempo;
    if (tiempoRestante <= 0.0f) {
        tiempoRestante = 0.0f;
        estadoActual = Estado::VICTORIA;
    }
}

/**
 * @brief Genera obstáculos aleatorios.
 */
void Nivel_1::generarObstaculos(float deltaTiempo)
{
    tiempoParaSiguienteObstaculo -= deltaTiempo;
    if (tiempoParaSiguienteObstaculo <= 0) {
        float posXAleatoria = 225 + static_cast<float>(rand() % 350);
        TipoObstaculo tipo = static_cast<TipoObstaculo>(rand() % 3);
        bool esSinusoidal = (rand() % 2 == 0);

        // 1. Crear el nuevo obstáculo y guardarlo en la variable 'nuevoObs'.
        Obstaculo* nuevoObs = new Obstaculo(posXAleatoria, -60.0f, tipo, esSinusoidal);

        // 2. Ahora que 'nuevoObs' existe, podemos usarlo para asignarle una velocidad inicial.
        nuevoObs->setVelocidadY(150.0f);

        // 3. Finalmente, lo añadimos al vector de obstáculos.
        obstaculos.push_back(nuevoObs);

        // Reiniciar el temporizador para el siguiente obstáculo.
        tiempoParaSiguienteObstaculo = INTERVALO_GENERACION_OBSTACULO;
    }
}
/**
 * @brief Comprueba colisiones.
 */
void Nivel_1::revisarColisiones()
{
    if (!jugador) return;

    for (Obstaculo* obs : obstaculos) {
        if (jugador->getBoundingRect().intersects(obs->getBoundingRect())) {
            // AÑADE ESTA LÍNEA DE DEBUG
            qDebug() << "Colision detectada! Estado de Nivel_1 cambiando a DERROTA.";

            estadoActual = Estado::DERROTA;
            return;
        }
    }
}
/**
 * @brief Dibuja todos los elementos en pantalla.
 */
void Nivel_1::dibujar(QPainter* painter, const QRectF& ventanaRect, const std::map<std::string, QPixmap>& sprites)
{
    // --- DIBUJAR EL FONDO ---
    auto itFondo = sprites.find("fondo_nivel1");
    if (itFondo != sprites.end()) {
        const QPixmap& fondo = itFondo->second;
        painter->drawPixmap(ventanaRect, fondo, fondo.rect());
    }

    // --- DIBUJAR AL JUGADOR ---
    if (jugador) {
        std::string claveSpriteJugador;
        switch (personajeElegido) {
        case PersonajeSeleccionado::GOKU:   claveSpriteJugador = "goku"; break;
        case PersonajeSeleccionado::KRILIN: claveSpriteJugador = "krilin"; break;
        case PersonajeSeleccionado::YAMCHA: claveSpriteJugador = "yamcha"; break;
        }

        auto itJugador = sprites.find(claveSpriteJugador);
        if (itJugador != sprites.end()) {
            const QPixmap& spriteJugador = itJugador->second;
            painter->drawPixmap(jugador->getBoundingRect(), spriteJugador, spriteJugador.rect());
        }
    }

    // --- DIBUJAR OBSTÁCULOS ---
    for (const auto& obs : obstaculos) {
        std::string claveSpriteObs;
        switch (obs->getTipo()) {
        case TipoObstaculo::VEHICULO: claveSpriteObs = "obstaculo_coche"; break;
        case TipoObstaculo::PAJARO:   claveSpriteObs = "obstaculo_pajaro"; break;
        case TipoObstaculo::CAPSULA:  claveSpriteObs = "obstaculo_dron";  break;
        }

        auto itObs = sprites.find(claveSpriteObs);
        if (itObs != sprites.end()) {
            const QPixmap& spriteObs = itObs->second;
            painter->drawPixmap(obs->getBoundingRect(), spriteObs, spriteObs.rect());
        }
    }

    // --- DIBUJAR LA INTERFAZ (UI) ---
    painter->setPen(Qt::white);
    painter->setFont(QFont("Arial", 24, QFont::Bold));
    QString textoTiempo = QString("Tiempo: %1").arg(static_cast<int>(tiempoRestante));
    painter->drawText(20, 40, textoTiempo);

    if (estadoActual == Estado::CUENTA_REGRESIVA) {
        painter->setFont(QFont("Arial", 72, QFont::Bold));
        int num = static_cast<int>(ceil(tiempoCuentaRegresiva));
        painter->drawText(ventanaRect, Qt::AlignCenter, QString::number(num));
    }
}

void Nivel_1::recibirInput(const QSet<int>& teclas)
{
    Q_UNUSED(teclas); // No se usa en este nivel.
}
// --- Métodos de la interfaz Nivel ---
bool Nivel_1::estaTerminado() const
{
    return estadoActual == Estado::VICTORIA || estadoActual == Estado::DERROTA;
}
Nivel_1::Estado Nivel_1::getEstadoNivel() const {
    return estadoActual;
}
void Nivel_1::procesarInput(QKeyEvent* evento)
{
    if (jugador && estadoActual == Estado::JUGANDO) {
        jugador->procesarTeclaPresionada(evento);
    }
}

void Nivel_1::procesarInputLiberado(QKeyEvent* evento)
{
    if (jugador && estadoActual == Estado::JUGANDO) {
        jugador->procesarTeclaLiberada(evento);
    }
}
