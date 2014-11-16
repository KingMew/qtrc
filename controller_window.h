#ifndef CONTROLLER_WINDOW_H
#define CONTROLLER_WINDOW_H

#include <QMainWindow>
#include <QTimer>
#include <global.h>

namespace Ui {
class controller_window;
}

class controller_window : public QMainWindow
{
    Q_OBJECT

public:
    explicit controller_window(QWidget *parent = 0);
    ~controller_window();

public slots:
    void StartRC();
    void ToggleStops();
    void ShowRC();
    void Shutdown();
    void AddPhase();

private:
    Ui::controller_window *ui;
    QTimer* timer;
    QTimer* stoptimer;
    QTimer* phasetimer;
    int min, max, stophours, phase;
    RC_POSITION_MODE positionMode;
    bool phaseD;

    void getPositionMode();
    void moveToCenter();
};

#endif // CONTROLLER_WINDOW_H
