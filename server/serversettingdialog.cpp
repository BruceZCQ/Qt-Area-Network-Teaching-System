#include "serversettingdialog.h"
#include "ui_serversettingdialog.h"

ServerSettingDialog::ServerSettingDialog(QWidget *parent) :
    QDialog(parent),
    ui(new Ui::ServerSettingDialog)
{
    ui->setupUi(this);
    setWindowFlags(Qt::WindowTitleHint);
    initDBServerConfData();
    setDefaultFocus();
    connect(ui->settingBtn,SIGNAL(clicked()),this,SLOT(settingDBServer()));
}

ServerSettingDialog::~ServerSettingDialog()
{
    delete ui;
}

void ServerSettingDialog::settingDBServer()
{
    QSettings teachingroomsetting("teachingroomServer",qAppName());
    teachingroomsetting.beginGroup(tr("SettingServer"));
    teachingroomsetting.setValue(tr("ip"),ui->ipAddressEdit->text());
    teachingroomsetting.setValue(tr("port"),ui->portEdit->text());
    teachingroomsetting.endGroup();
    emit imClosed();
    close();
}

void ServerSettingDialog::initDBServerConfData()
{
    QSettings teachingroomsetting("teachingroomServer",qAppName());
    teachingroomsetting.beginGroup(tr("SettingServer"));
    QString serverIP = teachingroomsetting.value(tr("ip")).toString();
    QString serverPort = teachingroomsetting.value(tr("port")).toString();
    teachingroomsetting.endGroup();
    ui->ipAddressEdit->setText(serverIP);
    ui->portEdit->setText(serverPort);
}

void ServerSettingDialog::setDefaultFocus()
{
    ui->ipAddressEdit->setFocus();
}
