#pragma once

#include "Nivel.h"
#include "personajejugadornivel_1.h"
#include "Obstaculo.h"
#include "GameTypes.h"
#include <vector>
#include <QKeyEvent>
#include <QPainter>
#include <map>

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

    /// Destructor.
    ~Nivel_1() override;

    // --- Implementación de los métodos virtuales de Nivel ---
    void inicializar() override;
    void actualizar(float deltaTiempo) override;
    void dibujar(QPainter* painter, const QRectF& ventanaRect, const std::map<std::string, QPixmap>& sprites) override;
    bool estaTerminado() const override;
    void recibirInput(const QSet<int>& teclas) override;
    void procesarInput(QKeyEvent* evento) override;
    void procesarInputLiberado(QKeyEvent* evento) override;
    // --- Estado del nivel ---
    enum class Estado {
        CUENTA_REGRESIVA,
        JUGANDO,
        VICTORIA,
        DERROTA
    };
    /**
     * @brief Devuelve el estado actual del nivel.
     */
    Estado getEstadoNivel() const;

private:
    // --- Métodos internos ---
    void actualizarCuentaRegresiva(float deltaTiempo);
    void actualizarJugando(float deltaTiempo);
    void generarObstaculos(float deltaTiempo);
    void revisarColisiones();

    Estado estadoActual;

    // --- Datos del jugador y configuración ---
    PersonajeSeleccionado personajeElegido;
    PersonajeJugadorNivel1* jugador;
    std::vector<Obstaculo*> obstaculos;

    // --- Temporizador y dificultad ---
    float tiempoObjetivo;
    float tiempoRestante;
    float aceleracionGlobal;

    // --- Generación de obstáculos ---
    float tiempoParaSiguienteObstaculo;

    // --- Cuenta regresiva inicial ---
    float tiempoCuentaRegresiva;
};
