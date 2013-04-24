#include <QtGui>
#include "editquestion.h"
#include "ui_editquestion.h"
#include "constvar.h"

EditQuestion::EditQuestion(QWidget *parent) :
    QDialog(parent),
    ui(new Ui::EditQuestion)
{
    ui->setupUi(this);
    this->setWindowFlags(Qt::WType_TopLevel|Qt::WStyle_StaysOnTop |Qt::WindowTitleHint);
    connect(ui->questionID,SIGNAL(currentIndexChanged(int)),this,SIGNAL(changeCurrentQuestionIndex(int)));
    connect(ui->refreshQuestionDataBtn,SIGNAL(clicked()),this,SLOT(refreashQuestionDataSlot()));
    connect(ui->submitEditResultBtn,SIGNAL(clicked()),this,SLOT(submitEditValue()));

}

EditQuestion::~EditQuestion()
{
    delete ui;
}

void EditQuestion::addItem(QString itemText)
{
    ui->questionID->addItem(QIcon(":/appFace/questionlisticon"),itemText);
}

void EditQuestion::setValue(QString chapter,
                            QString questionTitle,
                            QString questionCotext,
                            QString limitTime,
                            QString score,
                            QString answer)
{
    ui->chapterID->setText(chapter);
    ui->questionTitle->setText(questionTitle);
    ui->questionContext->setText(questionCotext);
    ui->limitTime->setValue(limitTime.toInt());
    ui->questionScore->setValue(score.toInt());
    if(answer == "A")
    {
        ui->radio_A->setChecked(true);
    }
    if(answer == "B")
    {
        ui->radio_B->setChecked(true);
    }
    if(answer == "C")
    {
        ui->radio_C->setChecked(true);
    }
    if(answer == "D")
    {
        ui->radio_D->setChecked(true);
    }
}

void EditQuestion::setCurrentQuestionID(int questionIndex)
{
    ui->questionID->setCurrentIndex(questionIndex);
}

void EditQuestion::clearInfo()
{
    ui->questionID->setCurrentIndex(0);
    ui->questionTitle->clear();
    ui->chapterID->clear();
    ui->questionContext->clear();
    ui->limitTime->setValue(0);
    ui->questionScore->setValue(0);
}

void EditQuestion::refreashQuestionDataSlot(){
    int currentIndex = ui->questionID->currentIndex();
    ui->questionID->setCurrentIndex(0);
    ui->questionID->setCurrentIndex(currentIndex);
    emit refreashQuestionData();
}

void EditQuestion::submitEditValue(){
    QString answer = ui->buttonGroup->checkedButton()->text();//get the anwser from the buttonGroup
    emit emitNewValue(QString::number(ui->questionID->currentIndex()),
                      ui->chapterID->text(),
                      ui->questionTitle->text(),
                      ui->questionContext->toPlainText(),
                      QString::number(ui->limitTime->value()),
                      QString::number(ui->questionScore->value()),
                      answer);
}

void EditQuestion::slotUpdateResult(bool result)
{
    if(result){
        QMessageBox::information(this,SYSTEMPROMPT,SYSTEMESUCCESSPROMPT);
        close();
    }
    else{
        QMessageBox::information(this,SYSTEMPROMPT,SYSTEMERRORPROMPT);
        }
}
