#ifndef SERVERDASHBOARD_H
#define SERVERDASHBOARD_H

#include <QtCore>
#include <QtGui>
#include "serverconst.h"
#include "studentclassinfomaintain.h"
#include "database.h"

namespace Ui {
    class ServerDashboard;
}

class ServerDashboard : public QMainWindow
{
    Q_OBJECT

public:
    explicit ServerDashboard(QWidget *parent = 0);
    ~ServerDashboard();
    //build and connect the actions and the slots
    void createActions();
    void closeEvent(QCloseEvent *e);
    void setDatabaseHandle(ServerDataBase *databaseHandle);
    //get count by class name
    int getStudentsCountByClassName(QString className);
    TeachingRoomStudents* getStudentsByClassFromDB(QString className,int index);
signals:
    void closedDashboard();
public slots:
    void addTab();
private slots:
    void quitApp();
    void refreshMaintainData();
    void studentClassInfoMaintainAddItemSlot();
    void setCurrentClass(QString className);
    void startServer();
private:
    Ui::ServerDashboard *ui;
    ServerDataBase *databaseHandle;
    void initData();
    void initClassList();//init the class list data
    void initStudentList(QString className);//init the student list  data
    //class list
    QList<TeachingRoomClass*> classList;
    //student list
    QList<TeachingRoomStudents*> studentList;
    //student class maintain
    StudentClassInfoMaintain *studentClassMaintainWin;
    //current class
    QString currentClassName;
};

#endif // SERVERDASHBOARD_H
