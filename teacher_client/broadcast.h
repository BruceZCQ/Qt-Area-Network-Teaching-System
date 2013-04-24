#ifndef BROADCAST_H
#define BROADCAST_H

#include <QtCore>
#include <QtGui>
#include "constvar.h"

namespace Ui {
    class BroadCast;
}

class BroadCast : public QDialog
{
    Q_OBJECT

public:
    explicit BroadCast(QWidget *parent = 0);
    ~BroadCast();
    QString getBroadCastContent();
    void keyPressEvent(QKeyEvent *e);
private:
    Ui::BroadCast *ui;
private slots:
    void sendBroadCastContent();
};

#endif // BROADCAST_H
