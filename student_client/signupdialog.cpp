#include "signupdialog.h"
#include "ui_signupdialog.h"
#include "constvar.h"

SignUpDialog::SignUpDialog(QWidget *parent) :
    QDialog(parent),
    ui(new Ui::SignUpDialog)
{
    ui->setupUi(this);
    this->setWindowFlags(Qt::WType_TopLevel|Qt::WStyle_StaysOnTop
                         |Qt::WindowTitleHint|Qt::FramelessWindowHint);
    ui->classBox->clear();
    ui->studentIDTxt->setFocus();
    connect(ui->submitInfoBtn,SIGNAL(clicked()),this,SLOT(acceptDialog()));
}

SignUpDialog::~SignUpDialog()
{
    delete ui;
}

void SignUpDialog::acceptDialog()
{
    QString studentName = ui->studentnameTxt->text();
    QString studentID = ui->studentIDTxt->text();
    QString sex = ui->sex->currentText();
    QString className = ui->classBox->currentText();
   if(studentID.isEmpty()){
        QMessageBox::information(this,tr("Prompt"),INFOCANNOTOVER);
        ui->studentIDTxt->setFocus();
    }
    else  if(studentName.isEmpty()){
       QMessageBox::information(this,tr("Prompt"),INFOCANNOTOVER);
       ui->studentnameTxt->setFocus();
   }
    else if(sex.isEmpty()){
      QMessageBox::information(this,tr("Prompt"),INFOCANNOTOVER);
      ui->sex->setFocus();
    }
    else{
        emit emitRegisterData(studentID,studentName,sex,className);
    }
}

void SignUpDialog::initData(QString className)
{
    ui->classBox->addItem(className);
}

void SignUpDialog::clearClassList()
{
    ui->classBox->clear();
}

void SignUpDialog::accept()
{
    ui->studentIDTxt->clear();
    ui->studentnameTxt->clear();
    QDialog::accept();
}
