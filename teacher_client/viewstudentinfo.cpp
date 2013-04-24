#include "viewstudentinfo.h"
#include "ui_viewstudentinfo.h"
#include "constvar.h"

ViewStudentInfo::ViewStudentInfo(QWidget *parent) :
    QWidget(parent),
    ui(new Ui::ViewStudentInfo)
{
    ui->setupUi(this);
    this->setWindowFlags(Qt::WType_TopLevel|Qt::WStyle_StaysOnTop |Qt::WindowTitleHint);
    ui->answered->setRowCount(0);
}

ViewStudentInfo::~ViewStudentInfo()
{
    delete ui;
}

void ViewStudentInfo::setStudentInfo(QString studentID,
                                     QString studentName,
                                     QString studentSex,
                                     QString studentClassName,
                                     QString studentStatus,
                                     QString studentClassTimes,
                                     QString studentLastClassDate,
                                     QString studentScore)
{
    clearData();
    QString currentStatus;
    if(studentStatus == "on"){
        currentStatus = VIEWINFO_STATUS_ON;
    }
    else{
        currentStatus = VIEWINFO_STATUS_OFF;
    }
    ui->studentID->setText(studentID);
    ui->studentName->setText(studentName);
    ui->studentSex->setText(studentSex);
    ui->studentClass->setText(studentClassName);
    ui->studentStatus->setText(currentStatus);
    ui->studentClassTimes->setText(studentClassTimes);
    ui->studentLastClassDate->setText(studentLastClassDate);
    ui->studentScore->setText(studentScore);
}

void ViewStudentInfo::clearData()
{
    ui->studentID->clear();
    ui->studentName->clear();
    ui->studentSex->clear();
    ui->studentClass->clear();
    ui->studentStatus->clear();
    ui->studentClassTimes->clear();
    ui->studentLastClassDate->clear();
    ui->studentScore->clear();
}

void ViewStudentInfo::setAnsweredRows(int rows)
{
    ui->answered->setRowCount(rows);
}

void ViewStudentInfo::addAnsweredQuestion(int row,AnsweredQuestion *answered)
{
    QTableWidgetItem *questionIDItem = new QTableWidgetItem(answered->getQuestionID());
    questionIDItem->setTextAlignment(Qt::AlignHCenter|Qt::AlignBottom);
    ui->answered->setItem(row,0,questionIDItem);
    QTableWidgetItem *questionTitleItem = new QTableWidgetItem(answered->getQuestionTitle());
    questionTitleItem->setTextAlignment(Qt::AlignHCenter|Qt::AlignBottom);
    ui->answered->setItem(row,1,questionTitleItem);
    QTableWidgetItem *questionCorrectAnswerItem = new QTableWidgetItem(answered->getCorrectAnswer());
    questionCorrectAnswerItem->setTextAlignment(Qt::AlignHCenter|Qt::AlignBottom);
    ui->answered->setItem(row,2,questionCorrectAnswerItem);
    QTableWidgetItem *questionScoreItem = new QTableWidgetItem(answered->getQuestionScore());
    questionScoreItem->setTextAlignment(Qt::AlignHCenter|Qt::AlignBottom);
    ui->answered->setItem(row,3,questionScoreItem);
    QTableWidgetItem *studentAnswerItem = new QTableWidgetItem(answered->getStudentAnswer());
    studentAnswerItem->setTextAlignment(Qt::AlignHCenter|Qt::AlignBottom);//hcenter and buttom
    ui->answered->setItem(row,4,studentAnswerItem);
    QTableWidgetItem *studentScoreItem = new QTableWidgetItem(answered->getStudentScore());
    studentScoreItem->setTextAlignment(Qt::AlignHCenter|Qt::AlignBottom);//hcenter and buttom
    ui->answered->setItem(row,5,studentScoreItem);
}
