#include "studentdashboard.h"
#include "ui_studentdashboard.h"

StudentDashBoard::StudentDashBoard(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::StudentDashBoard)
{
    ui->setupUi(this);
    //set style
    Style style;
    style.styleWork(this);
    statusLabel = new QLabel;
    statusLabel->setAlignment(Qt::AlignRight|Qt::AlignBottom);
    ui->statusbar->addWidget(statusLabel,this->width());
    //set timer
    timer = new QTimer;
    messageCheck = new QTimer;
    hasMessage = false;
    broadCastTimer = new QTimer;
    clearBroadCastContent = new QTimer;
    showBroadCastWin = new ShowBroadCastContent;
    clearHelpContent = new QTimer;
    // ppt window
    pptWin = new PPTView;
    //    pptWin->setWindowFlags(Qt::WType_TopLevel|Qt::WStyle_StaysOnTop |Qt::WindowTitleHint);
    //coding win
    codingWin = new CodingWindow;
    codingWin->setWindowFlags(Qt::WType_TopLevel|Qt::WStyle_StaysOnTop |Qt::WindowTitleHint);
    questionWin = new QuestionWindow;
    message = QString(tr("test message from server"));
    socket = new QTcpSocket;
    videoViewWin = new VideoView;
    //  videoViewWin->setWindowFlags(Qt::WType_TopLevel|Qt::WStyle_StaysOnTop |Qt::WindowTitleHint);
    questionId = 0;
    QPixmap pix;
    pix.load("resource/dashboardbg.jpg",0,Qt::AvoidDither | Qt::ThresholdAlphaDither | Qt::ThresholdDither);
    resize(pix.size());
    setMask(pix.mask());
    createActions();
    createGlobalActions();
    //   showHelpInfo();
}

StudentDashBoard::~StudentDashBoard()
{
    delete ui;
}





void StudentDashBoard::paintEvent(QPaintEvent *)
{
    QPainter painter(this);
    painter.drawPixmap(0,0,QPixmap("resource/dashboardbg.jpg"));
}

void StudentDashBoard::moveEvent(QMoveEvent *e)
{
    e->ignore();
}

void StudentDashBoard::createActions()
{
    //reset system toolbar
    connect(timer,SIGNAL(timeout()),this,SLOT(statusMessage()));
    connect(messageCheck,SIGNAL(timeout()),this,SLOT(newQuestion()));
    connect(broadCastTimer,SIGNAL(timeout()),SLOT(showBroadCastContent()));
    connect(clearHelpContent,SIGNAL(timeout()),ui->label,SLOT(clear()));
    connect(clearHelpContent,SIGNAL(timeout()),clearHelpContent,SLOT(stop()));
    connect(clearBroadCastContent,SIGNAL(timeout()),SLOT(clearBroadCast()));
    connect(clearBroadCastContent,SIGNAL(timeout()),clearBroadCastContent,SLOT(stop()));
    //the head actions
    connect(ui->exit,SIGNAL(clicked()),this,SLOT(quitApp()));
    connect(ui->helpBtn,SIGNAL(clicked()),this,SLOT(showHelpInfo()));
    //viewppt
    connect(ui->viewpptBtn,SIGNAL(clicked()),this,SLOT(viewPPt()));
    //coding
    connect(ui->codingBtn,SIGNAL(clicked()),timer,SLOT(stop()));
    connect(ui->codingBtn,SIGNAL(clicked()),codingWin,SLOT(showFullScreen()));
    connect(codingWin,SIGNAL(exitCoding()),SLOT(showFullScreen()));
    connect(codingWin,SIGNAL(serverStarted()),SLOT(hide()));///???????????????????????????????!!!!!!!!!!!!!!!!!
    //question
    connect(ui->questionViewBtn,SIGNAL(clicked()),this,SLOT(exerciseQuestion()));
    //socket to server
    connect(socket, SIGNAL( readyRead()), SLOT(receiveQuestionID()));
    // connect(qApp,SIGNAL(aboutToQuit()),SLOT(sendStudentStatus()));
    //video view
    connect(ui->viewVideoBtn,SIGNAL(clicked()),this,SLOT(viewVideos()));
    //refreshdata
    connect(this,SIGNAL(refreshDatabase()),SLOT(refreshDataFromDB()));
}

void StudentDashBoard::createGlobalActions()
{
    QxtGlobalShortcut * screenFullSc = new QxtGlobalShortcut(QKeySequence("CTRL+F"), this);
    connect(screenFullSc, SIGNAL(activated()),this, SLOT(showFullScreen()));
}

void StudentDashBoard::statusMessage()
{
    QString currentDate = QString::number(QDate::currentDate().year())+tr("年" )
            +QString::number(QDate::currentDate().month())+tr("月")
            +QString::number(QDate::currentDate().day())+tr("日") ;
    currentDate = currentDate+QTime::currentTime().toString("  hh:mm:ss");
    if(hasMessage){
        ui->label->setText(message);
    }
    else{
        statusLabel->setText("<span style='color:white'>"+currentDate+"</span>");
    }
}


void StudentDashBoard::showFullScreen()
{
    timer->start(1000);
    messageCheck->start(1000);
    sendStudentStatus();
    QMainWindow::showFullScreen();
}

void StudentDashBoard::showHelpInfo()
{
    ui->label->setText(HELP);
    clearHelpContent->start(3000);
}

void StudentDashBoard::hide()
{
    pptWin->hide();
    codingWin->hide();
    QMainWindow::hide();
}

bool StudentDashBoard::connectQuestionServer()
{
    if(socket->state()  == QAbstractSocket::UnconnectedState){
        socket->connectToHost(serverIP, TRANSFERQUESTION);
    }
    if(socket->state() == QAbstractSocket::ConnectedState){
        return true;
    }
    else{
        return false;
    }
}

void StudentDashBoard::sendStudentStatus()
{
    socket->write(QString("updateStatus\n").toUtf8());
    socket-> waitForBytesWritten(200);////保证关闭时能够准确发送退出信息!!!!!!!!!!!!!!!!!!!!!!!
}

void StudentDashBoard::receiveQuestionID()
{
    while (socket->canReadLine())
    {
        QString line = QString::fromUtf8(socket->readLine()).trimmed();
        //the teacher data format :teacher/studentid/questionid
        //the student data format : student/studentid/questionid/questionanswer
        QStringList messageList = line.split(QRegExp("/"));

        //refreshdata
        if(messageList.at(0) == QString("refreshdata")){
            emit refreshDatabase();
        }
        //data from teachar
        if(messageList.at(0)==QString("teacher")){
            message = RECEIEVEQUESTION;
            //check the studentid
            if(messageList.at(1) == studentID){
                questionId= messageList.at(2).toInt();
            }
            else{
                questionId = 0;
            }
            if(questionId != 0){
                hasMessage = true;
            }
        }//is teacher
        if(messageList.at(0)==QString("broadcast")){
            message = messageList.at(1);
            broadCastTimer->start(100);
            clearBroadCastContent->start(5000);
        }
    }
}

void StudentDashBoard::setDataBase(ServerDataBase *database)
{
    this->database = database;
}

void StudentDashBoard::setHost(QString hostAddress)
{
    serverIP = hostAddress;
    pptWin->setHost(serverIP);
}

void StudentDashBoard::viewPPt()
{
    pptWin->clearData();//clear ppt and point list
    int pptListSize = database->getChapterListSize();
    for(int index=0;index<pptListSize;index++){
        pptWin->initPPTList(database->getChapterIDByIndex(index),database->getChapterNameByIndex(index));
    }
    pptWin->showFullScreen();
}

void StudentDashBoard::quitApp()
{
    if(database->updateStudentStatus(studentID,"off")){
        sendStudentStatus();
        socket->disconnectFromHost();
        socket->close();
        system("stopserver.vbs");
        emit exitApp();
    }
    else{
        QMessageBox::information(this,SETTINGSERVERPROMPT,LOGOUTUPDATESTATUSFAILUREPROMPT,QMessageBox::Ok);
    }
}

void StudentDashBoard::changeMessageState(QString answer)
{
    socket->write(("student/"+studentID+"/"+answer+"\n").toUtf8());
    hasMessage = false;
    message = QString();
    ui->label->setText("");
    messageCheck->start(1000);
}

void StudentDashBoard::newQuestion()
{
    if(hasMessage){
        messageCheck->stop();
        ReceiveQuestion * receiveQuestionWin = new ReceiveQuestion;
        receiveQuestionWin->setQuestion(database->getQuestionByID(questionId));
        connect(receiveQuestionWin,SIGNAL(answerSent(QString)),this,SLOT(changeMessageState(QString)));
        connect(receiveQuestionWin,SIGNAL(answerSent(QString)),receiveQuestionWin,SLOT(accept()));
         connect(receiveQuestionWin,SIGNAL(answerSent(QString)),receiveQuestionWin,SLOT(deleteLater()));
         receiveQuestionWin->exec();
        //   connect(ui->showQuestion,SIGNAL(clicked()),receiveQuestionWin,SLOT(toTop()));
    }
}

void StudentDashBoard::setCurrentStudent(QString studentID)
{
    this->studentID = studentID;
}


//testing found it:data range
void StudentDashBoard::refreshDataFromDB()
{
    database->initData();
}

void StudentDashBoard::exerciseQuestion()
{
    //share the database handle to questionwin
    questionWin->setDatabase(this->database);
    questionWin->showFullScreen();
}

void StudentDashBoard::viewVideos()
{
    QDir dir = QDir(qApp->applicationDirPath());
    qDebug()<<dir.cdUp()<<dir.path()<<qApp->applicationDirPath();
    QString basePath= dir.path()+"/videos";
    videoViewWin->setBasePath(basePath);
    videoViewWin->showFullScreen();
}

void StudentDashBoard::showBroadCastContent()
{
    showBroadCastWin->setContent(message);
    showBroadCastWin->exec();
}

void StudentDashBoard::clearBroadCast(){
    message=QString();
    broadCastTimer->stop();
    if(showBroadCastWin->isVisible()){
        showBroadCastWin->accept();
    }
}
