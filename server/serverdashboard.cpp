#include "serverdashboard.h"
#include "ui_serverdashboard.h"
#include "customtabwidget.h"
#include "lib/datatransferserver.h"

ServerDashboard::ServerDashboard(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::ServerDashboard)
{
    ui->setupUi(this);
    studentClassMaintainWin = new StudentClassInfoMaintain;
    classList.clear();
    studentList.clear();
    createActions();
}

ServerDashboard::~ServerDashboard()
{
    delete ui;
    classList.clear();
    studentList.clear();
    delete studentClassMaintainWin;
}

void ServerDashboard::addTab()
{
}

void ServerDashboard::quitApp()
{
    qApp->exit(0);
}

void ServerDashboard::refreshMaintainData()
{
    //init data from database
    initData();
    studentClassInfoMaintainAddItemSlot();
}

//maintain the student and class info: studentClassMaintain Button slot
void ServerDashboard::studentClassInfoMaintainAddItemSlot()
{
    //add tab to the guide
    ui->dashboardCenter->addTab(studentClassMaintainWin,QIcon(":/server/theme/maintain"),STUDENTCLASSINFOMAINTAIN);
    //clear the student and class maintain list:remove the item
    studentClassMaintainWin->clearList();
    // add the class item (data by classlist) to the studentClassMainwin class and studnet list
    for(int index=0;index<classList.count();index++){
        studentClassMaintainWin->setClassMaintainItem(classList.at(index));
    }
    // add the student item (data by studentList) to the studentClassMainwin class and studnet list
    for(int index=0;index<classList.count();index++){
        QTreeWidgetItem *root = studentClassMaintainWin->setStudentRootItem(classList.at(index));
        QString className = classList.at(index)->getClassName();
        int studentCount = getStudentsCountByClassName(className);
        for(int nStudent=0; nStudent<studentCount; nStudent++){
            studentClassMaintainWin->setStudentMaintainItem(root,studentList.at(nStudent));
        }
    }
    //add item to the tabwidget
    int studentCount = getStudentsCountByClassName(currentClassName);
    for(int index=0; index<studentCount; index++){
        TeachingRoomStudents *student
                = getStudentsByClassFromDB(currentClassName,index);
        studentClassMaintainWin->addStudentItem(index,student);
    }
    //init class list data
    studentClassMaintainWin->initClassItemList();
}


//init data from database
void ServerDashboard::initData()
{
    //init the data from database
    this->databaseHandle->initData();
    //init the class list
    initClassList();
    currentClassName = this->databaseHandle->getFirstClassName();
    //init student list
    initStudentList(currentClassName);
}

//init class List
void ServerDashboard::initClassList()
{
    classList.clear();
    int classCount =  this->databaseHandle->getClassCount();
    for(int index=0; index<classCount; index++){
        TeachingRoomClass *currentClass = this->databaseHandle->getClassFromDB(index);
        classList.append(currentClass);
    }
}

//set current class student list
void ServerDashboard::setCurrentClass(QString className)
{
    currentClassName = className;
    initStudentList(currentClassName);
    studentClassInfoMaintainAddItemSlot();
}
// init student list
void ServerDashboard::initStudentList(QString className)
{
    int studentCount = getStudentsCountByClassName(className);
    //set student list count
    studentClassMaintainWin->setStudentRows(studentCount);
}

int ServerDashboard::getStudentsCountByClassName(QString className){
    studentList.clear();
    int studentCount = this->databaseHandle->getStudentsCountByClassName(className);
    for(int index=0; index<studentCount; index++){
        TeachingRoomStudents *currentStudent
                = this->databaseHandle->getStudentsByClassFromDB(className,index);
        studentList.append(currentStudent);
    }
    return studentCount;
}

TeachingRoomStudents *ServerDashboard::getStudentsByClassFromDB(QString className, int index)
{
    return this->databaseHandle->getStudentsByClassFromDB(className,index);
}

//connect signals and slots
void ServerDashboard::createActions()
{
    //quit app
    connect(ui->quitAction,SIGNAL(triggered()),
            this,SLOT(quitApp()));
    //stundetclass maintain add item to the list
    connect(ui->studentClassInfoMaintain,SIGNAL(clicked()),
            this,SLOT(studentClassInfoMaintainAddItemSlot()));
    //refresh student and class list info
    connect(studentClassMaintainWin,SIGNAL(refreshData()),
            this,SLOT(refreshMaintainData()));
    //change the student list in studentmaintain list
    connect(studentClassMaintainWin,SIGNAL(clickRootItem(QString)),
            this,SLOT(setCurrentClass(QString)));
}

//emit the close signal to close database in the logindialog
void ServerDashboard::closeEvent(QCloseEvent *e)
{
    emit closedDashboard();
    e->accept();
}

//set database handle
void ServerDashboard::setDatabaseHandle(ServerDataBase *databaseHandle)
{
    this->databaseHandle = databaseHandle;
    //init the data from databse
    initData();
    //startServer
    startServer();
}

void ServerDashboard::startServer()
{
    DataTransferServer *server = new DataTransferServer;
    server->startListen();
}

