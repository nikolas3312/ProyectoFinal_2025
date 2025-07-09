#include "mainwindow.h" // Asegúrate de que el nombre coincida
#include <QApplication>

int main(int argc, char *argv[])
{
    // Crea la aplicación de Qt.
    QApplication a(argc, argv);

    // Crea una instancia de nuestra ventana principal.
    MainWindow w;

    // Muestra la ventana.
    w.show();

    // Inicia el bucle de eventos de la aplicación.
    return a.exec();
}
