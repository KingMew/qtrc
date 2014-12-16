#include "mainwindow.h"
#include "ui_mainwindow.h"
#include <QTimer>
#include <QCloseEvent>
#include <QDebug>
#include <QDesktopWidget>

MainWindow::MainWindow(QWidget *parent) :
    QWidget(parent),
    ui(new Ui::MainWindow)
{
    ui->setupUi(this);
    //setWindowFlags(windowFlags() | Qt::Tool);
    this->setWindowFlags(Qt::Tool | Qt::FramelessWindowHint | Qt::WindowStaysOnTopHint | Qt::WindowSystemMenuHint | Qt::WindowDoesNotAcceptFocus);
    this->setStyleSheet("background:transparent;");
    this->setAttribute(Qt::WA_TranslucentBackground, true);
    this->setAttribute(Qt::WA_NoSystemBackground, true);
    this->setAttribute(Qt::WA_ShowWithoutActivating);
    this->mode = RC_CURSOR;
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
    QString filename = ":/rc"+QString::number(rand()%std::min(phase+1,3)+1)+".png";
#ifdef QTRC_DEBUG
    qDebug("rand phase batch: %d %d %d %d\n", rand()%std::min(phase+1,3)+1,rand()%std::min(phase+1,3)+1,rand()%std::min(phase+1,3)+1,rand()%std::min(phase+1,3)+1);
    qDebug("filename: %s %d %d\n",qPrintable(filename), QPixmap(filename).width(),QPixmap(filename).height() );
#endif
    setGeometry(this->geometry().x(), this->geometry().y(), QPixmap(filename).width(), QPixmap(filename).height());
    this->ui->centralWidget->resize(QPixmap(filename).width(),QPixmap(filename).height());
    this->ui->label->setGeometry(0,0,QPixmap(filename).width(),QPixmap(filename).height());
    this->ui->label->setPixmap(QPixmap(filename));
}

void MainWindow::setPositionMode(RC_POSITION_MODE m)
{
    mode=m;
    switch(mode)
    {
	case RC_CURSOR:
	{
	    this->move(QCursor::pos());
	}
	    break;
	case RC_RANDOM:
	{
	    int x,y;
	    QRect r = QApplication::desktop()->availableGeometry();
	    x = rand()%r.width();
	    y = rand()%r.height();
	    this->move(x,y);
	}
	    break;
	case RC_CENTER:
	{
	    int x,y;
	    QRect r = QApplication::desktop()->screenGeometry();
	    x = r.width()/2-this->geometry().width()/2;
	    y = r.height()/2-this->geometry().height()/2;
	    this->move(x,y);
	}
	    break;
    }
}
