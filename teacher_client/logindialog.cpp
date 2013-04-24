#include "logindialog.h"
#include "settingdbserver.h"
#include "constvar.h"
#include "ui_logindialog.h"

TeachingLoginDialog::TeachingLoginDialog(QWidget *parent) :
    QDialog(parent),
    ui(new Ui::TeachingLoginDialog)
{
    ui->setupUi(this);
    this->setWindowFlags(Qt::WType_TopLevel|Qt::WStyle_StaysOnTop |Qt::WindowTitleHint);
    initWindow();
    createTray();
    createActions();
}


TeachingLoginDialog::~TeachingLoginDialog()
{
    //delete sysTrayMenu;
    //delete mainWin;

    /*
    power's note: use explain can avoid
Error -
RtlWerpReportException failed with status code :-1073741823. Will try to launch the process directly
    */
    delete sysTray;
    delete ui;
}

void TeachingLoginDialog::createActions()
{
    connect(ui->submitBtn,SIGNAL(clicked()),this,SLOT(checkUser()));
    connect(showMainWinAction,SIGNAL(triggered()),this,SLOT(showMainWin()));
    connect(quitAction,SIGNAL(triggered()),mainWin,SLOT(quitApp()));
    connect(sysTray,SIGNAL(activated(QSystemTrayIcon::ActivationReason)),this,SLOT(dbClickTray(QSystemTrayIcon::ActivationReason)));
    connect(this,SIGNAL(quitApp()),qApp,SLOT(quit()));
    connect(logoutAction,SIGNAL(triggered()),this,SLOT(showLoginDialog()));
    connect(ui->settingBtn,SIGNAL(clicked()),settingserverdialog,SLOT(exec()));
    //signals from mainwindow
    connect(mainWin,SIGNAL(logout()),this,SLOT(showLoginDialog()));
    connect(mainWin,SIGNAL(logout()),ui->passWord,SLOT(setFocus()));
    connect(mainWin,SIGNAL(minMe()),this,SLOT(showTrayMessage()));
    connect(mainWin,SIGNAL(refreshOnTrayMessage()),this,SLOT(refreshOnTrayMessage()));
    //signal from settingdbserver dialog
    connect(settingserverdialog,SIGNAL(imClosed()),ui->passWord,SLOT(setFocus()));
    //global shortcut
    connect(mainWin,SIGNAL(showMe()),this,SLOT(showMainWin()));
    //getserverconnectinfo
    connect(getInfo,SIGNAL(timeout()),this,SLOT(getServerConnectInfo()));
}

bool TeachingLoginDialog::getServerSetting()
{
    QSettings teachingroomsetting("teachingroom",qAppName());
    teachingroomsetting.beginGroup(tr("SettingServer"));
    serverIP = teachingroomsetting.value(tr("ip")).toString();
    serverPort = teachingroomsetting.value(tr("port")).toString();
    teachingroomsetting.endGroup();
    if(serverIP.isEmpty()||serverIP.isNull()||serverPort.isEmpty()||serverPort.isNull()){
        QMessageBox::question(this,SETTINGSERVERPROMPT,SETTINGSERVERPROMPTMOREINFO,QMessageBox::Ok);
        return false;
    }
    else{
        return true;
    }
}


void TeachingLoginDialog::checkUser()
{
    if(getServerSetting()){
        if(ui->passWord->text().isEmpty()
                || ui->passWord->text().isNull()){
            QMessageBox::information(this,PASSWORDEMPTY,PASSWORDEMPTYPROMPT,QMessageBox::Ok);
            ui->passWord->setFocus();
        }
        else{
            mainWin->settingSever(serverIP,serverPort);
            if(mainWin->initDatabase()){
                if(mainWin->checkLoginingUser(ui->passWord->text())){
                    mainWin->setServerHost(serverIP);
                    checkSuccess();
                }
                else{
                    QMessageBox::information(this,PASSWORDERRORPROMPT,PASSWORDFAILUREPROMPT,QMessageBox::Ok);
                    ui->passWord->clear();
                    ui->passWord->setFocus();
                }
            }
        }
    }
}

void TeachingLoginDialog::checkSuccess()
{
    ui->stackedWidget->setCurrentIndex(1);
    startMovie();
    getInfo->start(1000);
}

void TeachingLoginDialog::getServerConnectInfo()
{
    if(mainWin->connectQuestionServer()){
         ui->stackedWidget->setCurrentIndex(0);
        getInfo->stop();
        this->hide();
        mainWin->show();
        sysTray->show();
        sysTray->showMessage(SYSPROMPT_SUCCESS,
                             SYSPROMPT_SUCCESSMOREINFO,
                             QSystemTrayIcon::Information,100);
    }
}

void TeachingLoginDialog::startMovie()
{
    QMovie *movie = new QMovie(":/appFace/loading");
    ui->loading->setMovie(movie);
    movie->start();
}


void TeachingLoginDialog::initWindow()
{
    // main window
    mainWin = new MainWindow;
    // sysTray
    sysTray = new QSystemTrayIcon;
    sysTrayMenu = new QMenu;
    showMainWinAction = new QAction(SHOWMAINWINACTION,this);
    showMessageAction = new QAction(SHOWMESSAGEACTION,this);
    quitAction = new QAction(QUITACTION,this);
    logoutAction = new QAction(LOGOUTACTION,this);
    //
    hasMessage = false;
    settingserverdialog = new SettingDBServer;
    getInfo = new QTimer;
    ui->passWord->setFocus();
}

void TeachingLoginDialog::createTray()
{
    //setting tray's icon
    sysTray->setIcon(QIcon(":/appFace/systray"));
    //setting tray's menu
    sysTrayMenu->addAction(showMainWinAction);
    sysTrayMenu->addAction(showMessageAction);
    sysTrayMenu->addSeparator();
    sysTrayMenu->addAction(logoutAction);
    sysTrayMenu->addAction(quitAction);
    sysTray->setContextMenu(sysTrayMenu);
    //set Tray tooltip
    sysTray->setToolTip(SYSTOOLTIP);
}


void TeachingLoginDialog::showMainWin(){
    if(mainWin->isHidden()){
        mainWin->show();
    }
    else{
        mainWin->hide();
    }
}

void TeachingLoginDialog::showLoginDialog(){
    mainWin->close();
    sysTray->hide();
    this->show();
    ui->userName->setFocus();
}

void TeachingLoginDialog::closeEvent(QCloseEvent *)
{
    if(sysTray->isVisible()){
        delete sysTray;
    }
    emit quitApp();
}

void TeachingLoginDialog::dbClickTray(QSystemTrayIcon::ActivationReason reason){
    if(reason == QSystemTrayIcon::DoubleClick&&hasMessage==false){
        showMainWin();
    }
}

void TeachingLoginDialog::showTrayMessage(){
    sysTray->showMessage(SYSTEMPROMPT,
                         SYSTEMPROMPTMOREINFO,
                         QSystemTrayIcon::Information,100);
}

void TeachingLoginDialog::keyPressEvent(QKeyEvent *e)
{
    if(e->key() == Qt::Key_Escape){
        qApp->exit();
    }
    else if(e->key() == Qt::Key_Return){
        ui->submitBtn->click();
    }
    else{
        e->accept();
    }
}

void TeachingLoginDialog::refreshOnTrayMessage()
{
    sysTray->showMessage(SYSTEMPROMPT,
                         SYSTEMREFRESHPROMPT,
                         QSystemTrayIcon::Information,100);
}


