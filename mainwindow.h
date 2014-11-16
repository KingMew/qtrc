#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QWidget>
#include <global.h>

#define DEBUG

namespace Ui {
class MainWindow;
}

class MainWindow : public QWidget
{
    Q_OBJECT

public:
    explicit MainWindow(QWidget *parent = 0);
    void ChgGraphic(int phase);
    void setPositionMode(RC_POSITION_MODE m);
    ~MainWindow();

protected:
    void closeEvent(QCloseEvent *);

private:
    Ui::MainWindow *ui;
    RC_POSITION_MODE mode; //Default mode follows cursor
};

#endif // MAINWINDOW_H
