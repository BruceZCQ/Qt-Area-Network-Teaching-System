#include "receivequestion.h"
#include "ui_receivequestion.h"

ReceiveQuestion::ReceiveQuestion(QWidget *parent) :
    QDialog(parent),
    ui(new Ui::ReceiveQuestion)
{
    ui->setupUi(this);
    timer = new QTimer;
    limitTime = 0.0;
    createActions();
}

ReceiveQuestion::~ReceiveQuestion()
{
    delete ui;
}

void ReceiveQuestion::setQuestion(QuestionSet *question)
{
    currentQuestionID = question->getQuestionID();
    this->setWindowTitle(ANSWERQUESTIONID
                         +currentQuestionID);
    limitTime = question->getQuestionLimitTime().toDouble();
    ui->timeLimit->display(limitTime--);
    ui->questionContent->setText(question->getQuestionContent());
}

void ReceiveQuestion::exec()
{
    setTopLevel();
    timer->start(1000);
    QDialog::exec();
}

void ReceiveQuestion::createActions()
{
    connect(ui->sendAnswerBtn,SIGNAL(released()),this,SLOT(answerSentSlot()));
    connect(timer,SIGNAL(timeout()),SLOT(changeDisplay()));
  //  connect(this,SIGNAL(accepted()),this,SLOT(deleteLater()));////!!!!!!!!!!!!!!!!!!!!!!!
}

void ReceiveQuestion::setTopLevel(){
    this->setWindowFlags(Qt::WType_TopLevel|Qt::WStyle_StaysOnTop
                         |Qt::WindowTitleHint|Qt::FramelessWindowHint);
}

void ReceiveQuestion::answerSentSlot(){
    QString answer="null";
    if(ui->answerA->isChecked()){
        answer = "A";
    }
    if(ui->answerB->isChecked()){
        answer = "B";
    }
    if(ui->answerC->isChecked()){
        answer = "C";
    }
    if(ui->answerD->isChecked()){
        answer = "D";
    }
    emit answerSent(currentQuestionID+"/"+answer);
}


void ReceiveQuestion::changeDisplay(){
    if(limitTime==0){
        timer->stop();
        answerSentSlot();
    }
    else{
        ui->timeLimit->display(limitTime--);
    }
    toTop();
}

void ReceiveQuestion::toTop()
{
    this->setWindowFlags(Qt::WType_TopLevel|Qt::WStyle_StaysOnTop
                         |Qt::WindowTitleHint|Qt::FramelessWindowHint);
}

