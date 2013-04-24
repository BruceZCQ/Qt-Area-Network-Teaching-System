#include <QtCore>
#include <QtGui>
#include "createquestion.h"
#include "ui_createquestion.h"
#include "constvar.h"

CreateQuestion::CreateQuestion(QWidget *parent) :
    QDialog(parent),
    ui(new Ui::CreateQuestion)
{
    ui->setupUi(this);
    ui->addQuestionBtn->setEnabled(false);
    //ui->buttonGroup->button(0)->setCheckable(true);
    this->setWindowFlags(Qt::WType_TopLevel|Qt::WStyle_StaysOnTop |Qt::WindowTitleHint);
    connect(ui->chapterNameList,SIGNAL(currentIndexChanged(int)),this,SLOT(currentIndexChanged(int)));
    connect(ui->refreshChapterBtn,SIGNAL(clicked()),this,SIGNAL(refreshChapterList()));
    connect(ui->addQuestionBtn,SIGNAL(clicked()),this,SLOT(addQuestion()));
    connect(this,SIGNAL(addQuestionResult(bool)),this,SLOT(addQuestionResultSlot(bool)));
}

CreateQuestion::~CreateQuestion()
{
    delete ui;
}

void CreateQuestion::setChapterList(QString chapterName)
{
    ui->chapterNameList->addItem(QIcon(":/appFace/chapter"),chapterName);
}

void CreateQuestion::clearQuestionList()
{
    ui->chapterNameList->clear();
    ui->chapterNameList->addItem(QIcon(":/appFace/selectquestion"),SELECTCHAPTER);
}

void CreateQuestion::addQuestion()
{
    int limitime = ui->limitTime->value();
    int score = ui->score->value();
    QString answer = ui->buttonGroup->checkedButton()->text();//get the anwser from the buttonGroup
    QString chapterName = ui->chapterNameList->itemText(ui->chapterNameList->currentIndex());
    QString questionTitle = ui->questionTitle->text();
    QString questionContext = ui->questionContext->toPlainText();
    if(questionTitle.isEmpty()||questionTitle.isNull()
            ||questionContext.isEmpty()||questionContext.isNull()){
        QMessageBox::information(this,SYSTEMPROMPT,
                                 INCOMPLETION);
        if(questionTitle.isEmpty()||questionTitle.isNull()){
            ui->questionTitle->setFocus();
        }
        else if(questionContext.isNull()||questionContext.isEmpty()){
            ui->questionContext->setFocus();
        }
    }else{
        emit addQuestion(chapterName,
                         questionTitle,
                         questionContext,
                         QString::number(limitime),
                         QString::number(score),
                         answer);
    }
}

void CreateQuestion::currentIndexChanged(int index)
{
    if(index!=0){
        ui->addQuestionBtn->setEnabled(true);
    }
    else{
        ui->addQuestionBtn->setEnabled(false);
    }
}

void CreateQuestion::addQuestionResultSlot(bool result)
{
    if(result == true){
        emit refreshChapterList();
        QMessageBox::information(this,SYSTEMPROMPT,SYSTEMESUCCESSPROMPT);
        clearAddQuestionInfo();
        this->close();
    }
    else{
        QMessageBox::information(this,SYSTEMPROMPT,SYSTEMERRORPROMPT);
    }
}

void CreateQuestion::clearAddQuestionInfo(){
    ui->questionTitle->clear();
    ui->questionContext->clear();
    ui->limitTime->setValue(0);
    ui->score->setValue(0);
}
