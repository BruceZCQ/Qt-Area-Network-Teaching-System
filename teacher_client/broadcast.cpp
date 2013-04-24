#include "broadcast.h"
#include "ui_broadcast.h"

BroadCast::BroadCast(QWidget *parent) :
    QDialog(parent),
    ui(new Ui::BroadCast)
{
    ui->setupUi(this);
    this->setWindowFlags(Qt::WType_TopLevel|Qt::WStyle_StaysOnTop
                         |Qt::WindowTitleHint);
    connect(ui->broadCastBtn,SIGNAL(clicked()),SLOT(sendBroadCastContent()));
}

BroadCast::~BroadCast()
{
    delete ui;
}

QString BroadCast::getBroadCastContent()
{
    return ui->broadCastContent->toPlainText();
}

void BroadCast::sendBroadCastContent()
{
    if(ui->broadCastContent->toPlainText().length()!=0){
        this->accept();
    }
    else{
        ui->label->setText(BROADCASTCONTENTISEMPTY);
    }
}

void BroadCast::keyPressEvent(QKeyEvent *e)
{
    if(e->key()==Qt::Key_Return){
        sendBroadCastContent();
    }
}
