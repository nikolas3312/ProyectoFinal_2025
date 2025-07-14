#include "Juego.h"

// Se incluyen las cabeceras de los objetos que esta clase debe conocer.
#include "Nivel_1.h"
#include "Nivel2_3.h"
#include <QPixmap>
#include <QTimer>
#include <QKeyEvent>
#include <QMainWindow>
#include <QPainter>
#include <stdexcept>// Para std::runtime_error
#include <QDebug>

// --- Constantes de configuración del Juego ---
// Tiempo de actualización del bucle principal en milisegundos (aprox. 60 FPS).
constexpr int INTERVALO_ACTUALIZACION = 16;

/**
 * @brief Constructor de la clase Juego.
 * Inicializa el estado, el temporizador y las variables de gestión.
 */
Juego::Juego(QMainWindow* ventana)
    // CORRECCIÓN: La lista ahora sigue el orden de declaración en Juego.h
    : estadoActual(GameState::MENU),
    ventanaPrincipal(ventana),
    gameLoopTimer(new QTimer()),
    nivelActual(nullptr),
    personajeActual(PersonajeSeleccionado::GOKU)
{
    // Conexión de la señal 'timeout' del temporizador con el bucle 'actualizar'.
    // Usamos una expresión lambda para llamar al método de nuestra instancia.
    QObject::connect(gameLoopTimer, &QTimer::timeout, [this]() {
        this->actualizar();
    });
    cargarRecursos();
}
void Juego::cargarRecursos()
{
    // Carga los sprites usando la ruta del archivo de recursos (:/)
    // y los nombres exactos de tus archivos de imagen.

    // --- Fondos ---
    sprites["fondo_nivel1"] = QPixmap(":/Nivel_1/fondoNivel_1.png");

    // --- Personajes Jugables ---
    sprites["goku"]    = QPixmap(":/Nivel_1/goku-removebg-preview.png");
    sprites["krilin"]  = QPixmap(":/Nivel_1/krilin-removebg-preview.png");
    sprites["yamcha"]  = QPixmap(":/Nivel_1/yamcha-removebg-preview.png");
    // Nota: Falta el sprite para Tenshinhan en la lista de archivos.

    // --- Obstáculos ---
    sprites["obstaculo_coche"] = QPixmap(":/Nivel_1/carro-removebg-preview.png");
    sprites["obstaculo_dron"]  = QPixmap(":/Nivel_1/Dron-removebg-preview.png");
    sprites["obstaculo_pajaro"]= QPixmap(":/Nivel_1/pajaro-removebg-preview (1).png");
    // --- Sprites para el Menú de Selección ---
    sprites["portada_goku"]   = QPixmap(":/Nivel_1/portadaGoku.png");
    sprites["portada_krilin"] = QPixmap(":/Nivel_1/portadaKrilin.png");
    sprites["portada_yamcha"] = QPixmap(":/Nivel_1/portadaYamcha.png");
    // --- AÑADE ESTA LÍNEA PARA EL FONDO DEL NIVEL 2/3 ---
    sprites["fondo_torneo"] = QPixmap(":/images/Images/Fondo_torneo.jpeg");
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
// En Juego.cpp

void Juego::procesarInput(QKeyEvent* evento)
{
    teclasPresionadas.insert(evento->key());
    if (estadoActual == GameState::JUGANDO && nivelActual != nullptr) {
        nivelActual->procesarInput(evento);
    }
}

// --- AÑADE ESTA NUEVA FUNCIÓN ---
void Juego::procesarInputLiberado(QKeyEvent* evento)
{
    teclasPresionadas.remove(evento->key());
    if (estadoActual == GameState::JUGANDO && nivelActual != nullptr) {
        nivelActual->procesarInputLiberado(evento);
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
        nivelActual->recibirInput(teclasPresionadas);
        nivelActual->actualizar(deltaTiempo);

        // Comprueba si el nivel ha terminado.
        if (nivelActual->estaTerminado()) {
            // AÑADE ESTE PRIMER DEBUG
            qDebug() << "Juego ha detectado que el nivel ha terminado.";

            Nivel_1* nivel1 = dynamic_cast<Nivel_1*>(nivelActual);
            if (nivel1 && nivel1->getEstadoNivel() == Nivel_1::Estado::DERROTA) {
                // AÑADE ESTE SEGUNDO DEBUG
                qDebug() << "El nivel termino por DERROTA. Cambiando estado de Juego a DERROTA.";
                this->estadoActual = GameState::DERROTA;
            } else {
                // Si es victoria, cambia al siguiente nivel
                cambiarNivel(2);
            }
        }
    }

    // Forza a la ventana a redibujarse para mostrar los cambios.
    ventanaPrincipal->update();
}

/**
 * @brief Dibuja la escena actual dependiendo del estado del juego.
 * @param painter Puntero al QPainter que se usará para dibujar.
 * @param ventanaRect El rectángulo de la ventana, para cálculos de UI.
 */
void Juego::dibujar(QPainter* painter, const QRectF& ventanaRect, const std::map<std::string, QPixmap>& sprites)
{
    if (painter == nullptr) return;

    switch (estadoActual) {
    case GameState::MENU:
        // TODO: Dibujar la pantalla del menú principal usando los sprites.
        // Ejemplo: painter->drawPixmap(0, 0, sprites.at("portada_goku"));
        break;
    case GameState::JUGANDO:
        if (nivelActual != nullptr) {
            // CAMBIO 2: Pasar el mapa de sprites al método dibujar del nivel.
            nivelActual->dibujar(painter, ventanaRect, sprites);
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
        nivelActual = new Nivel2_3(personajeActual, 2);
        break;
    case 3:
        nivelActual = new Nivel2_3(personajeActual, 3);
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
const std::map<std::string, QPixmap>& Juego::getSprites() const {
    return sprites;
}
Juego::GameState Juego::getEstado() const {
    return estadoActual;
}
PersonajeSeleccionado Juego::getPersonajeActual() const {
    return personajeActual;
}

