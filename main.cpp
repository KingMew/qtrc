#include "mainwindow.h"
#include "controller_window.h"
#include "qtrc_dbus.h"
#include <QApplication>
#include <QtDBus/QtDBus>
#include <QTimer>
#include <cstdio>
#include <global.h>
#define ARG_FLAG(val,flag) if(strcmp(argv[i],val)==0) { flag = true; }

int main(int argc, char *argv[])
{
	bool bStop = false;
	bool bShow = false;
	for(int i = 1; i < argc; i++)
	{
		ARG_FLAG("--exit",bStop) ;
		ARG_FLAG("--show",bShow) ;
	}

	QDBusInterface qdbi("net.mew151.qtrc","/","net.mew151.qtrc");
	QDBusMessage reply;
	if(bStop)
	{
		reply = qdbi.call("Stop");
	}
	else if(bShow)
	{
		reply = qdbi.call("Show");
	}
	else
	{
		reply = qdbi.call("Reconfigure");
	}
	if((reply.type() == QDBusMessage::ReplyMessage))
	{
		return 0;
	}

	QApplication a(argc, argv);

	controller_window win;
	new qtrc_dbus(&win);
	QDBusConnection::sessionBus().registerObject("/",&win);
	QDBusConnection::sessionBus().registerService("net.mew151.qtrc");

	win.show();
	return a.exec();
}
