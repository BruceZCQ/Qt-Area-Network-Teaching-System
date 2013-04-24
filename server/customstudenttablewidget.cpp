#include "customstudenttablewidget.h"

CustomStudentTableWidget::CustomStudentTableWidget(QWidget *parent) :
    QTableWidget(parent)
{
}

void CustomStudentTableWidget::setColumnWidth(int column,int width)
{
    QTableWidget::setColumnWidth(column,width*2);
    QTableWidget::setColumnWidth(column+1,width*4);
    QTableWidget::setColumnWidth(column+2,width*4);
    QTableWidget::setColumnWidth(column+3,width*2);
    QTableWidget::setColumnWidth(column+4,width*2);
}
