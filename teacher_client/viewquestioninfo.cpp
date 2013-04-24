#include "viewquestioninfo.h"
#include "ui_viewquestioninfo.h"
#include "constvar.h"

ViewQuestionInfo::ViewQuestionInfo(QWidget *parent) :
    QWidget(parent),
    ui(new Ui::ViewQuestionInfo)
{
    ui->setupUi(this);
    this->setWindowFlags(Qt::WType_TopLevel|Qt::WStyle_StaysOnTop |Qt::WindowTitleHint);
    connect(ui->editBtn,SIGNAL(clicked()),this,SLOT(enableAll()));
    //3
    connect(ui->questionTitleTxt,SIGNAL(textChanged(QString)),this,SLOT(changeBtnTxt()));
    connect(ui->questionTitleTxt,SIGNAL(textEdited(QString)),this,SLOT(changeBtnTxt()));
    //4
    connect(ui->questionContextTxt,SIGNAL(textChanged()),this,SLOT(changeBtnTxt()));
    connect(ui->questionContextTxt,SIGNAL(sourceChanged(QUrl)),this,SLOT(changeBtnTxt()));
//    //5
//    connect(ui->questionAnwserTxt,SIGNAL(textChanged(QString)),this,SLOT(changeBtnTxt()));
//    connect(ui->questionAnwserTxt,SIGNAL(textEdited(QString)),this,SLOT(changeBtnTxt()));
//    //6
//    connect(ui->questionLimitTimeTxt,SIGNAL(textChanged(QString)),this,SLOT(changeBtnTxt()));
//    connect(ui->questionLimitTimeTxt,SIGNAL(textEdited(QString)),this,SLOT(changeBtnTxt()));
}

ViewQuestionInfo::~ViewQuestionInfo()
{
    delete ui;
}

void ViewQuestionInfo::enableAll()
{
    ui->questionTitleTxt->setEnabled(true);//3
    ui->questionContextTxt->setEnabled(true);//4
    ui->questionAnwserTxt->setEnabled(true);//5
    ui->questionLimitTimeTxt->setEnabled(true);//6
}

void ViewQuestionInfo::changeBtnTxt()
{
    ui->editBtn->setText(SUBMITEDIT);
}
