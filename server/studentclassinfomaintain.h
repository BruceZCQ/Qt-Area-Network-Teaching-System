#ifndef STUDENTCLASSINFOMAINTAIN_H
#define STUDENTCLASSINFOMAINTAIN_H

#include <QtCore>
#include <QtGui>
#include "teachingroomstudents.h"
#include "teachingroomclass.h"
#include "serverconst.h"

namespace Ui {
class StudentClassInfoMaintain;
}

class StudentClassInfoMaintain : public QMainWindow
{
    Q_OBJECT
    
public:
    explicit StudentClassInfoMaintain(QWidget *parent = 0);
    ~StudentClassInfoMaintain();
    void setClassMaintainItem(TeachingRoomClass *trClass);
    QTreeWidgetItem* setStudentRootItem(TeachingRoomClass *trClass);
    void setStudentMaintainItem(QTreeWidgetItem *root,TeachingRoomStudents *trStudent);
    void createActions();
    //clear list
    void clearList();
    //init the index data
    void init();
    //set column width
    void setColumnWidth();
    //set student row
    void setStudentRows(int rows);
    void addStudentItem(int row, TeachingRoomStudents *student);
    void initClassItemList();
private slots:
    void setCurrentIndex(int);
    void setCurrentClassInClassMaintain(QTreeWidgetItem *item,int column);
    void setCurrentClassInStudentMaintain(QTreeWidgetItem *item,int column);
    void editClassInfoSlot();
    void addClassInfoSlot();
private:
    Ui::StudentClassInfoMaintain *ui;
    int currentIndex;
    int tempIndex;
    void studentMaintain(QString currentStudent);
    QHash<QString,TeachingRoomStudents*> studentItemList;
    QHash<QString,TeachingRoomClass*> classItemList;
signals:
    void refreshData();
    void clickRootItem(QString rootClassName);
};

#endif // STUDENTCLASSINFOMAINTAIN_H
