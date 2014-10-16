#ifndef RC_NOTIFICATION_H
#define RC_NOTIFICATION_H

#include <QWidget>

namespace Ui {
class rc_notification;
}

class rc_notification : public QWidget
{
    Q_OBJECT

public:
    explicit rc_notification(QWidget *parent = 0);
    ~rc_notification();

private:
    Ui::rc_notification *ui;
};

#endif // RC_NOTIFICATION_H
