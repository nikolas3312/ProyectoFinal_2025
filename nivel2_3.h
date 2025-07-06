#ifndef NIVEL2_3_H
#define NIVEL2_3_H

#include "personajejugador.h"
#include "Nivel.h"
#include "enemigo.h"
#include "hitbox.h"
#include <vector>
#include <QPainter>
#include <Qset>


class Nivel2_3 : public Nivel {
private:
    enum class Estado {
        CUENTA_REGRESIVA,
        JUGANDO,
        VICTORIA,
        DERROTA
    };

    Estado estadoActual;
    PersonajeSeleccionado personajeElegido;

    PersonajeJugador* jugador;
    Enemigo* enemigo;
    std::vector<Hitbox*> hitboxesActivas;
    float tiempoCuentaRegresiva;
    int numeroNivel; // esta es para saber si es contra ten shin han o piccolo

    void actualizarCuentaRegresiva(float deltaTiempo);
    void actualizarCombate(float deltaTiempo, const Qset<int>& teclas);
    void revisarColisiones();
    void limpiarHitboxes();


public:
    Nivel2_3(personajeSeleccionado personaje, int numeroNivel);
    ~Nivel2_3();

    void iniciaizar() override;
    void actualizar(float deltaTiempo) override;
    void dibujar(QPainter* painter) override;
    bool estaTerminado() const override;


    void recibirInput(const Qset<int>& teclas);

private:
    Qset<int> teclasPresionadas;

};

#endif // NIVEL2_3_H
