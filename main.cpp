#include "sesion.h"

#include <QApplication>

int main(int argc, char *argv[])
{
    QApplication a(argc, argv);
    Sesion w;
    w.show();
    return a.exec();
}
