#include "sesion.h"

#include <QApplication>

int main(int argc, char *argv[])
{
    QApplication a(argc, argv);
    a.setWindowIcon(QIcon(":/Imagenes/pelota.png"));
    Sesion w;
    w.show();
    return a.exec();
}
