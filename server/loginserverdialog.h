#ifndef LOGINSERVERDIALOG_H
#define LOGINSERVERDIALOG_H

#include <QtCore>
#include <QtGui>
#include "serverstyle.h"
#include "serverdashboard.h"
#include "serversettingdialog.h"
#include "database.h"
#include "serverconst.h"

namespace Ui {
    class LoginServerDialog;
}

class LoginServerDialog : public QDialog
{
    Q_OBJECT

public:
    explicit LoginServerDialog(QWidget *parent = 0);
    ~LoginServerDialog();
    //get the system style
    /*
    inline ServerStyle* getStyle() const{
        return style;
    }*/
    void createActions();
    //GET SERVER CONF DATA
    bool getServerSettingConfData();
private slots:
    void showDashboardSlot();//show the dashboard private slot
    void showSettingServerSlot();//show the settinf server private slot
    //setting default focus
    void setDefaultFocus();
    //close databse
    void closeDB();
private:
    Ui::LoginServerDialog *ui;
    ServerDashboard *dashboard;
    ServerSettingDialog *settingServer;
    QString serverIP;
    QString serverPort;
    ServerDataBase *database;
    bool setCurrentFocus();//check info is completion or not and set focus
    int infoIsCompletion();//check info is completion or not
    bool checkUserInfo();//check info indriect ,and print the prompt
    void printErrorPrompt();//print error prompt
};

#endif // LOGINSERVERDIALOG_H
