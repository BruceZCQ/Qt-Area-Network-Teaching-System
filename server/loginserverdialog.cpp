#include "loginserverdialog.h"
#include "ui_loginserverdialog.h"

LoginServerDialog::LoginServerDialog(QWidget *parent) :
    QDialog(parent),
    ui(new Ui::LoginServerDialog)
{
    //change profile
    ui->setupUi(this);
    setWindowFlags(Qt::WindowTitleHint);
    //setting style
    ServerStyle *style = new ServerStyle();
    style->styleWork(this);
    dashboard = new ServerDashboard;
    style->styleWork(dashboard);
    settingServer = new ServerSettingDialog;
    style->styleWork(settingServer);
    database = NULL;
    //create actions
    createActions();
    setDefaultFocus();
}

LoginServerDialog::~LoginServerDialog()
{
    delete ui;
    delete dashboard;
    delete settingServer;
    delete database;
}
//show dashboard slot
void LoginServerDialog::showDashboardSlot()
{
    //check the server conf
    //get conf data success and check user info is completion
    if(getServerSettingConfData() && checkUserInfo()){
        //get the database handle
        database = new ServerDataBase(serverIP,serverPort);
        //get the database connect result
        //success todo:check the user
        if(database->getConnectionResult()){
            if(database->checkUser(ui->passwordEdit->text()) == true){//check user success
                this->close();
                dashboard->setDatabaseHandle(database);//set the database and init all data
                dashboard->showMaximized();
            }
            else{
                database->closeDB();
                printErrorPrompt();
            }
        }
    }
}
//create action ,connect the signals and slots
void LoginServerDialog::createActions()
{
    //connect the login btn to the dashboard
    connect(ui->loginBtn,SIGNAL(clicked()),
            this,SLOT(showDashboardSlot()));
    //connect the setting btn to the server setting diaglog
    connect(ui->settingBtn,SIGNAL(clicked()),
            this,SLOT(showSettingServerSlot()));
    //connect setting Server dialog ,while the dialog emit the imclosed signals
    connect(settingServer,SIGNAL(imClosed()),
            this,SLOT(setDefaultFocus()));
    //close database while the dashboard emit close signal
    connect(dashboard,SIGNAL(closedDashboard()),
            this,SLOT(closeDB()));
}
//show the setting server slot
void LoginServerDialog::showSettingServerSlot()
{
    settingServer->setDefaultFocus();
    settingServer->exec();
}

//set default focus in userName Edit
void LoginServerDialog::setDefaultFocus(){
    ui->passwordEdit->setFocus();
}

//get server ip and port
bool LoginServerDialog::getServerSettingConfData()
{
    QSettings teachingroomsetting("teachingroomServer",qAppName());
    teachingroomsetting.beginGroup(tr("SettingServer"));
    serverIP = teachingroomsetting.value(tr("ip")).toString();
    serverPort = teachingroomsetting.value(tr("port")).toString();
    teachingroomsetting.endGroup();
    if(serverIP.isEmpty()||serverIP.isNull()||serverPort.isEmpty()||serverPort.isNull()){
        QMessageBox::question(this,SYSTEMPROMPT,SETTINGSERVERPROMPT,QMessageBox::Ok);
        setDefaultFocus();
        return false;
    }
    else{
        return true;
    }
}
//check info is completion or not and set focus
bool LoginServerDialog::setCurrentFocus()
{
    switch(infoIsCompletion()){
    case NAMEINFOINCOMPLETION:{//username incompletion
        ui->userNameEdit->setFocus();
        return false;
    }
    break;
    case PASSWORDINFOINCOMPLETION:{//password incompletion
        setDefaultFocus();
        return false;
    }
    break;
    case INFOCOMPLETION:{ //info completion
        return true;
    }
    break;
    default:{
        return true;
    }
    }
}

//check info is completion or not
int LoginServerDialog::infoIsCompletion(){
    //username incompletion return 10
    if(ui->userNameEdit->text().isEmpty()
            ||ui->userNameEdit->text().isNull()){
        return NAMEINFOINCOMPLETION;
    } //password incompletion return 11
    else if(ui->passwordEdit->text().isEmpty()
            || ui->passwordEdit->text().isNull()){
        return PASSWORDINFOINCOMPLETION;

    } //info completion return 12
    else{
        return INFOCOMPLETION;
    }
}
//check info indriect ,and print the prompt
bool LoginServerDialog::checkUserInfo()
{
    if(setCurrentFocus()){
        return true;
    }
    else{
        QMessageBox::information(this,SYSTEMPROMPT,INFOINCOMPLETIONPROMPT,QMessageBox::Ok);
        return false;
    }
}
//close databse
void LoginServerDialog::closeDB()
{
    database->closeDB();
    database = NULL;
    delete database;
//    if(database != NULL){
//        delete database;
    //    }
}

void LoginServerDialog::printErrorPrompt()
{
    QMessageBox::information(this,SYSTEMPROMPT,PASSWORDINCORRECT,QMessageBox::Ok);
}
