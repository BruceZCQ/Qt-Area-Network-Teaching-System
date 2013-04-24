#include <QtCore>
#include <QtGui>
#include "settingserver.h"
#include "ui_settingserver.h"

SettingServer::SettingServer(QWidget *parent) :
    QDialog(parent),
    ui(new Ui::settingServer)
{
    ui->setupUi(this);
    this->setWindowFlags(Qt::WType_TopLevel|Qt::WStyle_StaysOnTop
                         |Qt::WindowTitleHint|Qt::FramelessWindowHint);
    initServerConfData();
    connect(ui->setBtn,SIGNAL(clicked()),this,SLOT(settingServer()));
}

SettingServer::~SettingServer()
{
    delete ui;
}

void SettingServer::settingServer()
{
    QSettings teachingroomsetting("teachingroomstudent",qAppName());
    teachingroomsetting.beginGroup(tr("SettingServer"));
    teachingroomsetting.setValue(tr("ip"),ui->ipAddressEdit->text());
    teachingroomsetting.setValue(tr("port"),ui->portEdit->text());
    teachingroomsetting.endGroup();
    close();
}

void SettingServer::initServerConfData()
{
    QSettings teachingroomsetting("teachingroomstudent",qAppName());
    teachingroomsetting.beginGroup(tr("SettingServer"));
    QString serverIP = teachingroomsetting.value(tr("ip")).toString();
    QString serverPort = teachingroomsetting.value(tr("port")).toString();
    teachingroomsetting.endGroup();
    ui->ipAddressEdit->setText(serverIP);
    ui->portEdit->setText(serverPort);
}
