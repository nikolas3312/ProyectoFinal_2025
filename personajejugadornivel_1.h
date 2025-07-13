#pragma once

#include "Entidad.h"

class QKeyEvent; // Declaración adelantada, es más eficiente que incluir la cabecera completa.

/**
 * @class PersonajeJugadorNivel1
 * @brief Representa al personaje del jugador específicamente para el Nivel 1.
 *
 * Su comportamiento está simplificado para un juego de esquivar: solo se mueve
 * horizontalmente y no es afectado por la gravedad.
 */
class PersonajeJugadorNivel1 : public Entidad {
public:
    /**
     * @brief Constructor.
     * @param x Posición inicial en X.
     * @param y Posición inicial en Y.
     * @param ancho Ancho del personaje.
     * @param alto Alto del personaje.
     */
    PersonajeJugadorNivel1(float x, float y, float ancho, float alto);

    // Destructor.
    ~PersonajeJugadorNivel1();

    // --- Métodos heredados de Entidad ---
    void actualizar(float deltaTiempo) override;

    // --- Métodos de Control ---
    /**
     * @brief Procesa un evento de tecla presionada para iniciar el movimiento.
     * @param evento El evento de teclado de Qt.
     */
    void procesarTeclaPresionada(QKeyEvent* evento);

    /**
     * @brief Procesa un evento de tecla liberada para detener el movimiento.
     * @param evento El evento de teclado de Qt.
     */
    void procesarTeclaLiberada(QKeyEvent* evento);
};
