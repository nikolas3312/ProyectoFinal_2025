#pragma once

// Se usan declaraciones adelantadas (forward declarations) para evitar incluir
// cabeceras completas de Qt en este archivo, reduciendo tiempos de compilación.
class QMainWindow;
class QTimer;
class QPainter;
class QKeyEvent;
#include <QSet>


// Incluimos las definiciones de nuestras clases de lógica.
#include "Nivel.h"
#include "GameTypes.h"
#include "nivel2_3.h"
#include <QPixmap>
/**
 * @class Juego
 * @brief Clase principal que gestiona el flujo y la lógica general del juego.
 *
 * Actúa como el motor principal, controlando el estado del juego (menú, jugando, etc.),
 * la creación y destrucción de niveles, y sirviendo de puente entre la
 * interfaz de usuario de Qt y la capa de lógica del juego.
 */
class Juego {
public:
    /**
     * @brief Constructor de la clase Juego.
     * @param ventana Puntero a la QMainWindow principal que contendrá el juego.
     */
    explicit Juego(QMainWindow* ventana);

    // Destructor. Se encarga de liberar la memoria del nivel actual y el timer.
    ~Juego();

    /**
     * @brief Inicia el bucle principal del juego.
     */
    void iniciar();

    /**
     * @brief Procesa los eventos de teclado recibidos desde la ventana principal.
     * @param evento El evento de teclado que se ha producido.
     */
    void procesarInput(QKeyEvent* evento);

    /**
     * @brief Dibuja la escena actual del juego.
     * @param painter Puntero al QPainter que se usará para dibujar.
     */
    void dibujar(QPainter* painter, const QRectF& ventanaRect, const std::map<std::string, QPixmap>& sprites);

    // --- Métodos para ser llamados desde la UI (ej. botones del menú) ---

    /**
     * @brief Inicia un nuevo juego con el personaje seleccionado.
     * @param personaje El personaje elegido por el jugador en el menú.
     */
    void iniciarNuevaPartida(PersonajeSeleccionado personaje);
    /**
     * @brief Cambia el nivel actual del juego.
     * @param numeroNivel El identificador del nuevo nivel a cargar.
     */
    void cambiarNivel(int numeroNivel);
    void soltarTecla(QKeyEvent* evento);
    const std::map<std::string, QPixmap>& getSprites() const;
    void procesarInputLiberado(QKeyEvent* evento);
    // Enum para los estados generales del juego.
    enum class GameState {
        MENU,
        JUGANDO,
        VICTORIA,
        DERROTA
    };
    GameState getEstado() const;
    PersonajeSeleccionado getPersonajeActual() const;
private:
    /**
     * @brief El bucle principal de actualización, llamado por el QTimer.
     */
    void actualizar();
    QSet<int> teclasPresionadas;
    void cargarRecursos();
    std::map<std::string, QPixmap> sprites;
    // --- Atributos de Estado y Gestión ---
    GameState estadoActual;
    QMainWindow* ventanaPrincipal; // Puntero a la ventana para interactuar con ella.
    QTimer* gameLoopTimer;       // El "corazón" que impulsa el juego.
    Nivel* nivelActual;          // Puntero polimórfico al nivel en curso.

    // Almacena la selección del jugador para pasarla al constructor del nivel.
    PersonajeSeleccionado personajeActual;
};
