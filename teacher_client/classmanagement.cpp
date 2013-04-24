#include <QtCore>
#include <QtGui>
#include "classmanagement.h"
#include "constvar.h"
#include "ui_classmanagement.h"

ClassManagementDialog::ClassManagementDialog(QWidget *parent) :
    QDialog(parent),
    ui(new Ui::ClassManagementDialog)
{
    ui->setupUi(this);
   this->setWindowFlags(Qt::WType_TopLevel|Qt::WStyle_StaysOnTop |Qt::WindowTitleHint);
    setMouseTracking(true);
    ui->tableWidget->setColumnWidth(0,150);
    ui->tableWidget->setColumnWidth(1,80);
    ui->tableWidget->setColumnWidth(2,70);
    //  ui->tableWidget->viewport()->installEventFilter(this);
    connect(ui->addClassBtn,SIGNAL(clicked()),this,SLOT(slotNewClassInfo()));
    connect(ui->tableWidget,SIGNAL(cellPressed(int,int)),this,SLOT(manageClass(int,int)));
}

ClassManagementDialog::~ClassManagementDialog()
{
    delete ui;
}

void ClassManagementDialog::setClassCount(int classCount)
{
    ui->tableWidget->setRowCount(classCount);
}

void ClassManagementDialog::setClassItems(int rowIndex, int columnIndex,TeachingRoomClass *currentClass)
{
    QString itemText;
    if(columnIndex == 0){
        itemText = currentClass->getClassName();
    }
    else{
        itemText = currentClass->getClassStudentsCount()+STUDENTCOUNTUNIT;
    }
    QTableWidgetItem *item = new QTableWidgetItem(itemText);
    item->setTextAlignment(Qt::AlignHCenter);
    ui->tableWidget->setItem(rowIndex,columnIndex,item);
}

void ClassManagementDialog::setManageBtn(int rowIndex)
{
    QTableWidgetItem *manageItem = new QTableWidgetItem(QIcon(":/appFace/deleteclass"),DELETECLASS);
    ui->tableWidget->setItem(rowIndex,2,manageItem);
}

void ClassManagementDialog::manageClass(int row, int column){
    if(column == 2){
        switch(QMessageBox::question(this,SYSTEMPROMPT,DELETECLASSPROMPT+ui->tableWidget->item(row,0)->text(),
                                     QMessageBox::Ok|QMessageBox::Cancel,QMessageBox::Cancel)){
        case QMessageBox::Ok:
        {
            emit deleteClassbyName(ui->tableWidget->item(row,0)->text());
            this->update();
            this->close();
        }
        break;
        case QMessageBox::Cancel:{
        }
        break;
        default:
            break;
        }
    }
    /*
    if(event->type() == QEvent::MouseButtonPress){
        QMouseEvent *mouseEvent = static_cast<QMouseEvent*>(event);
        QMenu *onContentMenu = new QMenu;
        if(mouseEvent->button() == Qt::LeftButton && column==2){
            QAction *classManageAction = new QAction(QIcon(":/appFace/studentmm"),ui->tableWidget->item(row,0)->text(),this);
            onContentMenu->addAction(classManageAction);
        }
        onContentMenu->exec(mouseEvent->globalPos());
    }
    */
}

void ClassManagementDialog::slotNewClassInfo()
{
    emit emitNewClassInfo(ui->classNameText->text(),ui->studentCount->text());
}

void ClassManagementDialog::addNewClassSuccess()
{
    ui->classNameText->setText(CLASSDEFAULTNAME);
    ui->studentCount->setValue(30);
    ui->tabWidget->setCurrentIndex(0);
    this->accept();
}

/*
bool ClassManagementDialog::eventFilter(QObject *o, QEvent *e)
{
    event = e;
    return QDialog::eventFilter(o,event);
}
*/

