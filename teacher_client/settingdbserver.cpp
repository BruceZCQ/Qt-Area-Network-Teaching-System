#include <QtCore>
#include <QtGui>
#include "settingdbserver.h"
#include "ui_settingdbserver.h"

SettingDBServer::SettingDBServer(QWidget *parent) :
    QDialog(parent),
    ui(new Ui::settingDBServer)
{
    ui->setupUi(this);
    this->setWindowFlags(Qt::WType_TopLevel|Qt::WStyle_StaysOnTop |Qt::WindowTitleHint);
    initDBServerConfData();
    connect(ui->setBtn,SIGNAL(clicked()),this,SLOT(settingDBServer()));
}

SettingDBServer::~SettingDBServer()
{
    delete ui;
}

void SettingDBServer::settingDBServer()
{
    QSettings teachingroomsetting("teachingroom",qAppName());
    teachingroomsetting.beginGroup(tr("SettingServer"));
    teachingroomsetting.setValue(tr("ip"),ui->ipAddressEdit->text());
    teachingroomsetting.setValue(tr("port"),ui->portEdit->text());
    teachingroomsetting.endGroup();
    emit imClosed();
    close();
}

void SettingDBServer::initDBServerConfData()
{
    QSettings teachingroomsetting("teachingroom",qAppName());
    teachingroomsetting.beginGroup(tr("SettingServer"));
    QString serverIP = teachingroomsetting.value(tr("ip")).toString();
    QString serverPort = teachingroomsetting.value(tr("port")).toString();
    teachingroomsetting.endGroup();
    ui->ipAddressEdit->setText(serverIP);
    ui->portEdit->setText(serverPort);
}
