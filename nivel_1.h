#pragma once

#include "Nivel.h"
#include "PersonajeJugador.h"
#include "Obstaculo.h"
#include <vector>

// Enum para saber qué personaje se seleccionó en el menú.
enum class PersonajeSeleccionado {
    GOKU,
    KRILIN,
    YAMCHA,
    TENSHINHAN
};

/**
 * @class Nivel_1
 * @brief Implementación del primer nivel del juego.
 *
 * Gestiona la lógica del nivel de esquivar obstáculos, incluyendo un temporizador
 * de supervivencia, una cuenta regresiva inicial, y la generación aleatoria de obstáculos.
 */
class Nivel_1 : public Nivel {
public:
    /**
     * @brief Constructor del Nivel 1.
     * @param personaje El personaje que el jugador seleccionó en el menú.
     */
    explicit Nivel_1(PersonajeSeleccionado personaje);

    // Destructor.
    ~Nivel_1();

    // --- Implementación de los métodos virtuales de Nivel ---
    void inicializar() override;
    void actualizar(float deltaTiempo) override;
    void dibujar(QPainter* painter, const QRectF& ventanaRect) override;
    bool estaTerminado() const override;

private:
    // --- Métodos de Lógica Interna ---
    void actualizarCuentaRegresiva(float deltaTiempo);
    void actualizarJugando(float deltaTiempo);
    void generarObstaculos(float deltaTiempo);
    void revisarColisiones();
    void reiniciar(); // Reinicia el nivel si el jugador choca.
    void recibirInput(const QSet<int>& teclas) override;


    // Enum para controlar los estados internos del nivel.
    enum class Estado {
        CUENTA_REGRESIVA,
        JUGANDO,
        VICTORIA,
        DERROTA // Aunque la pantalla de Game Over la muestra 'Juego', el nivel sabe que ha perdido.
    };

    // --- Atributos del Nivel ---
    Estado estadoActual;
    PersonajeSeleccionado personajeElegido;
    PersonajeJugador* jugador;
    std::vector<Obstaculo*> obstaculos;

    // Atributos para el temporizador y la dificultad
    float tiempoObjetivo; // Tiempo total que se debe sobrevivir.
    float tiempoRestante; // El contador en reversa.
    float aceleracionGlobal;

    // Atributos para la generación de obstáculos
    float tiempoParaSiguienteObstaculo;

    // Atributos para la cuenta regresiva
    float tiempoCuentaRegresiva;
};
