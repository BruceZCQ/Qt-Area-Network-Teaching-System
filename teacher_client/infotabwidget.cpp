#include "infotabwidget.h"

InfoTabWidget::InfoTabWidget(QWidget *parent) :
    QTabWidget(parent)
{
}

void InfoTabWidget::closeEvent(QCloseEvent *e)
{
    this->clear();
    emit clearList();
    e->accept();
}

void InfoTabWidget::emptyInfoTabWidget()
{
    this->clear();
    this->close();
}
