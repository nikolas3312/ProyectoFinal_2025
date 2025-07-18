#pragma once

#include <QMainWindow>
#include "Juego.h" // Incluimos la cabecera de nuestro gestor de juego.
#include <QPushButton>
/**
 * @class MainWindow
 * @brief La ventana principal de la aplicación que contiene y renderiza el juego.
 */
class MainWindow : public QMainWindow
{
    Q_OBJECT // Macro necesaria para cualquier clase de Qt que use señales o slots.

public:
    // Constructor de la ventana.
    explicit MainWindow(QWidget *parent = nullptr);

    // Destructor.
    ~MainWindow();

protected:
    /**
     * @brief Se ejecuta cada vez que la ventana necesita ser redibujada.
     * @param event Información sobre el evento de pintado.
     */
    void paintEvent(QPaintEvent *event) override;

    /**
     * @brief Se ejecuta cuando se presiona una tecla.
     * @param event Información sobre la tecla presionada.
     */
    void keyPressEvent(QKeyEvent *event) override;

    void keyReleaseEvent(QKeyEvent *event) override;
private:
    void configurarUI(); // <--- AÑADE ESTA LÍNEA
    void ocultarBotonesSeleccion(); // <--- AÑADE ESTA LÍNEA

    // --- AÑADE LA DECLARACIÓN DE LOS BOTONES ---
    QPushButton* gokuButton;
    QPushButton* krilinButton;
    QPushButton* yamchaButton;
    QPushButton* retryButton;
    // Puntero a la instancia principal de la lógica del juego.
    Juego* juego;
};
