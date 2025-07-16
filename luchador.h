#ifndef LUCHADOR_H
#define LUCHADOR_H

#include "entidad.h"
#include "GameTypes.h"



class Luchador : public Entidad
{
protected:
    float vida;
    float dañoBase;
    bool estaAtacando;
    TipoAtaque tipoAtaque;
    float tiempoAtaque;
    float cooldownAtaque;
    float velocidadSalto;
    bool enSuelo;
    int direccion;
    bool enDefensa;
    float tiempoDaño;


public:
    Luchador(float x, float y, float ancho, float alto);
    virtual ~Luchador();

    virtual void recibirDaño(float daño);
    virtual bool estaVivo() const;
    virtual void saltar();
    virtual void actualizar(float deltaTiempo) override;
    virtual void atacarPuño() = 0;
    virtual void atacarPatada() = 0;
    float getDañoBase() const { return dañoBase; }
    bool getEstaAtacando() const { return estaAtacando; }
    TipoAtaque getTipoAtaque() const { return tipoAtaque; }
    void setEstaAtacando(bool valor) { estaAtacando = valor; }
    float getVida() const { return vida; }
    int getDireccion() const { return direccion; }
    void setDireccion(int dir) { direccion = dir; }
    void setDefensa(bool estado) { enDefensa = estado; }
    bool getEnDefensa() const { return enDefensa; }
    float getTiempoDanio() const { return tiempoDaño; }
    void setVida(float nuevaVida) { vida = nuevaVida; }
    void setCooldownAtaque(float cd) { cooldownAtaque = cd; }





protected:
    void aplicarGravedad(float deltaTiempo);
    bool estaEnElSuelo() const;
};

#endif // LUCHADOR_H
