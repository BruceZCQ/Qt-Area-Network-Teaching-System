#include "sendquestiondialog.h"
#include "ui_sendquestiondialog.h"
#include "constvar.h"

SendQuestionDialog::SendQuestionDialog(QWidget *parent) :
    QDialog(parent),
    ui(new Ui::SendQuestionDialog)
{
    ui->setupUi(this);
    questionList.clear();
     this->setWindowFlags(Qt::WType_TopLevel|Qt::WStyle_StaysOnTop |Qt::WindowTitleHint);
    ui->editQuestionBtn->setEnabled(false);
    ui->sendQuesitonBtn->setEnabled(false);
    connect(ui->questionID,SIGNAL(currentIndexChanged(int)),this,SLOT(changeQuestionData(int)));
    connect(ui->refreshQuestionSetBtn,SIGNAL(clicked()),this,SLOT(refreshQuestionSetSlot()));
    //editquestion
    editQuestion = new EditQuestion;
    connect(ui->editQuestionBtn,SIGNAL(clicked()),this,SLOT(editCurrentQuestion()));
    connect(editQuestion,SIGNAL(changeCurrentQuestionIndex(int)),this,SLOT(changeCurrentQuestionIndex(int)));
    connect(editQuestion,SIGNAL(refreashQuestionData()),this,SIGNAL(refreshQuestionSet()));
    connect(editQuestion,SIGNAL(emitNewValue(QString,QString,QString,QString,QString,QString,QString)),
            this,SIGNAL(emitNewValue(QString,QString,QString,QString,QString,QString,QString)));
    connect(this,SIGNAL(emtUpdateResult(bool)),editQuestion,SLOT(slotUpdateResult(bool)));
    //send quesiton  id
    connect(ui->sendQuesitonBtn,SIGNAL(clicked()),SLOT(sendQuestionID()));
}

SendQuestionDialog::~SendQuestionDialog()
{
    delete ui;
    questionList.clear();
}

void SendQuestionDialog::setCurrentUser(TeachingRoomStudents *user){
    currentStundent = user;
    ui->userNameLabel->setText(tr("[<font color='red'>")+currentStundent->getStudentName()+tr("</font>]"));
}


void SendQuestionDialog::closeEvent(QCloseEvent *e)
{
    ui->questionID->setCurrentIndex(0);
    ui->questionTimelimit->display(0);
    e->accept();
}

void SendQuestionDialog::setQuestionSet(QuestionSet *question)
{
    int questionID = question->getQuestionID().toInt();
    if(questionList.contains(questionID) == false){
        ui->questionID->addItem(QIcon(":/appFace/questionlisticon"),QUESTIONID+question->getQuestionID());
        editQuestion->addItem(QUESTIONID+question->getQuestionID());
    }
    questionList.insert(questionID,question);
}

void SendQuestionDialog::changeQuestionData(int quesionIndex){
    if(quesionIndex==0){
        ui->sendQuesitonBtn->setEnabled(false);
    }
    else{
        ui->sendQuesitonBtn->setEnabled(true);
    }
    if(questionList.contains(quesionIndex)){
        clearQuestionInfo();
        ui->editQuestionBtn->setEnabled(true);
        int index = quesionIndex;
        ui->questionTitle->setText(questionList.value(index)->getQuestionTitle());
        QString description = QUESTIONADDR
                +questionList.value(index)->getChapterID()
                +QUESTIONSCORE+questionList.value(index)->getQuestionScore()
                +QUESTIONPUBLICDATE+questionList.value(index)->getQuestionPublicDate()
                +QUESTIONPUBLICDATEEND;
        ui->questionDescription->append(description);//after the prompt apend the question data
        ui->questionTimelimit->display(questionList.value(index)->getQuestionLimitTime());
        ui->questionContent->append(questionList.value(index)->getQuestionContent());
    }
    else{
        clearQuestionInfo();
    }
}

void SendQuestionDialog::clearQuestionInfo()
{
    ui->editQuestionBtn->setEnabled(false);
    ui->questionTitle->clear();
    ui->questionDescription->clear();
    ui->questionDescription->setText(QUESTIONDEC);
    ui->questionTimelimit->display(0);
    ui->questionContent->clear();
    ui->questionContent->setText(QUESTIONCONTEXT);
}


void SendQuestionDialog::editCurrentQuestion()
{
    int index = ui->questionID->currentIndex();
    editQuestion->setCurrentQuestionID(index);
    editQuestion->setValue(questionList.value(index)->getChapterID(),
                           questionList.value(index)->getQuestionTitle(),
                           questionList.value(index)->getQuestionContent(),
                           questionList.value(index)->getQuestionLimitTime(),
                           questionList.value(index)->getQuestionScore(),
                           questionList.value(index)->getQuestionAnwser());
    editQuestion->exec();
}

void SendQuestionDialog::changeCurrentQuestionIndex(int index){
    if(index != 0){
        editQuestion->setValue(questionList.value(index)->getChapterID(),
                               questionList.value(index)->getQuestionTitle(),
                               questionList.value(index)->getQuestionContent(),
                               questionList.value(index)->getQuestionLimitTime(),
                               questionList.value(index)->getQuestionScore(),
                               questionList.value(index)->getQuestionAnwser());
    }
    else{
        editQuestion->clearInfo();
    }
}

void SendQuestionDialog::refreshQuestionSetSlot()
{
    int currentIndex = ui->questionID->currentIndex();
    ui->questionID->setCurrentIndex(0);
    ui->questionID->setCurrentIndex(currentIndex);
    update();
    emit refreshQuestionSet();
}



void SendQuestionDialog::sendQuestionID()
{
    int id = ui->questionID->currentIndex();
//    questionSocket->write(QString("teacher/"+QString::number(id)+" \n").toUtf8());
    emit sentQuestion("teacher/"+currentStundent->getStudentID()+"/"+QString::number(id)+"\n");
}

