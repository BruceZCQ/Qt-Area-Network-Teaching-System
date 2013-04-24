#ifndef TEACHINGDB_H
#define TEACHINGDB_H

#include <QtCore>
#include <QtSql/QSqlDatabase>
#include <QtSql>
#include <QtNetwork>
#include "questionset.h"

class ServerDataBase
{
public:
    ServerDataBase(QString host,QString port);
    ~ServerDataBase();
    void initData();
    void closeDB();
    bool getConnectionResult();
    bool checkUser(QString userID);
    int getClassCount();
    QString getClassNamebyIndex(int index);
    int addStudent(QString studentID,
                         QString userName,
                         QString sex,
                         QString className);
    bool updateStudentStatus(QString studentID,QString status);
    int getChapterListSize();
    QString getChapterNameByIndex(int index);
    int getChapterIDByIndex(int index);
    QuestionSet* getQuestionByID(int id);
    bool updateLastClassDate(QString studentID);
    bool updateStudentIPaddress(QString studentID);
    int getQuestionSetSize();
private:
    //the database handle
    QSqlDatabase *db;
    //database connection result
    bool databaseConnectResult;
    QStringList classList;
    QHash<int,QString> pptList;
    enum result {success,failure,updatestatusfailure};
    QHash<QString,QuestionSet*> questionSetList;
};

#endif // TEACHINGDB_H
