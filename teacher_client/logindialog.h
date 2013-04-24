#ifndef LOGINDIALOG_H
#define LOGINDIALOG_H

#include <QDialog>
#include "mainwindow.h"
#include "settingdbserver.h"

namespace Ui {
    class TeachingLoginDialog;
}

class TeachingLoginDialog : public QDialog
{
    Q_OBJECT

public:
    explicit TeachingLoginDialog(QWidget *parent = 0);
    ~TeachingLoginDialog();
    void createActions();
    void createTray();
    void initWindow();
    void closeEvent(QCloseEvent *e);
    void keyPressEvent(QKeyEvent *e);
private slots:
    void checkUser();
    void showMainWin();
    void showLoginDialog();
    void dbClickTray(QSystemTrayIcon::ActivationReason reason);
    void showTrayMessage();    
    void refreshOnTrayMessage();
    void getServerConnectInfo();
signals:
    void quitApp();
private:
    bool getServerSetting();
    Ui::TeachingLoginDialog *ui;
    MainWindow *mainWin;
    QSystemTrayIcon *sysTray;
    QMenu *sysTrayMenu;
    QAction *awayAction;
    QAction *leaveAction;
    QAction *showMainWinAction;
    QAction *showMessageAction;
    QAction *quitAction;
    QAction *logoutAction;
    bool hasMessage;
    SettingDBServer *settingserverdialog;
    QString serverIP;
    QString serverPort;
    void checkSuccess();
    void startMovie();
    QTimer *getInfo;
};

#endif // LOGINDIALOG_H
