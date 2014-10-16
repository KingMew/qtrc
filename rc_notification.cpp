#include "rc_notification.h"
#include "ui_rc_notification.h"

rc_notification::rc_notification(QWidget *parent) :
    QWidget(parent),
    ui(new Ui::rc_notification)
{
    ui->setupUi(this);
}

rc_notification::~rc_notification()
{
    delete ui;
}
