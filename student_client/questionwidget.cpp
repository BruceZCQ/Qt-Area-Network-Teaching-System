#include "questionwidget.h"
#include "ui_questionwidget.h"

QuestionWidget::QuestionWidget(QWidget *parent) :
    QWidget(parent),
    ui(new Ui::QuestionWidget)
{
    ui->setupUi(this);
    sendNext = new QTimer;
    createActions();
}

QuestionWidget::~QuestionWidget()
{
    delete ui;
}


void QuestionWidget::setMovie(int result)
{
    QString pic ;
    if(result == OK){
        pic = QString(":/appFace/ok");
    }
    else{
        pic = QString(":/appFace/no");
    }
    QMovie *movie = new QMovie(pic);
    ui->showResultPic->setMovie(movie);
    movie->start();
}

void QuestionWidget::setQuestionInfo(QString answer, QString content)
{
    ui->questionContent->setText(content);
    correctAnswer = answer;
}

void QuestionWidget::createActions()
{
    connect(ui->sureBtn,SIGNAL(clicked()),SLOT(submitAnswer()));
    connect(sendNext,SIGNAL(timeout()),SIGNAL(nextQuestion()));
    connect(sendNext,SIGNAL(timeout()),sendNext,SLOT(stop()));
}


void QuestionWidget::submitAnswer(){
    QString answer;
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
    if(answer == correctAnswer){
        setMovie(OK);
    }
    else{
        setMovie(NO);
    }
    sendNext->start(1000);
}
