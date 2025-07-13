#ifndef NIVEL2_3_H
#define NIVEL2_3_H

#include "personajejugador.h"
#include "Nivel.h"
#include "nivel_1.h"
#include "enemigo.h"
#include "hitbox.h"
#include <vector>
#include <QPainter>
#include <QSet>
#include <QPixmap>


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
    void actualizarCombate(float deltaTiempo, const QSet<int>& teclas);
    void revisarColisiones();
    void limpiarHitboxes();

    QSet<int> teclasPresionadas;
    QPixmap fondoEscenario;

public:
    Nivel2_3(PersonajeSeleccionado personaje, int numeroNivel);
    ~Nivel2_3();

    void inicializar() override;
    void actualizar(float deltaTiempo) override;
    void dibujar(QPainter* painter, const QRectF& ventanaRect, const std::map<std::string, QPixmap>& sprites) override;
    bool estaTerminado() const override;


    void recibirInput(const QSet<int>& teclas);

};

#endif // NIVEL2_3_H
