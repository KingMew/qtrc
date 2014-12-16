#include "controller_window.h"
#include "mainwindow.h"
#include "ui_controller_window.h"
#include "QMessageBox"
#include <QStandardPaths>
#include <QTimer>
#include <cstdlib>
#include <stdio.h>
#include <time.h>
#include <QDesktopWidget>
#include <QDir>

#define TIMER_DURATION (min+(rand()%(max-min+1)))*1000
#define PHASETIMER_DURATION 7200000

#define MODE_CURSOR "Cursor Position"
#define MODE_RANDOM "Random Position"
#define MODE_CENTER "Screen Center"

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
    this->phasetimer->setInterval(PHASETIMER_DURATION);
    this->phasetimer->start();
    //readConfig();
    moveToCenter();
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

void controller_window::readConfig()
{
    QString configDirPath = QStandardPaths::writableLocation(QStandardPaths::ConfigLocation)+PATH_SEPARATOR+APP_NAME;
    if(!QDir(configDirPath).exists())
    {
	QDir().mkdir(configDirPath);
    }

    QString configPath = configDirPath+PATH_SEPARATOR+"config";
    FILE *configFile = fopen(configPath.toStdString().c_str(),"r");
    if(configFile!=NULL)
    {
	printf("Config file found, reading...\n");
	char buffer[256];
	while(fgets(buffer,sizeof(buffer),configFile))
	{
	    QString curLine = buffer;

	}
    }
    else
    {
	printf("Config file not found at location: %s\n"
	       "Creating file now...\n",configPath.toStdString().c_str());
	configFile = fopen(configPath.toStdString().c_str(),"w");
	if(configFile==NULL)
	{
	    fprintf(stderr,"Cannot write to config file. Aborting and using program defaults.\n");
	    return;
	}
	else
	{
	    fprintf(configFile,"#qtrc config file\n"
			       "MIN_DURATION=170\n"
			       "MAX_DURATION=270\n"
			       "LOCATION=CURSOR\n"
			       "STOP=no\n"
			       "STOP_HOURS=0\n"
			       "#do a RC!"
		    );
	    printf("Config file written!\n");
	}
    }
    fclose(configFile);
}

void controller_window::StartRC()
{
    min=this->ui->minDuration->text().toInt();
    max=this->ui->maxDuration->text().toInt();
    getPositionMode();
    int stopCheck = (!this->ui->stopCheck->isChecked()||this->ui->stopHours->text().toInt()>0);
    if(min>0 && max>=min && stopCheck)
    {
	this->hide();
	timer->start(TIMER_DURATION);
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

void controller_window::getPositionMode()
{
    QString mode_str = this->ui->positionMode->currentText();
    if(mode_str.compare(MODE_CURSOR)==0)
    {
	positionMode = RC_CURSOR;
    }
    else if(mode_str.compare(MODE_RANDOM)==0)
    {
	positionMode = RC_RANDOM;
    }
    else if(mode_str.compare(MODE_CENTER)==0)
    {
	positionMode = RC_CENTER;
    }
    else
    {
	positionMode = RC_CURSOR;
    }
}

void controller_window::ShowRC()
{
    this->timer->stop();
    MainWindow *rc = new MainWindow();
    rc->ChgGraphic(phase);
    rc->setPositionMode(positionMode);
    rc->show();
    int duration = TIMER_DURATION;
#ifdef QTRC_DEBUG
	    qDebug("Next duration: %d\n",duration);
#endif
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

void controller_window::moveToCenter()
{
    int x,y;
    QRect r = QApplication::desktop()->screenGeometry();
    x = r.width()/2-this->geometry().width()/2;
    y = r.height()/2-this->geometry().height()/2;
    this->move(x,y);
}
