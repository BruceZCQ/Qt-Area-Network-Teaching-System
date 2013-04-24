#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QtCore>
#include <QtGui>
#include "functionbox.h"
#include "teachingdb.h"
#include "changepassworddialog.h"
#include "sendquestiondialog.h"
#include "classmanagement.h"
#include "createquestion.h"
#include "viewstudentinfo.h"
#include "viewquestioninfo.h"
#include "infotabwidget.h"
#include "qxtglobalshortcut.h"
#include "answeredquestion.h"
#include "broadcast.h"

namespace Ui {
    class MainWindow;
}

class MainWindow : public QMainWindow
{
    Q_OBJECT
public:
    explicit MainWindow(QWidget *parent = 0);
    ~MainWindow();
    void keyPressEvent(QKeyEvent *e);
    void closeEvent(QCloseEvent *e);
    void setCurrentTeacherUser();
    void settingSever(QString host, QString port);
    void startMovie();
    bool eventFilter(QObject *o, QEvent *e);
    bool initDatabase();
    void setTreeItemsList();
    bool checkLoginingUser(QString userPassword);
    void setQuestionSet();
    void setServerHost(QString hostIP);
    bool connectQuestionServer();
    void closeDB();
signals:
    void logout();
    void minMe();
    void addNewClassSuccess();
    void updateQuestionResult(bool);
    void addQuestionResult(bool);    
    void refreshOnTrayMessage();
    void emptyInfoTabWidget();
    //global shortcut
    void showMe();
private slots:
    void about();
    void emitLogoutSignal();
    void itemDbClick(QTreeWidgetItem *item, int column);
    void itemPress(QTreeWidgetItem *item, int column);
    void emitNewPassword(QString newPassword);
    void classManage();
    void addNewClass(QString className, QString studentCount);
    void updateQuestion(QString questionIndex,
                      QString chapterID,
                      QString questionTitle,
                      QString questionContext,
                      QString limitTime,
                      QString questionScore,
                      QString answer);
    void addQuestion(QString chapterID,
                     QString questionTitle,
                     QString questionContext,
                     QString questionLimitTime,
                     QString questionScore,
                     QString answer);
    void viewStudentInfoSlot();
    void closeStudentTabWidgetByIndex(int index);
    void clearStudenetInfoList();
    void receiveQuestionAnswer();
//socket slots
    void sendQuestionInfo(QString questionInfo);
public slots:
    void quitApp();
    void refreshData();
    void deleteStudent();
    void setStudentZero();
    void deleteClassbyName(QString className);
    void broadCast();
private:

    void initWindowProfile();
    void createActions();
    void createGlobalActions();
    void setTooltips();
    Ui::MainWindow *ui;
    QRect screenRect;
    FunctionBox *functionbox;
    TeachingDB *teachinDB;
    QEvent *event;
    QString host;
    QString port;
    QString webHost;
    QString webPort;
    SendQuestionDialog *sendQuestion;
    ChangePasswordDialog *changePasswordDialog;
    ClassManagementDialog *classManageMentDialog;
    CreateQuestion *createQuestionDialog;
    InfoTabWidget *infoTabWidget;
    QHash<QString,ViewStudentInfo*> studentInfoList;
    //socket
    QTcpSocket *socket;
    QString serverIP;
    void updateStudentScore(QString studentID,QString questionID,QString questionAnswer);
};

#endif // MAINWINDOW_H
