#include "controller_window.h"
#include "mainwindow.h"
#include "ui_controller_window.h"
#include "QMessageBox"
#include <QTimer>
#include <cstdlib>
//#include <stdio.h>
#include <time.h>

controller_window::controller_window(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::controller_window)
{
    srand(time(NULL));
    ui->setupUi(this);
    phase = 0;
    timer = new QTimer(this);
    stoptimer = new QTimer(this);
    phasetimer = new QTimer(this);
    phaseD = false;
    this->phasetimer->setInterval(86400000);
    connect(timer,SIGNAL(timeout()),this,SLOT(ShowRC()));
    connect(stoptimer,SIGNAL(timeout()),this,SLOT(Shutdown()));
    connect(phasetimer,SIGNAL(timeout()),SLOT(AddPhase()));
    connect(ui->goButton,SIGNAL(clicked()),this,SLOT(StartRC()));
    connect(ui->stopCheck,SIGNAL(clicked()),this,SLOT(ToggleStops()));
}

controller_window::~controller_window()
{
    delete ui;
}

void controller_window::StartRC()
{
    min=this->ui->minDuration->text().toInt();
    max=this->ui->maxDuration->text().toInt();
    int stopCheck = (!this->ui->stopCheck->isChecked()||this->ui->stopHours->text().toInt()>0);
    if(min>0 && max>=min && stopCheck)
    {
        this->hide();
        timer->start((min+(rand()%(max-min)))*1000);
        if(this->ui->stopHours->text().toInt()>0 && this->ui->stopCheck->isChecked())
        {
            stoptimer->start(this->ui->stopHours->text().toInt()*60000);
        }
    }
    else
    {
        QMessageBox msg;
        msg.setText("Invalid Configuration");
        if(min<=0)
        {
            msg.setInformativeText("Minimum duration must be greater than zero.");
        }
        else if(max<min)
        {
            msg.setInformativeText("Maximum duration must be greater or equal to minimum duration.");
        }
        else if(!stopCheck)
        {
            msg.setInformativeText("Hours must be greater than 0.");
        }
        msg.setStandardButtons(QMessageBox::Ok);
        msg.setDefaultButton(QMessageBox::Ok);
        msg.exec();
    }
}

void controller_window::ShowRC()
{
    this->timer->stop();
    MainWindow *rc = new MainWindow();
    rc->ChgGraphic(phase);
    rc->show();
    int duration = (min+(rand()%(max-min)))*1000;
    //printf("Duration: %d\n",duration);
    this->timer->setInterval(duration);
    this->timer->start();
}

void controller_window::ToggleStops()
{
    ui->stopHours->setEnabled(ui->stopCheck->isChecked());
}

void controller_window::Shutdown()
{
    QApplication::exit(0);
}

void controller_window::AddPhase()
{
    if(!phaseD)
    {
        phase = std::min(phase+1,3);
        if(phase == 3)
        {
            phaseD = true;
        }
        return;
    }
    else
    {
        phase = std::max(phase-1,0);
        if(phase == 0)
        {
            phaseD = false;
        }
        return;
    }
    phasetimer->start();
}
