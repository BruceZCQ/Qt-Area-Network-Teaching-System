#ifndef LOGINDIALOG_H
#define LOGINDIALOG_H

#include <QtCore>
#include <QtGui>
#include "settingserver.h"
#include "signupdialog.h"
#include "database.h"
#include "studentdashboard.h"

namespace Ui {
class TeachingLoginDialog;
}

class TeachingLoginDialog : public QDialog
{
    Q_OBJECT

public:
    explicit TeachingLoginDialog(QWidget *parent = 0);
    ~TeachingLoginDialog();
    void closeEvent(QCloseEvent *e);
    void keyPressEvent(QKeyEvent *e);
private slots:
    void checkUser();
    void showDashBoardWin();
    void showLoginDialog();
    void showSignUpDialog();
    void registerStudent(QString studentID,
                         QString userName,
                         QString sex,
                         QString className);
    void exitApp();
    //
    void getServerConnectInfo();
    void startMovie();
signals:
    void quitApp();
    void registerSuccess();
private:
    void createActions();
    void initWindow();
    bool getServerSetting();
    void checkSuccess();
    Ui::TeachingLoginDialog *ui;
    bool hasMessage;
    SettingServer *settingserverdialog;
    QString serverIP;
    QString serverPort;
    //signupdialog
    SignUpDialog *signupdialog;
    ServerDataBase *database;
    bool isConn;
    enum result {success,failure,updatestatusfailure};
    //dashboard
    StudentDashBoard *dashBoard;
    QTimer *getInfo;
    QProcess *process;
    void hidenStartMenu(bool);
};

#endif // LOGINDIALOG_H
