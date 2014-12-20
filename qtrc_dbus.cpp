#include "qtrc_dbus.h"
#include <QApplication>

qtrc_dbus::qtrc_dbus(QObject *parent) : QDBusAbstractAdaptor(parent)
{
	win = (controller_window*)parent;
}

qtrc_dbus::~qtrc_dbus()
{

}

void qtrc_dbus::Reconfigure()
{
	win->show();
	win->showNormal();
	win->raise();
	win->activateWindow();
}

void qtrc_dbus::Stop()
{
	QApplication::exit(0);
}

void qtrc_dbus::Show()
{
	if(win->isActive())
	{
		win->ShowRC();
	}
	else
	{
		qDebug("RC Timer is currently inactive; Ignoring Show() command.\n");
	}
}

