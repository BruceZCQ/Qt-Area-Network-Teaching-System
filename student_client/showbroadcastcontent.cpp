#include "showbroadcastcontent.h"
#include "ui_showbroadcastcontent.h"

ShowBroadCastContent::ShowBroadCastContent(QWidget *parent) :
    QDialog(parent),
    ui(new Ui::ShowBroadCastContent)
{
    ui->setupUi(this);
    this->setWindowFlags(Qt::WType_TopLevel|Qt::WStyle_StaysOnTop
                         |Qt::WindowTitleHint|Qt::FramelessWindowHint);
    QDesktopWidget* desktopWidget = QApplication::desktop();
   QRect screenRect = desktopWidget->screenGeometry();
    int winX = screenRect.width()-width();
    int winY = screenRect.height()-height();
    this->setGeometry(QRect(winX,winY-50,width(),height()));
}

ShowBroadCastContent::~ShowBroadCastContent()
{
    delete ui;
}

void ShowBroadCastContent::setContent(QString content)
{
    ui->broadCastContent->setText(content);
}

