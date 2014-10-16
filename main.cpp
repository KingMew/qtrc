#include "mainwindow.h"
#include "controller_window.h"
#include <QApplication>
#include <QTimer>
#include <cstdio>

int main(int argc, char *argv[])
{
    QApplication a(argc, argv);
    controller_window w;
    w.show();
    return a.exec();
}
