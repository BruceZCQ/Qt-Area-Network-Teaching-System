#include "customtabwidget.h"

CustomTabWidget::CustomTabWidget(QWidget *parent) :
    QTabWidget(parent)
{
    connect(this,SIGNAL(tabCloseRequested(int)),SLOT(removeTab(int)));
    connect(this,SIGNAL(currentChanged(int)),SLOT(setCurrentIndex(int)));
}
//private slot
void CustomTabWidget::removeTab(int index)
{
    setProfileByCount();
    setProfileByIndex(index);
    setProfileByCount();
}

void CustomTabWidget::setProfileByCount()
{
    if(this->count() == 1){
        this->setTabsClosable(false);
    }
    else{
        this->setTabsClosable(true);
    }
}

//remove tab assitant
void CustomTabWidget::setProfileByIndex(int index)
{
    if(index != 0){
        this->setTabsClosable(true);
        QTabWidget::removeTab(index);
    }
    else{
        this->setTabsClosable(false);
    }
}

void CustomTabWidget::addTab(QWidget *widget, const QIcon &icon, const QString &label)
{
    QTabWidget::addTab(widget,icon,label);
    setProfileByCount();
    setCurrentIndex(this->indexOf(widget));
}

void CustomTabWidget::addTab(QWidget *page, const QString &label){
     QTabWidget::addTab(page,label);
     setProfileByCount();
     setCurrentIndex(this->indexOf(page));
}
//private slot
void CustomTabWidget::setCurrentIndex(int index)
{
    QTabWidget::setCurrentIndex(index);
    setTabsClosable(index);
}

void CustomTabWidget::setTabsClosable(bool boo){
    QTabWidget::setTabsClosable(boo);
}

void CustomTabWidget::setTabsClosable(int index)
{
    if(index == 0){
        this->setTabsClosable(false);
    }
    else{
     this->setTabsClosable(true);
    }
}
