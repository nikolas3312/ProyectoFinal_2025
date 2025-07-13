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
    int direccion;
public:
    Luchador(float x, float y, float ancho, float alto);
    virtual ~Luchador() {}

    virtual void recibirDaño(float daño);
    virtual bool estaVivo() const;
    virtual void saltar();
    virtual void actualizar(float deltaTiempo) override;
    virtual void atacarPuño() = 0;
    virtual void atacarPatada() = 0;
    float getDañoBase() const { return dañoBase; }
    bool getEstaAtacando() const { return estaAtacando; }
    void setEstaAtacando(bool valor) { estaAtacando = valor; }
    float getVida() const { return vida; }
    int getDireccion() const { return direccion; }
    void setDireccion(int dir) { direccion = dir; }




protected:
    void aplicarGravedad(float deltaTiempo);
    bool estaEnElSuelo() const;
};

#endif // LUCHADOR_H
