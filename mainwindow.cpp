#include "mainwindow.h"
#include "ui_mainwindow.h"
#include <QTimer>
#include <QCloseEvent>
#include <QDebug>

MainWindow::MainWindow(QWidget *parent) :
    QWidget(parent),
    ui(new Ui::MainWindow)
{
    ui->setupUi(this);
    //setWindowFlags(windowFlags() | Qt::Tool);
    this->setWindowFlags(Qt::Popup | Qt::FramelessWindowHint);
    this->setStyleSheet("background:transparent;");
    this->setAttribute(Qt::WA_TranslucentBackground, true);
    this->setAttribute(Qt::WA_NoSystemBackground, true);
    this->move(QCursor::pos());
    QTimer *timer = new QTimer(this);
    connect(timer, SIGNAL(timeout()), this, SLOT(close()));
    timer->start(1250);
}

MainWindow::~MainWindow()
{
    delete ui;
}

void MainWindow::closeEvent(QCloseEvent * event)
{
    event->accept();
}

void MainWindow::ChgGraphic(int phase)
{
    if(phase == 0)
    {
        QString filename = ":/rc.png";
        setGeometry(this->geometry().x(), this->geometry().y(), QPixmap(filename).width(), QPixmap(filename).height());
        this->ui->centralWidget->resize(QPixmap(filename).width(),QPixmap(filename).height());
        this->ui->label->setGeometry(0,0,QPixmap(filename).width(),QPixmap(filename).height());
        return;
    }
    else
    {
        if(true)
        {
            QString filename = ":/rc"+QString::number(rand()%std::min(phase,3)+2)+".png";
            qDebug("filename: %s %d %d\n",qPrintable(filename), QPixmap(filename).width(),QPixmap(filename).height() );
            //this->ui->label->setPixmap(QPixmap(filename));
            setGeometry(this->geometry().x(), this->geometry().y(), QPixmap(filename).width(), QPixmap(filename).height());
            this->ui->centralWidget->resize(QPixmap(filename).width(),QPixmap(filename).height());
            this->ui->label->setGeometry(0,0,QPixmap(filename).width(),QPixmap(filename).height());
            this->ui->label->setPixmap(QPixmap(filename));
        }
    }
}
