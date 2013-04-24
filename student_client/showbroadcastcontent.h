#ifndef SHOWBROADCASTCONTENT_H
#define SHOWBROADCASTCONTENT_H

#include <QtCore>
#include <QtGui>

namespace Ui {
    class ShowBroadCastContent;
}

class ShowBroadCastContent : public QDialog
{
    Q_OBJECT

public:
    explicit ShowBroadCastContent(QWidget *parent = 0);
    void setContent(QString content);
    ~ShowBroadCastContent();

private:
    Ui::ShowBroadCastContent *ui;
private slots:
};

#endif // SHOWBROADCASTCONTENT_H
