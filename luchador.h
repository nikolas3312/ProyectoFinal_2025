#ifndef LUCHADOR_H
#define LUCHADOR_H

#include "entidad.h"

class Luchador : public Entidad
{
protected:
    float vida;
    float dañoBase;
    bool estaAtacando;
    float cooldownAtaque;
    float velocidadSalto;
    bool enSuelo;

public:
    Luchador(float x, float y, float ancho, float alto);
    virtual ~Luchador() {}

    virtual void recibirDaño(float daño);
    virtual bool estaVivo() const;
    virtual void saltar();
    virtual void actualizar(float deltaTiempo) override;
    virtual void atacar() = 0; // Pure virtual, se define en hijos
    float getDañoBase() const { return dañoBase; }
    bool getEstaAtacando() const { return estaAtacando; }
    void setEstaAtacando(bool valor) { estaAtacando = valor; }

protected:
    void aplicarGravedad(float deltaTiempo);
    bool estaEnElSuelo() const;
};

#endif // LUCHADOR_H
