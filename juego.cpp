#include "Juego.h"

// Se incluyen las cabeceras de los objetos que esta clase debe conocer.
#include "Nivel_1.h"
#include "Nivel2_3.h"

#include <QTimer>
#include <QKeyEvent>
#include <QMainWindow>
#include <stdexcept> // Para std::runtime_error

// --- Constantes de configuración del Juego ---
// Tiempo de actualización del bucle principal en milisegundos (aprox. 60 FPS).
constexpr int INTERVALO_ACTUALIZACION = 16;

/**
 * @brief Constructor de la clase Juego.
 * Inicializa el estado, el temporizador y las variables de gestión.
 */
Juego::Juego(QMainWindow* ventana)
    : estadoActual(GameState::MENU),
    nivelActual(nullptr),
    ventanaPrincipal(ventana),
    gameLoopTimer(new QTimer()),
    personajeActual(PersonajeSeleccionado::GOKU) // Valor por defecto
{
    // Conexión de la señal 'timeout' del temporizador con el bucle 'actualizar'.
    // Usamos una expresión lambda para llamar al método de nuestra instancia.
    QObject::connect(gameLoopTimer, &QTimer::timeout, [this]() {
        this->actualizar();
    });
}

/**
 * @brief Destructor. Libera la memoria del nivel actual y del temporizador.
 */
Juego::~Juego()
{
    delete nivelActual;
    delete gameLoopTimer;
}

/**
 * @brief Inicia el bucle principal del juego.
 */
void Juego::iniciar()
{
    gameLoopTimer->start(INTERVALO_ACTUALIZACION);
}

/**
 * @brief Inicia una nueva partida, comenzando por el primer nivel.
 * @param personaje El personaje seleccionado por el jugador.
 */
void Juego::iniciarNuevaPartida(PersonajeSeleccionado personaje)
{
    this->personajeActual = personaje;
    cambiarNivel(1);
}

/**
 * @brief Procesa la entrada de teclado y la delega al nivel actual si es pertinente.
 */
void Juego::procesarInput(QKeyEvent* evento)
{
    if (estadoActual == GameState::JUGANDO && nivelActual != nullptr) {
        // TODO: Delegar el evento al nivel o al jugador para que lo procese.
        // Por ejemplo: nivelActual->procesarInput(evento);
    }
}

/**
 * @brief Bucle principal de actualización, llamado 60 veces por segundo por el QTimer.
 */
void Juego::actualizar()
{
    // La lógica de actualización depende del estado actual del juego.
    if (estadoActual == GameState::JUGANDO && nivelActual != nullptr) {
        // Calcula el tiempo delta en segundos.
        float deltaTiempo = static_cast<float>(INTERVALO_ACTUALIZACION) / 1000.0f;

        nivelActual->actualizar(deltaTiempo);

        // Comprueba si el nivel ha terminado.
        if (nivelActual->estaTerminado()) {
            // TODO: Determinar si es victoria o derrota y cambiar de estado/nivel.
            // Por ahora, cambiamos al nivel 2 como ejemplo.
            cambiarNivel(2);
        }
    }

    // Forza a la ventana a redibujarse para mostrar los cambios.
    ventanaPrincipal->update();
}

/**
 * @brief Dibuja la escena actual dependiendo del estado del juego.
 */
void Juego::dibujar(QPainter* painter)
{
    if (painter == nullptr) return;

    switch (estadoActual) {
    case GameState::MENU:
        // TODO: Dibujar la pantalla del menú principal.
        break;
    case GameState::JUGANDO:
        if (nivelActual != nullptr) {
            nivelActual->dibujar(painter);
        }
        break;
    case GameState::VICTORIA:
        // TODO: Dibujar la pantalla de victoria.
        break;
    case GameState::DERROTA:
        // TODO: Dibujar la pantalla de derrota.
        break;
    }
}

/**
 * @brief Destruye el nivel actual y crea una nueva instancia del nivel solicitado.
 */
void Juego::cambiarNivel(int numeroNivel)
{
    // Liberar memoria del nivel anterior si existe.
    delete nivelActual;
    nivelActual = nullptr;

    switch (numeroNivel) {
    case 1:
        nivelActual = new Nivel_1(personajeActual);
        break;
    case 2:
        // TODO: Implementar la creación del Nivel 2.
        // nivelActual = new Nivel_2_3(personajeActual, 2);
        // Por ahora, entramos en un estado de victoria para terminar el flujo.
        estadoActual = GameState::VICTORIA;
        break;
    case 3:
        // TODO: Implementar la creación del Nivel 3.
        break;
    default:
        // Si el nivel no existe, puede ser el fin del juego.
        estadoActual = GameState::VICTORIA; // O mostrar créditos, etc.
        break;
    }

    // Si se creó un nuevo nivel, se inicializa.
    if (nivelActual != nullptr) {
        nivelActual->inicializar();
        estadoActual = GameState::JUGANDO;
    }
}
