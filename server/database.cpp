#include <QtCore>
#include <QtGui>
#include "database.h"

ServerDataBase::ServerDataBase(QString host,QString port)
{
    //init database connect flag
    databaseConnectResult = false;
    db = new QSqlDatabase(QSqlDatabase::addDatabase("QMYSQL"));
    db->setHostName(host);
    db->setPort(port.toInt());
    db->setDatabaseName("teachingroom");
    db->setUserName("root");
    db->setPassword("admin");
    bool dbConn = db->open();
    if (dbConn) {
        databaseConnectResult = true;
    } else {
        databaseConnectResult = false;
        QString errorInfo = db->lastError().text()+QObject::tr("\nPlease resetting your DB server");
        QMessageBox::critical(0,QObject::tr("Database Setting Error"),errorInfo);
    }
    classList.clear();
    studentsList.clear();
    ipList.clear();
}
//close db
void ServerDataBase::closeDB()
{
    QString dbname = db->connectionName();
    db->close();
    delete db;
    db = NULL;
    QSqlDatabase::removeDatabase(dbname);
    databaseConnectResult = false;
}
//get connect result
bool ServerDataBase::getConnectionResult()
{
    return databaseConnectResult;
}

ServerDataBase::~ServerDataBase(){
    delete db;
    classList.clear();
    studentsList.clear();
    ipList.clear();
}
//check user info
bool ServerDataBase::checkUser(QString userPassword)
{
    QString checkUserSql = "SELECT * FROM TEACHER WHERE TEACHERNAME='jsp001';";
    QSqlQuery checkQuery(checkUserSql);
    if(checkQuery.exec()){
        while(checkQuery.next()){
            if(checkQuery.value(1).toString()==userPassword){
                return true;
            }
            else{
                return false;
            }
        }
    }
    else{
        db->rollback();
        return false;
    }
    return true;
}


void ServerDataBase::initData()
{
    classList.clear();
    studentsList.clear();
    ipList.clear();
    //get class from database
    QSqlQuery selectClassQuery("SELECT * FROM CLASS;");
    while(selectClassQuery.next()){
        QString className = selectClassQuery.value(0).toString();
        QString classStudentCount = selectClassQuery.value(1).toString();
        classList.insert(className,classStudentCount);
    }
    //get student from database
    for(int i=0;i<classList.size();i++){
        if(i==0)
        {
            firstClassName = classList.keys().at(i);//the first show in dashboard
        }
        QString selectStudentSql = "SELECT * FROM STUDENT WHERE STUEDNTCLASS='"+classList.keys().at(i)+"';";
        QSqlQuery selectStudentQuery(selectStudentSql);
        while(selectStudentQuery.next()){
            TeachingRoomStudents *student = new TeachingRoomStudents;
            QString studentID = selectStudentQuery.value(0).toString();
            QString studentName = selectStudentQuery.value(1).toString();
            student->setStudentID(studentID);//studentID
            student->setStudentName(studentName);//studentName
            student->setClassMajor(classList.keys().at(i));//studentClass
            student->setStudentSex(selectStudentQuery.value(2).toString());//studentSex
            student->setStudentStatus(selectStudentQuery.value(4).toString());//studentstatus
            student->setClassCount(selectStudentQuery.value(5).toString());//classCount
            student->setClassTime(selectStudentQuery.value(6).toString());//classDate
            student->setStudentScore(selectStudentQuery.value(7).toString());//studentscore
            student->setIpAddRess(selectStudentQuery.value(8).toString());//stundetIpaddress
            ipList.append(selectStudentQuery.value(8).toString());//add current student ipaddress
            studentsList.insertMulti(classList.keys().at(i),student);
        }
    }
}

TeachingRoomClass* ServerDataBase::getClassFromDB(int index)
{
    TeachingRoomClass *currentClass = new TeachingRoomClass;
    currentClass->setClassName(classList.keys().at(index));
    currentClass->setClassStudentsCount(classList.values().at(index));
    return currentClass;
}

int ServerDataBase::getClassCount()
{
    return classList.size();
}

int ServerDataBase::getStudentsCountByClassName(QString className)
{
    return studentsList.values(className).size();
}

TeachingRoomStudents* ServerDataBase::getStudentsByClassFromDB(QString className,int index)
{
    TeachingRoomStudents *student = new TeachingRoomStudents;
    student = studentsList.values(className).at(index);
    return student;
}

QString ServerDataBase::getFirstClassName()
{
    return firstClassName;
}

int ServerDataBase::getIpListSize()
{
    return ipList.size();
}

QString ServerDataBase::getIPaddressByIndex(int index)
{
    return ipList.at(index);
}

