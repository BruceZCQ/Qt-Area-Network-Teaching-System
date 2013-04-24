#include "videoview.h"
#include "ui_videoview.h"

VideoView::VideoView(QWidget *parent) :
    QWidget(parent),
    ui(new Ui::VideoView)
{
    ui->setupUi(this);
    QPixmap pix;
    pix.load("resource/viewvideobg.jpg",0,Qt::AvoidDither | Qt::ThresholdAlphaDither | Qt::ThresholdDither);
    resize(pix.size());
    setMask(pix.mask());
    process = new QProcess;
    createActions();
}

VideoView::~VideoView()
{
    delete ui;
}

void VideoView::createActions(){
    connect(ui->jdk,SIGNAL(pressed()),SLOT(chooseCurrentVideo()));
    connect(ui->tomcat,SIGNAL(pressed()),SLOT(chooseCurrentVideo()));
    connect(ui->dw,SIGNAL(pressed()),SLOT(chooseCurrentVideo()));
    connect(ui->ide,SIGNAL(pressed()),SLOT(chooseCurrentVideo()));
    connect(ui->ex1_1,SIGNAL(pressed()),SLOT(chooseCurrentVideo()));
    connect(ui->firstweb,SIGNAL(pressed()),SLOT(chooseCurrentVideo()));
    connect(ui->jbscope,SIGNAL(pressed()),SLOT(chooseCurrentVideo()));
    connect(ui->jdbcex6_1,SIGNAL(pressed()),SLOT(chooseCurrentVideo()));
    connect(ui->jdbcex6_4,SIGNAL(pressed()),SLOT(chooseCurrentVideo()));
    connect(ui->jdbcex6_5,SIGNAL(pressed()),SLOT(chooseCurrentVideo()));
    connect(ui->jdbcex6_6,SIGNAL(pressed()),SLOT(chooseCurrentVideo()));
    connect(ui->jdbcsqlserver,SIGNAL(pressed()),SLOT(chooseCurrentVideo()));
    connect(ui->jspex3_11,SIGNAL(pressed()),SLOT(chooseCurrentVideo()));
    connect(ui->jspex2_1,SIGNAL(pressed()),SLOT(chooseCurrentVideo()));
    connect(ui->jspex2_2,SIGNAL(pressed()),SLOT(chooseCurrentVideo()));
    connect(ui->jspex2_7,SIGNAL(pressed()),SLOT(chooseCurrentVideo()));
    connect(ui->servlet,SIGNAL(pressed()),SLOT(chooseCurrentVideo()));
    connect(ui->jbaddjar,SIGNAL(pressed()),SLOT(chooseCurrentVideo()));
    connect(ui->el,SIGNAL(pressed()),SLOT(chooseCurrentVideo()));
    connect(ui->exitBtn,SIGNAL(clicked()),SLOT(close()));
}
void VideoView::setBasePath(QString basePath)
{
    this->basePath = QString();
    QStringList pathList = basePath.split(QRegExp("/"));
    for(int index=0;index<pathList.size();index++){
        this->basePath += pathList.at(index)+"\\";
    }
}


void VideoView::chooseCurrentVideo()
{
    currentVideo = QString();
    if(ui->jdk->isDown()){
        currentVideo = "jdk.exe\"";
    }
    if(ui->tomcat->isDown()){
        currentVideo = "tomcat.exe\"";
    }
    if(ui->dw->isDown()){
        currentVideo = "dw.exe\"";
    }
    if(ui->ide->isDown()){
        currentVideo = "ide.exe\"";
    }
    if(ui->ex1_1->isDown()){
        currentVideo = "firstexam.exe\"";
    }
    if(ui->firstweb->isDown()){
        currentVideo = "firstweb.exe\"";
    }
    if(ui->jbscope->isDown()){
        currentVideo = "jbscope.exe\"";
    }
    if(ui->jdbcex6_1->isDown()){
        currentVideo = "jdbcaccessdba.exe\"";
    }
    if(ui->jdbcex6_4->isDown()){
        currentVideo = "jdbcaccessdbb.exe\"";
    }
    if(ui->jdbcex6_5->isDown()){
        currentVideo =  "jdbcaccessdbc.exe\"";
    }
    if(ui->jdbcex6_6->isDown()){
        currentVideo =  "jdbcaccessdbd.exe\"";
    }
    if(ui->jdbcsqlserver->isDown()){
        currentVideo =  "jdbcaccesssqlserver.exe\"";
    }
    if(ui->jspex3_11->isDown()){
         currentVideo =  "jspconcealedobject.exe\"";
    }
    if(ui->jspex2_1->isDown()){
      currentVideo =  "jspelementa.exe\"";
    }
    if(ui->jspex2_2->isDown()){
         currentVideo =  "jspelementb.exe\"";
    }
    if(ui->jspex2_7->isDown()){
         currentVideo =  "jspelementc.exe\"";
    }
    if(ui->servlet->isDown()){
         currentVideo =  "servlet.exe\"";
    }
    if(ui->jbaddjar->isDown()){
       currentVideo =  "addjar.exe\"";
    }
    if(ui->el->isDown()){
      currentVideo =  "el.exe\"";
    }
    startVideo();
}

void VideoView::startVideo()
{
    process->start("\""+this->basePath+"\\"+currentVideo);
}

void VideoView::paintEvent(QPaintEvent *)
{
    QPainter painter(this);
    painter.drawPixmap(0,0,QPixmap("resource/viewvideobg.jpg"));
}
