#ifndef QTRC_DBUS_H
#define QTRC_DBUS_H

#include <QObject>
#include <controller_window.h>
#include <QtDBus/QtDBus>

class qtrc_dbus : public QDBusAbstractAdaptor
{
		Q_OBJECT
	public:
		explicit qtrc_dbus(QObject *parent = 0);
		~qtrc_dbus();

	public Q_SLOTS:
		void Reconfigure();
		void Stop();
		void Show();

	private:
		controller_window *win;
		Q_CLASSINFO("D-Bus Interface", "net.mew151.qtrc")
};

#endif // QTRC_DBUS_H
