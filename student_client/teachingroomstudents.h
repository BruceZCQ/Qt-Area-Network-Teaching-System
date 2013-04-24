#ifndef TEACHINGROOMSTUDENTS_H
#define TEACHINGROOMSTUDENTS_H

#include <QtCore>

class TeachingRoomStudents
{
public:
    TeachingRoomStudents();
    void setStudentID(QString studentID);
    QString getStudentID();
    void setStudentName(QString studentName);
    QString getStudentName();
    void setStudentSex(QString studentSex);
    QString getStudentSex();
    void setClassMajor(QString classMajor);
    QString getClassMajor();
    void setStudentStatus(QString studentStatus);
    QString getStudentStatus();
    void setClassCount(QString classCount);
    QString getClassCount();
    void setClassTime(QString classTime);
    QString getClassTime();
    void setStudentScore(QString score);
    QString getStudentScore();
    void setIpAddRess(QString ipAddress);
    QString getIpAddress();
private:
    QString studentID;
    QString studentName;
    QString studentSex;
    QString classMajor;
    QString studentStatus;
    QString classCount;
    QString classTime;
    QString score;
    QString ipAddress;
};

#endif // TEACHINGROOMSTUDENTS_H
