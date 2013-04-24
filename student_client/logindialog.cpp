#include "logindialog.h"
#include "settingserver.h"
#include "constvar.h"
#include "ui_logindialog.h"

TeachingLoginDialog::TeachingLoginDialog(QWidget *parent) :
    QDialog(parent),
    ui(new Ui::TeachingLoginDialog)
{
    ui->setupUi(this);
    this->setWindowFlags(Qt::WType_TopLevel|Qt::WStyle_StaysOnTop
                         |Qt::WindowTitleHint|Qt::FramelessWindowHint);
    initWindow();
    createActions();
}


TeachingLoginDialog::~TeachingLoginDialog()
{
    delete ui;
}

void TeachingLoginDialog::createActions()
{
    connect(ui->submitBtn,SIGNAL(clicked()),this,SLOT(checkUser()));
    connect(ui->settingBtn,SIGNAL(clicked()),settingserverdialog,SLOT(exec()));
    //signals from pptwindow
    //signup
    connect(ui->signupBtn,SIGNAL(clicked()),this,SLOT(showSignUpDialog()));
    connect(signupdialog,SIGNAL(emitRegisterData(QString,QString,QString,QString)),
            this,SLOT(registerStudent(QString,QString,QString,QString)));
    connect(this,SIGNAL(registerSuccess()),signupdialog,SLOT(accept()));
    //exit and closedb
    connect(dashBoard,SIGNAL(exitApp()),this,SLOT(exitApp()));
    //getserverconnectinfo
    connect(getInfo,SIGNAL(timeout()),this,SLOT(getServerConnectInfo()));
}

bool TeachingLoginDialog::getServerSetting()
{
    QSettings teachingroomsetting("teachingroomstudent",qAppName());
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
    if(getServerSetting() == true){
        if(isConn == false){
            database = new ServerDataBase(serverIP,serverPort);
            database->initData();
            isConn = true;
        }
        if(database->getConnectionResult() == true
                &&database->checkUser(ui->userName->text())
                &&database->updateStudentStatus(ui->userName->text(),"on")){
            checkSuccess();
        }else{
            ui->userName->setFocus();
            QMessageBox::information(this,SETTINGSERVERPROMPT,LOGINFAILURE,QMessageBox::Ok);
        }
    }
}

void TeachingLoginDialog::initWindow()
{
    //register
    signupdialog = new SignUpDialog;
    isConn = false;
    database = NULL;
    //message
    hasMessage = false;
    settingserverdialog = new SettingServer;
    //dashboard
    dashBoard = new StudentDashBoard;
    //focus
    ui->userName->setFocus();
    getInfo = new QTimer;
    process = new  QProcess;
    //lock the switch work and startmenu
    process->start("lockdesktop.exe");
    process->start("locktoolbar.exe");
    hidenStartMenu(true);
}



void TeachingLoginDialog::showDashBoardWin(){
    if(dashBoard->isHidden()){
        dashBoard->showFullScreen();
    }
    else{
        dashBoard->hide();
    }
}

void TeachingLoginDialog::showLoginDialog(){
    dashBoard->close();
    this->show();
    ui->userName->setFocus();
}

void TeachingLoginDialog::closeEvent(QCloseEvent *e)
{
    e->ignore();
}


void TeachingLoginDialog::keyPressEvent(QKeyEvent *e)
{
    if(e->key() == Qt::Key_Return){
        ui->submitBtn->click();
    }
    else{
        e->accept();
    }
}

void TeachingLoginDialog::showSignUpDialog()
{
    if(getServerSetting() == true){
        if(isConn == false){
            database = new ServerDataBase(serverIP,serverPort);
            database->initData();
            isConn = true;
        }
        if(database->getConnectionResult() == true){
            //add items to signupbox
            signupdialog->clearClassList();
            int classCount = database->getClassCount();
            for (int index=0; index<classCount; index++){
                QString className = database->getClassNamebyIndex(index);
                signupdialog->initData(className);
            }
            signupdialog->exec();
        }
    }
}

void TeachingLoginDialog::registerStudent(QString studentID,
                                          QString userName, QString sex, QString className)
{
    int result = database->addStudent(studentID,userName,sex,className);
    if(result == success){
        emit registerSuccess();
        ui->userName->setText(studentID);
        checkSuccess();
    }
    else if(result == updatestatusfailure) {
        emit registerSuccess();
        ui->userName->setFocus();
        QMessageBox::information(this,SETTINGSERVERPROMPT,UPDATESTATUSFAILUREPROMPT,QMessageBox::Ok);
    }
    else{
        QMessageBox::information(this,SETTINGSERVERPROMPT,REGISTERFAILURELPROMPT,QMessageBox::Ok);
    }
}

void TeachingLoginDialog::exitApp()
{
    if(database!=NULL){
        database->closeDB();
    }
    process->execute("unlock.exe");
    hidenStartMenu(false);
    qApp->quit();
}

void TeachingLoginDialog::checkSuccess()
{
    dashBoard->setDataBase(database);
   dashBoard->setHost(serverIP);
    ui->stackedWidget->setCurrentIndex(1);
    startMovie();
    getInfo->start(1000);
}

void TeachingLoginDialog::getServerConnectInfo()
{
    if(dashBoard->connectQuestionServer())
    {
        getInfo->stop();
        database->updateLastClassDate(ui->userName->text());
        database->updateStudentIPaddress(ui->userName->text());
        this->hide();
        dashBoard->setCurrentStudent(ui->userName->text());
        dashBoard->showFullScreen();//FullScreen
    }
}

void TeachingLoginDialog::startMovie()
{
    QMovie *movie = new QMovie(":/appFace/loading");
    ui->loading->setMovie(movie);
    movie->start();
}


void TeachingLoginDialog::hidenStartMenu(bool bShowHide)
{

    HWND    startMenuhWnd;
    WCHAR* wstr = new WCHAR[2 * strlen( "Shell_TrayWnd") + 2];
    MultiByteToWideChar( CP_ACP, 0,  "Shell_TrayWnd", -1, wstr, 2 * (int )strlen(  "Shell_TrayWnd" ) + 2 );
    startMenuhWnd = GetDlgItem(FindWindow(wstr, NULL), ID_STARTBUTTON);

    ShowWindow(startMenuhWnd, bShowHide ? SW_HIDE : SW_SHOW);
    UpdateWindow(startMenuhWnd);

    HWND    toolbarhWnd;
    toolbarhWnd = FindWindow(wstr, NULL);
    ShowWindow(toolbarhWnd, bShowHide ?  SW_HIDE: SW_SHOW);
    UpdateWindow(toolbarhWnd);
}
