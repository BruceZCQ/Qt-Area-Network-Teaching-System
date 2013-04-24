#ifndef TEACHINGDB_H
#define TEACHINGDB_H

#include <QtCore>
#include <QtSql/QSqlDatabase>
#include <QtSql>
#include "teachingroomstudents.h"
#include "teachingroomclass.h"

class ServerDataBase
{
public:
    ServerDataBase(QString host,QString port);
    ~ServerDataBase();
    void closeDB();
    bool getConnectionResult();
    bool checkUser(QString userPassword);
    void initData();
    TeachingRoomClass *getClassFromDB(int index);
    int getClassCount();
    int getStudentsCountByClassName(QString className);
    TeachingRoomStudents *getStudentsByClassFromDB(QString className, int index);
    QString getFirstClassName();
    int getIpListSize();
    QString getIPaddressByIndex(int index);
private:
    //the database handle
    QSqlDatabase *db;
    //database connection result
    bool databaseConnectResult;
    //classlist
    QHash<QString,QString> classList;
    //studentslist from class
    QHash<QString,TeachingRoomStudents*> studentsList;
    QString firstClassName;
    QList<QString> ipList;
};

#endif // TEACHINGDB_H
