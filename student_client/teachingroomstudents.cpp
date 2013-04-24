#include "teachingroomstudents.h"

TeachingRoomStudents::TeachingRoomStudents()
{
}

void TeachingRoomStudents::setStudentID(QString studentID){
    this->studentID = studentID;
}

QString TeachingRoomStudents::getStudentID(){
    return this->studentID;
}

void TeachingRoomStudents::setStudentName(QString studentName)
{
    this->studentName = studentName;
}

QString TeachingRoomStudents::getStudentName()
{
    return this->studentName;
}

void TeachingRoomStudents::setStudentSex(QString studentSex)
{
    this->studentSex = studentSex;
}

QString TeachingRoomStudents::getStudentSex()
{
    return this->studentSex;
}

void TeachingRoomStudents::setClassMajor(QString classMajor)
{
    this->classMajor = classMajor;
}

QString TeachingRoomStudents::getClassMajor()
{
    return this->classMajor;
}

void TeachingRoomStudents::setStudentStatus(QString studentStatus)
{
    this->studentStatus = studentStatus;
}

QString TeachingRoomStudents::getStudentStatus()
{
    return this->studentStatus;
}

void TeachingRoomStudents::setClassCount(QString classCount)
{
    this->classCount = classCount;
}

QString TeachingRoomStudents::getClassCount()
{
    return this->classCount;
}

void TeachingRoomStudents::setClassTime(QString classTime)
{
    this->classTime = classTime;
}

QString TeachingRoomStudents::getClassTime()
{
    return this->classTime;
}

void TeachingRoomStudents::setStudentScore(QString score)
{
    this->score = score;
}

QString TeachingRoomStudents::getStudentScore()
{
    return this->score;
}

void TeachingRoomStudents::setIpAddRess(QString ipAddress)
{
    this->ipAddress = ipAddress;
}

QString TeachingRoomStudents::getIpAddress()
{
    return this->ipAddress;
}
