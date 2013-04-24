#include "pptwin.h"
#include "ui_pptwin.h"

PPTView::PPTView(QWidget *parent) :
    QDialog(parent),
    ui(new Ui::PPTWin)
{
    ui->setupUi(this);
    ui->pptView->settings()->setAttribute(QWebSettings::JavascriptEnabled,true);
    ui->pptView->settings()->setAttribute(QWebSettings::PluginsEnabled,true);
    ui->pptView->setContextMenuPolicy(Qt::NoContextMenu);

    QDesktopWidget* desktopWidget = QApplication::desktop();
    QRect screenRect = desktopWidget->screenGeometry();

    screenWidth = screenRect.width();
    screenHeigth = screenRect.height();

    createActions();
}

PPTView::~PPTView()
{
    delete ui;
}

void PPTView::keyPressEvent(QKeyEvent *e)
{
    if(e->key() == Qt::Key_Escape){
        if(this->isFullScreen()){
            ui->pptList->show();
            showNormal();
        }
    }
}

void PPTView::setHost(QString hostAddress)
{
    this->hostAddress = "http://"+hostAddress+":8188/courseppt/";
    setCurrentPPT(1);
    ui->pptList->topLevelItem(0)->setSelected(true);
}

void PPTView::createActions()
{
    //reload ppt
    connect(ui->reload,SIGNAL(clicked()),this,SLOT(reloadPPT()));
    connect(ui->exitPPt,SIGNAL(clicked()),SLOT(close()));
    connect(ui->pptList,SIGNAL(itemPressed(QTreeWidgetItem*,int)),this,SLOT(pptPressed(QTreeWidgetItem*,int)));
}

void PPTView::initPPTList(int pptID,QString chapterName)
{
   QTreeWidgetItem* item =new  QTreeWidgetItem(ui->pptList);
   item->setText(0,chapterName);
   item->setIcon(0,QIcon(":/appFace/viewppt"));
   pptList.insert(pptID,chapterName);
}

void PPTView::pptPressed(QTreeWidgetItem* item,int c){
    int id = pptList.key(item->text(c));
    setCurrentPPT(id);
}

void PPTView::clearData()
{
    ui->pptList->clear();
    pptList.clear();
}


void PPTView::setCurrentPPT(int courseID)
{
    ui->pptView->setUrl(QUrl( this->hostAddress+"index.jsp?id="+QString::number(courseID)
                              +"&w="+QString::number(screenWidth-260)+"&h="+QString::number(screenHeigth-140)+""));
    this->courseID = courseID;
}

void PPTView::reloadPPT()
{
    setCurrentPPT(courseID);
}



