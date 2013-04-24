#include "studentclassinfomaintain.h"
#include "ui_studentclassinfomaintain.h"
#include "serverstyle.h"


StudentClassInfoMaintain::StudentClassInfoMaintain(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::StudentClassInfoMaintain)
{
    ui->setupUi(this);
    init();
    createActions();
}

StudentClassInfoMaintain::~StudentClassInfoMaintain()
{
    delete ui;
    studentItemList.clear();
    classItemList.clear();
}

void StudentClassInfoMaintain::setClassMaintainItem(TeachingRoomClass *trClass)
{
    QString trClassName = trClass->getClassName();//get class Name
    QString trClassStudentsCount = trClass->getClassStudentsCount();
    QTreeWidgetItem *currentClass = new QTreeWidgetItem(ui->classList,CLASS_ITEM);
    //set text
    QString classInfo = trClassName +"   "+trClassStudentsCount+CLASSCOUNTUNIT;
    currentClass->setText(0,classInfo);
    classItemList.insert(classInfo,trClass);
}
//set root item
QTreeWidgetItem* StudentClassInfoMaintain::setStudentRootItem(TeachingRoomClass *trClass)
{
    QString trClassName = trClass->getClassName();//get class Name
    QTreeWidgetItem *currentClass = new QTreeWidgetItem(ui->studentsList,CLASS_ITEM);
    //set text
    currentClass->setText(0,trClassName);
    currentClass->setExpanded(true);
    return currentClass;
}
//set root's child
void StudentClassInfoMaintain::setStudentMaintainItem(QTreeWidgetItem *root,TeachingRoomStudents *trStudent)
{
    QString trStudentName = trStudent->getStudentName();//get student Name
    QTreeWidgetItem *currentStudent = new QTreeWidgetItem(root,STUDENT_ITEM);
    //set text
    currentStudent->setText(0,trStudentName);
    //add student to studentitemlist
    studentItemList.insert(trStudentName,trStudent);
}

//conn the signal and slot
void StudentClassInfoMaintain::createActions()
{
    //change the maintain theme
    connect(ui->chooseMaintain,SIGNAL(currentChanged(int)),
            this,SLOT(setCurrentIndex(int)));
    // reget the data from database
    connect(ui->refreshBtn,SIGNAL(clicked()),
            this,SIGNAL(refreshData()));
    //set current class in class maintain
    connect(ui->classList,SIGNAL(itemClicked(QTreeWidgetItem*,int)),
            this,SLOT(setCurrentClassInClassMaintain(QTreeWidgetItem*,int)));
    //set current class in student maintain
    connect(ui->studentsList,SIGNAL(itemClicked(QTreeWidgetItem*,int)),
            this,SLOT(setCurrentClassInStudentMaintain(QTreeWidgetItem*,int)));
    //edit class
    connect(ui->editBtn,SIGNAL(clicked()),
            this,SLOT(editClassInfoSlot()));
    //add new class
    connect(ui->newBtn,SIGNAL(clicked()),
            this,SLOT(addClassInfoSlot()));

}
//clear the list
void StudentClassInfoMaintain::clearList()
{
    ui->classList->clear();
    ui->studentsList->clear();
    studentItemList.clear();
    classItemList.clear();
    ui->className->clear();
}

//init data
void StudentClassInfoMaintain::init()
{
    //unused
    currentIndex = 0;
    tempIndex = 0;
    studentItemList.clear();
    classItemList.clear();
    //set style
    ServerStyle *style = new ServerStyle();
    style->styleNoWork(this);
    //set column width
    setColumnWidth();
}

void StudentClassInfoMaintain::setColumnWidth()
{
    ui->studentInfoWidget->setColumnWidth(TABLEWIDGETITEMROW,TABLEWIDGETITEMWIDTH);
}

//set student list rows
void StudentClassInfoMaintain::setStudentRows(int rows)
{
    ui->studentInfoWidget->setRowCount(rows);
}
//add student to the student table widget
void StudentClassInfoMaintain::addStudentItem(int row, TeachingRoomStudents *student)
{
    QTableWidgetItem *studentIDItem = new QTableWidgetItem(student->getStudentID());
    studentIDItem->setTextAlignment(Qt::AlignHCenter|Qt::AlignBottom);//hcenter and buttom
    ui->studentInfoWidget->setItem(row,0,studentIDItem);
    QTableWidgetItem *studentNameItem = new QTableWidgetItem(student->getStudentName());
    studentNameItem->setTextAlignment(Qt::AlignHCenter|Qt::AlignBottom);//hcenter and buttom
    ui->studentInfoWidget->setItem(row,1,studentNameItem);
    QTableWidgetItem *studentClassItem = new QTableWidgetItem(student->getClassMajor());
    studentClassItem->setTextAlignment(Qt::AlignHCenter|Qt::AlignBottom);//hcenter and buttom
    ui->studentInfoWidget->setItem(row,2,studentClassItem);
    QTableWidgetItem *studentClassCountItem = new QTableWidgetItem(student->getClassCount());
    studentClassCountItem->setTextAlignment(Qt::AlignHCenter|Qt::AlignBottom);//hcenter and buttom
    ui->studentInfoWidget->setItem(row,3,studentClassCountItem);
    QTableWidgetItem *studentGradeItem = new QTableWidgetItem(student->getStudentScore());
    studentGradeItem->setTextAlignment(Qt::AlignHCenter|Qt::AlignBottom);//hcenter and buttom
    ui->studentInfoWidget->setItem(row,4,studentGradeItem);
}
//init class item
void StudentClassInfoMaintain::initClassItemList()
{
    QList<TeachingRoomClass*> classList = classItemList.values();
    int classCount = classList.size();
    for(int index=0; index<classCount; index++){
        QString className = classList.at(index)->getClassName();
        ui->className_2->addItem(className);
    }
}

//change the toolbox index
void StudentClassInfoMaintain::setCurrentIndex(int index)
{
    if(tempIndex==1 && currentIndex==0){
        currentIndex=1;
        tempIndex=0;
    }
    if(index==1 && currentIndex==0){
        currentIndex = 0;
    }
    if(index==1 && currentIndex==1){
        currentIndex = 1;
    }
    if(index==0 && currentIndex==0){
        currentIndex=0;
    }
    if(index==0 && currentIndex==1){
        tempIndex = 1;
        currentIndex=0;
    }
    ui->stackedWidget->setCurrentIndex(index+currentIndex);
}
//set current class
void StudentClassInfoMaintain::setCurrentClassInClassMaintain(QTreeWidgetItem *item,int column)
{
    ui->className->setReadOnly(true);
    ui->studentCount->setReadOnly(true);
    ui->submitBtn->setEnabled(false);
    TeachingRoomClass *currentClass = classItemList.value(item->text(column));
    ui->className->setText(currentClass->getClassName());
    ui->studentCount->setValue(currentClass->getClassStudentsCount().toInt());
    //set title
    ui->title->setText(EDITCLASSINFOTITLE);
}

void StudentClassInfoMaintain::setCurrentClassInStudentMaintain(QTreeWidgetItem *item, int column)
{
    if(item->type() == CLASS_ITEM){//current click item txt :class name
        ui->stackedWidget->setCurrentIndex(1);
        currentIndex = 0;
        emit clickRootItem(item->text(column));
    }
    else{//show maintain student
        ui->stackedWidget->setCurrentIndex(2);
        currentIndex = 1;
        //set current item edit icon
        item->setIcon(0,QIcon(":/server/theme/edit"));
        studentMaintain(item->text(column));
    }
}

//edit current class info
void StudentClassInfoMaintain::editClassInfoSlot()
{
    ui->className->setReadOnly(false);
    ui->studentCount->setReadOnly(false);
    ui->submitBtn->setEnabled(true);
}

//add new class info
void StudentClassInfoMaintain::addClassInfoSlot()
{
    //setting title
    ui->title->setText(ADDCLASSINFOTITLE);
    //setting class name
    ui->className->setText(NEWCLASSNAME);
    ui->className->setFocus();
    ui->className->setReadOnly(false);
    //setting class count
    ui->studentCount->setValue(NEWCLASSCOUNT);
    ui->studentCount->setReadOnly(false);
    ui->submitBtn->setEnabled(true);
}


void StudentClassInfoMaintain::studentMaintain(QString currentStudent)
{
    ui->studentName->setText(currentStudent);
    TeachingRoomStudents *currentstudent = studentItemList.value(currentStudent);
    ui->studentID->setText(currentstudent->getStudentID());
    QString className = currentstudent->getClassMajor();
    ui->className_2->setCurrentIndex(ui->className_2->findText(className));
    ui->classCount->setValue(currentstudent->getClassCount().toInt());
    ui->studentGrade->setValue(currentstudent->getStudentScore().toInt());
}
