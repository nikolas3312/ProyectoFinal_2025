#ifndef PERSONAJEJUGADOR_H
#define PERSONAJEJUGADOR_H

#include "luchador.h"
#include <QSet>
/**
 * @class PersonajeJugador
 * @brief Clase que representa al personaje controlado por el jugador.
 */
class PersonajeJugador : public Luchador
{
public:
    PersonajeJugador(float x, float y, float ancho, float alto);
    ~PersonajeJugador() override {}

    void actualizar(float deltaTiempo) override;
    void dibujar(QPainter* painter) override;
    void procesarInput(const QSet<int>& teclas);
    // Métodos para iniciar diferentes tipos de ataque
    void atacarPuño() override;
    void atacarPatada() override;

};

#endif // PERSONAJEJUGADOR_H
