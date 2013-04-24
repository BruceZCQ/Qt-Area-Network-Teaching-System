#include "changepassworddialog.h"
#include "ui_changepassworddialog.h"

ChangePasswordDialog::ChangePasswordDialog(QWidget *parent) :
    QDialog(parent),
    ui(new Ui::ChangePasswordDialog)
{
    ui->setupUi(this);
    this->setWindowFlags(Qt::WType_TopLevel|Qt::WStyle_StaysOnTop |Qt::WindowTitleHint);
    connect(ui->submitBtn,SIGNAL(clicked()),this,SLOT(emitNewPassword()));
}

ChangePasswordDialog::~ChangePasswordDialog()
{
    delete ui;
}

void ChangePasswordDialog::emitNewPassword(){
    this->close();
    emit emitNewPassword(ui->newPassword->text());
    ui->newPassword->clear();
}
