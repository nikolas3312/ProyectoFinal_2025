#ifndef HITBOX_H
#define HITBOX_H

#include <QRectF>

class Hitbox
{
public:
    QRectF rect;
    float daño;
    float duracion;
    float tiempoActual;

    Hitbox(const QRectF& r, float d, float dur);

    bool estaActiva() const;
    void actualizar(float deltaTiempo);
};

#endif // HITBOX_H
