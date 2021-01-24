#ifndef SESION_H
#define SESION_H

#include <QMainWindow>
#include <QDebug>

namespace Ui {
class sesion;
}

class sesion : public QMainWindow
{
    Q_OBJECT

public:
    explicit sesion(QWidget *parent = nullptr);
    explicit sesion(float puntaje,float tiempo,float nivel);
    //sesion(float puntaje,float tiempo);
    ~sesion();

private slots:
    void on_pushButton_clicked();

private:
    Ui::sesion *ui;
    float score;
    float time;
    float level;
};

#endif // SESION_H
