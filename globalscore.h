#ifndef GLOBALSCORE_H
#define GLOBALSCORE_H

#include <QMainWindow>
#include <QSqlQuery>

namespace Ui {
class GlobalScore;
}

class GlobalScore : public QMainWindow
{
    Q_OBJECT

public:
    explicit GlobalScore(QWidget *parent = nullptr);
    GlobalScore(QString nombre);
    ~GlobalScore();

private slots:
    void on_cargar_clicked();

    void on_volver_clicked();

    void on_Eliminar_clicked();

    void on_SALIR_clicked();

private:
    Ui::GlobalScore *ui;
    int idt;
    QString name;
};

#endif // GLOBALSCORE_H
