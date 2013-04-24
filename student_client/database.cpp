#include <QtCore>
#include <QtGui>
#include "database.h"

ServerDataBase::ServerDataBase(QString host,QString port)
{
    //init list
    classList.clear();
    pptList.clear();
    questionSetList.clear();
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
    closeDB();
    classList.clear();
    pptList.clear();
    questionSetList.clear();
}
//check user info
bool ServerDataBase::checkUser(QString userID)
{
    QString checkUserSql = "SELECT * FROM STUDENT WHERE STUDENTID='"+userID+"';";
    QSqlQuery checkQuery(checkUserSql);
    if(checkQuery.exec()){
        if(checkQuery.next()){
            return true;
        }
        else{
            return false;
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
    pptList.clear();
    questionSetList.clear();

    //get classname from database
    QSqlQuery selectClassQuery("SELECT * FROM CLASS;");
    while(selectClassQuery.next()){
        QString className = selectClassQuery.value(0).toString();
        classList.append(className);
    }
    //get ppt list
    QSqlQuery selectPPTQuery("SELECT * FROM CHAPTER");
    while(selectPPTQuery.next()){
        int chapterID = selectPPTQuery.value(0).toInt();
        QString chapterName = selectPPTQuery.value(1).toString();
        pptList.insert(chapterID,chapterName);
    }
    //get questionset from database
    QSqlQuery selectQuestionSetQuery("SELECT * FROM QUESTIONSET");
    while(selectQuestionSetQuery.next()){
        QuestionSet *question = new QuestionSet;
        QString questionID = QString::number(selectQuestionSetQuery.value(0).toInt());
        question->setQustionID(questionID);
        QString chapterID = selectQuestionSetQuery.value(1).toString();
        question->setChapterID(chapterID);
        QString questionTitle = selectQuestionSetQuery.value(2).toString();
        question->setQuestionTitle(questionTitle);
        QString questionContent = selectQuestionSetQuery.value(3).toString();
        question->setQuestionContent(questionContent);
        QString questionLimitTime = selectQuestionSetQuery.value(4).toString();
        question->setQuestionLimitTime(questionLimitTime);
        QString questionPublicDate = selectQuestionSetQuery.value(5).toString();
        question->setQuestionPublicDate(questionPublicDate);
        QString questionScore = selectQuestionSetQuery.value(6).toString();
        question->setQuestionScore(questionScore);
        QString questionAnwser = selectQuestionSetQuery.value(7).toString();
        question->setQuestionAnwser(questionAnwser);
        questionSetList.insert(questionID,question);
    }
}

int ServerDataBase::getClassCount()
{
    return classList.size();
}

QString ServerDataBase::getClassNamebyIndex(int index)
{
    return classList.at(index);
}

int ServerDataBase::addStudent(QString studentID, QString userName, QString sex, QString className)
{
    QString localHostName = QHostInfo::localHostName();
    QHostInfo info = QHostInfo::fromName(localHostName);
    QString localhostIP ;
    foreach(QHostAddress address,info.addresses()) {
        if(address.protocol() == QAbstractSocket::IPv4Protocol){
           localhostIP = address.toString();
        }
    }
    QString currentDate = QString::number(QDate::currentDate().year())+"."
            +QString::number(QDate::currentDate().month())+"."
            +QString::number(QDate::currentDate().day()) ;
    currentDate = currentDate+QTime::currentTime().toString("  hh:mm:ss");
    QString insertStudentSql = "INSERT INTO STUDENT VALUES('"+studentID
            +"','"+userName+"','"+sex+"','"+className+"','off','0','"+currentDate+"','0','"+localhostIP+"');";
    QSqlQuery insertQuery(*db);
    insertQuery.prepare(insertStudentSql);
    if(insertQuery.exec()){
        if(updateStudentStatus(studentID,"on") == false) {
            return updatestatusfailure;
        }
        else{
            return success;
        }
    }
    else{
        db->rollback();
        return failure;
    }
}

bool ServerDataBase::updateStudentStatus(QString studentID,QString status)
{
    QString updateStudentStatusSql = "UPDATE STUDENT SET STUDENTSTATUS='"+status+"' WHERE STUDENTID='"+studentID+"';";
    QSqlQuery updateQuery(*db);
    updateQuery.prepare(updateStudentStatusSql);
    if(updateQuery.exec()){
        return true;
    }
    else{
        db->rollback();
        return false;
    }
}

int ServerDataBase::getChapterListSize()
{
    return pptList.keys().size();
}

QString ServerDataBase::getChapterNameByIndex(int index)
{
    return pptList.value(pptList.keys().at(index));
}

int ServerDataBase::getChapterIDByIndex(int index)
{
    return pptList.keys().at(index);
}

QuestionSet * ServerDataBase::getQuestionByID(int id)
{
    return questionSetList.value(QString::number(id));
}


int ServerDataBase::getQuestionSetSize()
{
    return questionSetList.size();
}


bool ServerDataBase::updateLastClassDate(QString studentID)
{
    QString currentDate = QString::number(QDate::currentDate().year())+"."
            +QString::number(QDate::currentDate().month())+"."
            +QString::number(QDate::currentDate().day()) ;
    currentDate = currentDate+QTime::currentTime().toString("  hh:mm:ss");
    QString updateStudentLastClassDateSql = "UPDATE STUDENT SET STUDENTONCLASSDATE='"+currentDate+"' WHERE STUDENTID='"+studentID+"';";
    QSqlQuery updateQuery(*db);
    updateQuery.prepare(updateStudentLastClassDateSql);
    if(updateQuery.exec()){
        return true;
    }
    else{
        db->rollback();
        return false;
    }
}

bool ServerDataBase::updateStudentIPaddress(QString studentID)
{
    QString localHostName = QHostInfo::localHostName();
    QHostInfo info = QHostInfo::fromName(localHostName);
    QString localhostIP ;
    foreach(QHostAddress address,info.addresses()) {
        if(address.protocol() == QAbstractSocket::IPv4Protocol){
           localhostIP = address.toString();
        }
    }
    QString updateStudentipAddressSql = "UPDATE STUDENT SET STUDENTIPADDRESS='"+localhostIP+"' WHERE STUDENTID='"+studentID+"';";
    QSqlQuery updateQuery(*db);
    updateQuery.prepare(updateStudentipAddressSql);
    if(updateQuery.exec()){
        return true;
    }
    else{
        db->rollback();
        return false;
    }
}
