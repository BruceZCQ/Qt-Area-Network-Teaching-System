#include "studentmanagement.h"
#include "ui_studentmanagement.h"
#include "constvar.h"

StudentManagement::StudentManagement(QWidget *parent) :
    QDialog(parent),
    ui(new Ui::StudentManagement)
{
    ui->setupUi(this);
    setWindowFlags(Qt::WindowTitleHint);
    classNameList.clear();
    studentsList.clear();
    ui->studentList->topLevelItem(1)->setExpanded(true);
    connect(ui->studentList,SIGNAL(itemPressed(QTreeWidgetItem*,int)),
            this,SLOT(selectClass(QTreeWidgetItem*,int)));
    connect(ui->refreshBtn,SIGNAL(clicked()),this,SLOT(slotRefreshData()));
}

StudentManagement::~StudentManagement()
{
    delete ui;
    classNameList.clear();
    studentsList.clear();
}


void StudentManagement::selectClass(QTreeWidgetItem *item,int column){
    int index = ui->studentList->indexOfTopLevelItem(item);
    if(item->type() == CLASS_ITEM){
        ui->className->setText(item->text(column));
    }
    else{
        if(index==0){
            emit emitAddClass();
        }
        ui->className->setText(ALLSTUDENTS);
    }
    currentClass = item->text(column);
    setStudentList(item->text(column));
}

void StudentManagement::setClassList(QStringList classNameList)
{
    this->classNameList = classNameList;
        QTreeWidgetItem *rootItem = ui->studentList->topLevelItem(1);
        for(int i=0;i<this->classNameList.size();i++)
        (new QTreeWidgetItem(rootItem,CLASS_ITEM))->setText(0,classNameList.at(i));
}

void StudentManagement::addStudentItem(QString className, QList<TeachingRoomStudents*> studentList)
{
    studentsList.insert(className,studentList);
}

void StudentManagement::exec()
{
    setStudentList();
    QDialog::exec();
}

void StudentManagement::setStudentList(QString className)
{
    QList<TeachingRoomStudents*> list = studentsList.value(className);
    int count = list.size();
    ui->studentInfoList->setRowCount(count);
    QStringList lableList;
    for(int i=0; i<count; i++){
        //setting vertical header item text
        lableList << ">";
        ui->studentInfoList->setVerticalHeaderLabels(lableList);
        //setting student id
        QLabel *studentIDITem = new QLabel;
        studentIDITem->setText(list.at(i)->getStudentID());
        ui->studentInfoList->setCellWidget(i,0,studentIDITem);
        ui->studentInfoList->setColumnWidth(0,100);
        //setting stuent name
        QTableWidgetItem *studentNameITem = new QTableWidgetItem(list.at(i)->getStudentName());
        ui->studentInfoList->setItem(i,1,studentNameITem);
        ui->studentInfoList->setColumnWidth(1,100);
        //setting stuent sex
        QTableWidgetItem *studentSexITem = new QTableWidgetItem(list.at(i)->getStudentSex());
        ui->studentInfoList->setItem(i,2,studentSexITem);
        ui->studentInfoList->setColumnWidth(2,50);
        //setting stuent class
        QComboBox *classBox = new QComboBox;
        classBox->addItems(classNameList);
        ui->studentInfoList->setCellWidget(i,3,classBox);
        ui->studentInfoList->setColumnWidth(3,180);
        int index = classNameList.indexOf(className);
        classBox->setCurrentIndex(index);
        //setting stuent score
        QTableWidgetItem *studentScoreITem = new QTableWidgetItem(list.at(i)->getStudentScore());
        ui->studentInfoList->setItem(i,4,studentScoreITem);
        ui->studentInfoList->setColumnWidth(4,50);
    }
}

void StudentManagement::slotRefreshData()
{
    setStudentList(currentClass);
    emit refreshData();
}

