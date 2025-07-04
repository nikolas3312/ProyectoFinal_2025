#ifndef NIVEL2_3_H
#define NIVEL2_3_H

#include "personajejugador.h"
#include "enemigo.h"
#include "hitbox.h"
#include <vector>
#include <QPainter>

enum class EstadoJuego { Jugando, Ganado, Perdido };

class Nivel2_3
{
private:
    PersonajeJugador* jugador;
    Enemigo* enemigo;
    std::vector<Hitbox*> hitboxesActivas;
    EstadoJuego estado;

public:
    Nivel2_3();
    ~Nivel2_3();

    void actualizar(float deltaTiempo, const QSet<int>& teclas);
    void dibujar(QPainter* painter);
    EstadoJuego getEstadoJuego() const;

private:
    void revisarColisiones();
    void limpiarHitboxes();
};

#endif // NIVEL2_3_H
