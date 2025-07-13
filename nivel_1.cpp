#include "Nivel_1.h"
#include <cstdlib> // Para rand()
#include <ctime>   // Para srand()

// --- Constantes de configuración del Nivel ---
constexpr float TIEMPO_A_SOBREVIVIR = 60.0f;
constexpr float TIEMPO_INICIAL_CUENTA_REGRESIVA = 3.0f;
constexpr float INTERVALO_GENERACION_OBSTACULO = 0.5f;

/**
 * @brief Constructor. Inicializa el estado y guarda el personaje elegido.
 */
Nivel_1::Nivel_1(PersonajeSeleccionado personaje)
    : estadoActual(Estado::CUENTA_REGRESIVA),
    personajeElegido(personaje),
    jugador(nullptr), // Se inicializa en inicializar()
    tiempoObjetivo(TIEMPO_A_SOBREVIVIR),
    tiempoRestante(TIEMPO_A_SOBREVIVIR),
    aceleracionGlobal(0.1f),
    tiempoParaSiguienteObstaculo(0.0f),
    tiempoCuentaRegresiva(TIEMPO_INICIAL_CUENTA_REGRESIVA)
{
    // Inicializa la semilla del generador de números aleatorios.
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
    // Crea al jugador en el centro de la parte inferior de la pantalla.
    // El sprite a usar se basará en 'personajeElegido'.
    jugador = new PersonajeJugador(380.0f, 500.0f, 40.0f, 40.0f);

    // Setea el fondo (esto se haría en la clase 'Juego' o en el gestor de renderizado)
    // setFondo(":/sprites/fondo_ciudad.png");
}

/**
 * @brief Bucle principal de lógica del nivel, gestionado por estados.
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
        // No hacer nada, esperar a que la clase Juego cambie de nivel/pantalla.
        break;
    }
}

/**
 * @brief Maneja la lógica de la cuenta regresiva inicial.
 */
void Nivel_1::actualizarCuentaRegresiva(float deltaTiempo)
{
    tiempoCuentaRegresiva -= deltaTiempo;
    if (tiempoCuentaRegresiva <= 0) {
        estadoActual = Estado::JUGANDO;
    }
}

/**
 * @brief Maneja la lógica principal mientras se está jugando.
 */
void Nivel_1::actualizarJugando(float deltaTiempo)
{
    // Actualizar jugador y obstáculos
    jugador->actualizar(deltaTiempo);
    for (Obstaculo* obs : obstaculos) {
        // Calcula la nueva velocidad y luego asígnala con el método público.
        float nuevaVelocidadY = obs->getVelocidadY() + (aceleracionGlobal * deltaTiempo);
        obs->setVelocidadY(nuevaVelocidadY);
    }

    // Generar nuevos obstáculos
    generarObstaculos(deltaTiempo);

    // Revisar colisiones
    revisarColisiones(); // Si hay colisión, se llama a reiniciar()

    // Actualizar temporizador de supervivencia
    tiempoRestante -= deltaTiempo;
    if (tiempoRestante <= 0) {
        tiempoRestante = 0;
        estadoActual = Estado::VICTORIA;
    }
}


/**
 * @brief Comprueba si el nivel ha terminado (por victoria o derrota).
 */
bool Nivel_1::estaTerminado() const
{
    return estadoActual == Estado::VICTORIA || estadoActual == Estado::DERROTA;
}

/**
 * @brief Genera nuevos obstáculos de forma aleatoria.
 */
void Nivel_1::generarObstaculos(float deltaTiempo)
{
    tiempoParaSiguienteObstaculo -= deltaTiempo;
    if (tiempoParaSiguienteObstaculo <= 0) {
        // Lógica para crear un obstáculo en una posición X aleatoria
        // y con un tipo (sprite) aleatorio.
        // ...
        // obstaculos.push_back(new Obstaculo(...));

        tiempoParaSiguienteObstaculo = INTERVALO_GENERACION_OBSTACULO;
    }
}

/**
 * @brief Comprueba colisiones entre el jugador y los obstáculos.
 */
void Nivel_1::revisarColisiones()
{
    for (Obstaculo* obs : obstaculos) {
        if (jugador->getBoundingRect().intersects(obs->getBoundingRect())) {
            reiniciar(); // El jugador chocó, se reinicia el nivel.
            return; // Salir del bucle para no procesar más colisiones.
        }
    }
}

/**
 * @brief Reinicia el estado del nivel a sus valores iniciales.
 */
void Nivel_1::reiniciar()
{
    // TODO: Aquí podrías añadir una pantalla de "Retry". Por ahora, reinicia el tiempo.
    // La pantalla de Game Over tras X intentos la manejaría la clase 'Juego'.
    tiempoRestante = tiempoObjetivo;

    // Opcional: limpiar todos los obstáculos de la pantalla.
    for (Obstaculo* obs : obstaculos) {
        delete obs;
    }
    obstaculos.clear();
}


/**
 * @brief Dibuja todos los elementos en pantalla.
 */
void Nivel_1::dibujar(QPainter* painter, const QRectF& ventanaRect, const std::map<std::string, QPixmap>& sprites)
{
    // Dibujar el fondo (gestionado por una clase superior)
    // ...

    // Dibujar jugador y obstáculos
    jugador->dibujar(painter);
    for (const auto& obs : obstaculos) {
        obs->dibujar(painter); // Aquí se usaría el getTipo() para elegir el sprite.
    }

    // --- DIBUJAR LA INTERFAZ (UI) ---
    // Configurar la fuente y el color para el texto
    painter->setPen(Qt::white);
    painter->setFont(QFont("Arial", 24, QFont::Bold));

    // Dibujar el temporizador principal
    QString textoTiempo = QString("Tiempo: %1").arg(static_cast<int>(tiempoRestante));
    painter->drawText(20, 40, textoTiempo);

    // Dibujar la cuenta regresiva si está activa
    if (estadoActual == Estado::CUENTA_REGRESIVA) {
        painter->setFont(QFont("Arial", 72, QFont::Bold));
        int num = static_cast<int>(ceil(tiempoCuentaRegresiva));
        painter->drawText(ventanaRect, QString::number(num)); // Centrar el texto
    }
}

void Nivel_1::recibirInput(const QSet<int>& /*teclas*/)
{
    // No se usa en este nivel
}
