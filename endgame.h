#ifndef ENDGAME_H
#define ENDGAME_H

#include <QMainWindow>

namespace Ui {
class EndGame;
}

class EndGame : public QMainWindow
{
    Q_OBJECT

public:
    explicit EndGame(QWidget *parent = nullptr);
    ~EndGame();

private slots:
    void on_regButton_clicked();

    void on_loginButton_clicked();

private:
    Ui::EndGame *ui;
};

#endif // ENDGAME_H
