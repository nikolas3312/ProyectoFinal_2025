#include "luchador.h"
#include <QtMath>
#include <QUrl>

Luchador::Luchador(float x, float y, float ancho, float alto)
    : Entidad(x, y, ancho, alto),
    vida(100.0f), dañoBase(10.0f),
    estaAtacando(false), tipoAtaque(TipoAtaque::Ninguno),tiempoAtaque(0.0f), cooldownAtaque(0.0f),
    velocidadSalto(-500.0f), enSuelo(true), direccion(1)
{

    // Golpe recibido
    playerGolpeRecibido = new QMediaPlayer();
    audioOutputGolpe = new QAudioOutput();
    playerGolpeRecibido->setAudioOutput(audioOutputGolpe);
    playerGolpeRecibido->setSource(QUrl("qrc:/Sonidos/Golpe.mp3"));
    audioOutputGolpe->setVolume(0.6f);

    // Puño
    playerPuño = new QMediaPlayer();
    audioOutputPuño = new QAudioOutput();
    playerPuño->setAudioOutput(audioOutputPuño);
    playerPuño->setSource(QUrl("qrc:/Sonidos/Puno.mp3"));
    audioOutputPuño->setVolume(0.6f);

    // Patada
    playerPatada = new QMediaPlayer();
    audioOutputPatada = new QAudioOutput();
    playerPatada->setAudioOutput(audioOutputPatada);
    playerPatada->setSource(QUrl("qrc:/Sonidos/Patada.mp3"));
    audioOutputPatada->setVolume(0.6f);

    // Salto
    playerSalto = new QMediaPlayer();
    audioOutputSalto = new QAudioOutput();
    playerSalto->setAudioOutput(audioOutputSalto);
    playerSalto->setSource(QUrl("qrc:/Sonidos/Salto.mp3"));
    audioOutputSalto->setVolume(0.6f);

}

Luchador::~Luchador() {
    delete playerGolpeRecibido;
    delete audioOutputGolpe;

    delete playerPuño;
    delete audioOutputPuño;

    delete playerPatada;
    delete audioOutputPatada;

    delete playerSalto;
    delete audioOutputSalto;

}
void Luchador::recibirDaño(float daño) {
    if (enDefensa) {
        daño *= 0.3f; //Esto es para que reciba solo el 30% del daño
    }
    vida -= daño;
    if (vida < 0) vida = 0;

    tiempoDaño = 0.4f; //0.4 segundos de parpadeo
    if (direccion == 1)
        posX -= 20;
    else
        posX += 20;

    if (posX < 0) posX = 0;
    if (posX > 800 - ancho) posX = 800 - ancho;

    playerGolpeRecibido->stop();
    playerGolpeRecibido->play();

}

bool Luchador::estaVivo() const {
    return vida > 0;
}

void Luchador::saltar() {
    if (estaEnElSuelo()) {
        velocidadY = velocidadSalto;
        enSuelo = false;

        playerSalto->stop();
        playerSalto->play();
    }
}

void Luchador::actualizar(float deltaTiempo) {
    aplicarGravedad(deltaTiempo);
    posX += velocidadX * deltaTiempo;
    posY += velocidadY * deltaTiempo;

    if(tiempoDaño > 0)
        tiempoDaño -= deltaTiempo;

    if (tiempoAtaque > 0) {
        tiempoAtaque -= deltaTiempo;
    }

        if (tiempoAtaque <= 0) {
            estaAtacando = false;
            tipoAtaque = TipoAtaque::Ninguno;
        }

    if (posY >= 400) { // piso imaginario
        posY = 400;
        velocidadY = 0;
        enSuelo = true;

    if (cooldownAtaque > 0) {
        cooldownAtaque -= deltaTiempo;
        if (cooldownAtaque < 0) cooldownAtaque = 0;
    }
}
}


void Luchador::aplicarGravedad(float deltaTiempo) {
    if (!estaEnElSuelo()) {
        velocidadY += 980 * deltaTiempo; // gravedad aproximada
    }
}

bool Luchador::estaEnElSuelo() const {
    return enSuelo;
}
