#include "questionwindow.h"
#include "ui_questionwindow.h"

QuestionWindow::QuestionWindow(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::QuestionWindow)
{
    ui->setupUi(this);
    flags = START;
    deleteWidget =  new QTimer;
    startQuestionTimer = new QTimer;
    startTime = 0;
    endTime = 0;
    ui->preBtn->setEnabled(false);
    ui->nextBtn->setEnabled(false);
    ui->startQuestion->setEnabled(false);
    createActions();
}

QuestionWindow::~QuestionWindow()
{
    delete ui;
}



void QuestionWindow::createActions()
{
    connect(ui->exitBtn,SIGNAL(clicked()),SLOT(close()));
    connect(ui->timeBox,SIGNAL(valueChanged(QString)),SLOT(settingTime(QString)));
    connect(ui->startQuestion,SIGNAL(clicked()),SLOT(startQuestion()));
    connect(ui->questionCountBox,SIGNAL(valueChanged(QString)),SLOT(setQuestionCount(QString)));
    connect(deleteWidget,SIGNAL(timeout()),SLOT(removeWidgetFormStackWidget()));
    connect(ui->preBtn,SIGNAL(clicked()),SLOT(prePage()));
    connect(ui->nextBtn,SIGNAL(clicked()),SLOT(nextPage()));
    connect(startQuestionTimer,SIGNAL(timeout()),SLOT(changeTime()));
    connect(ui->clearBtn,SIGNAL(clicked()),SLOT(clearAll()));
}

void QuestionWindow::showFullScreen()
{
    this->setWindowFlags(Qt::WType_TopLevel|Qt::WStyle_StaysOnTop |Qt::WindowTitleHint |Qt::FramelessWindowHint);
    QMainWindow::showFullScreen();
}

void QuestionWindow::close()
{
    //clear
    clearAll();
    QMainWindow::close();
}


void QuestionWindow::setDatabase(ServerDataBase *database)
{
    this->database = database;
}

void QuestionWindow::startQuestion()
{
    if(flags == START){
        deleteWidget->start(1);
        startQuestionTimer->start(1000);//per min
        flags = STOP;
        ui->preBtn->setEnabled(false);
        ui->nextBtn->setEnabled(false);
        ui->startQuestion->setText(STOPQUESTION);
        ui->timeBox->disconnect(this);////////////////!!!!!!!!!!!!
    }
    else{
        //show result info
        connect(ui->timeBox,SIGNAL(valueChanged(QString)),SLOT(settingTime(QString)));
        stopQuestion();
    }
}

void QuestionWindow::preperQuestionList()
{
    int questionCount = ui->questionCountBox->text().toInt();
    int allQuestionCount = database->getQuestionSetSize();
    QTime time= QTime::currentTime();
    qsrand(time.msec()+time.second()*1000);
    if(questionCount != 0){
        //set buttons
        ui->nextBtn->setEnabled(true);
        //get question info
        for(int index=0;index<questionCount;index++){
            int id = 0;
            do{
                id = qrand()%allQuestionCount;
            }while(id == 0);
            addQuestion(id);
        }//for
    }//!=0
}

void QuestionWindow::setQuestionCount(QString value)
{
    //set max size
    int allQuestionCount = database->getQuestionSetSize();
    ui->questionCountBox->setMaxValue(allQuestionCount);
    //    //
    if(endTime != 0 && value.toInt() !=0){
        ui->startQuestion->setEnabled(true);
    }
    else{
        ui->startQuestion->setEnabled(false);
    }
}

void QuestionWindow::removeWidgetFormStackWidget()
{
    int count = ui->questionlist->count();
    if(count!=0){
        for(int index=0; index<count;index++){
            ui->questionlist->removeWidget(ui->questionlist->widget(index));
            delete ui->questionlist->widget(index);
        }
    }
    else{
        deleteWidget->stop();
        preperQuestionList();
    }
}

void QuestionWindow::stopQuestion()
{
    startTime = 0;
    if( startQuestionTimer->isActive()){
        startQuestionTimer->stop();
    }
    flags = START;
    ui->timeBox->setValue(0);
    ui->lcdNumber->display(0);
    ui->questionCountBox->setValue(0);
    ui->startQuestion->setText(STARTQUESTION);
}


void QuestionWindow::prePage(){
    int index = ui->questionlist->currentIndex();
    if(index == 0){//the first
        ui->preBtn->setEnabled(false);
        ui->nextBtn->setEnabled(true);
        index=1;
    }
    else  if (index !=0 && index != ui->questionlist->count()-1){//the middle
        ui->preBtn->setEnabled(true);
        ui->nextBtn->setEnabled(true);
    }
    else   if(index == ui->questionlist->count()-1){//the last
        ui->preBtn->setEnabled(true);
        ui->nextBtn->setEnabled(false);
        answerEnd();
    }
    this->update();////////////////////!!!!!!!!!!!!!!!
    ui->questionlist->setCurrentIndex(index-1);
}


void QuestionWindow::nextPage(){
    int index = ui->questionlist->currentIndex();
    if(index == 0){
        ui->preBtn->setEnabled(false);
        ui->nextBtn->setEnabled(true);
    }
    else  if (index !=0 && index != ui->questionlist->count()-1){
        ui->preBtn->setEnabled(true);
        ui->nextBtn->setEnabled(true);
    }
    else  if(index == ui->questionlist->count()-1){
        ui->preBtn->setEnabled(true);
        ui->nextBtn->setEnabled(false);
        answerEnd();
    }
    this->update();////////////////////!!!!!!!!!!!!!!!
    ui->questionlist->setCurrentIndex(index+1);
}

void QuestionWindow::addQuestion(int id)
{
    QuestionWidget *questionWidget =  new QuestionWidget;
    QuestionSet *currentQuestion = database->getQuestionByID(id);
    questionWidget->setQuestionInfo(currentQuestion->getQuestionAnwser(), currentQuestion->getQuestionContent());
    ui->questionlist->addWidget(questionWidget);
    connect(questionWidget,SIGNAL(nextQuestion()),SLOT(nextPage()));
}

void QuestionWindow::changeTime()
{
    ui->lcdNumber->display(startTime);
    if(startTime <= endTime){
        ++startTime;
    }
    else{
        stopQuestion();
    }
}

void QuestionWindow::settingTime(QString value)
{
    endTime = value.toInt()*60;//1 min = 60s
    ui->lcdNumber->display(endTime);
    if(endTime != 0 && ui->questionCountBox->value() !=0){
        ui->startQuestion->setEnabled(true);
    }
    else{
        ui->startQuestion->setEnabled(false);
    }
}


void QuestionWindow::clearAll()
{
    deleteWidget->start(1);
    ui->preBtn->setEnabled(false);
    ui->nextBtn->setEnabled(false);
    stopQuestion();
}

void QuestionWindow::answerEnd()
{
    startTime = 0;
    if( startQuestionTimer->isActive()){
        startQuestionTimer->stop();
    }
    flags = START;
    ui->timeBox->setValue(0);
    ui->questionCountBox->setValue(0);
    ui->startQuestion->setText(STARTQUESTION);
    connect(ui->timeBox,SIGNAL(valueChanged(QString)),SLOT(settingTime(QString)));
}
