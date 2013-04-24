#ifndef VIEWSTUDENTINFO_H
#define VIEWSTUDENTINFO_H

#include <QtCore>
#include <QtGui>
#include "answeredquestion.h"

namespace Ui {
    class ViewStudentInfo;
}

class ViewStudentInfo : public QWidget
{
    Q_OBJECT

public:
    explicit ViewStudentInfo(QWidget *parent = 0);
    ~ViewStudentInfo();
    void setStudentInfo(QString studentID,
                        QString studentName,
                        QString studentSex,
                        QString studentClassName,
                        QString studentStatus,
                        QString studentClassTimes,
                        QString studentLastClassDate,
                        QString studentScore);
    void setAnsweredRows(int rows);
    void addAnsweredQuestion(int row,AnsweredQuestion *answered);
private:
    Ui::ViewStudentInfo *ui;
    void clearData();
};

#endif // VIEWSTUDENTINFO_H
