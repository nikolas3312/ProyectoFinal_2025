#ifndef PERSONAJEJUGADOR_H
#define PERSONAJEJUGADOR_H

#include "luchador.h"
#include <QSet>

class PersonajeJugador : public Luchador
{
public:
    PersonajeJugador(float x, float y, float ancho, float alto);

    void procesarInput(const QSet<int>& teclas);
    void atacar() override;
};

#endif // PERSONAJEJUGADOR_H
