#ifndef ENEMIGO_H
#define ENEMIGO_H

#include "luchador.h"

enum class EstadoIA { Esperar, Atacar, Defender };

class Enemigo : public Luchador
{
private:
    EstadoIA estadoIA;
    float temporizadorEstado;

public:
    Enemigo(float x, float y, float ancho, float alto);

    void actualizar(float deltaTiempo) override;
    void atacarPuño() override;
    void atacarPatada() override;


private:
    void decidirAccion();
};

#endif // ENEMIGO_H
