#include "mainwindow.h"
#include "constvar.h"
#include "teachingroomstudents.h"
#include "ui_mainwindow.h"
#include "serverstyle.h"

MainWindow::MainWindow(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::MainWindow)
{
    ui->setupUi(this);
    initWindowProfile();
}

MainWindow::~MainWindow()
{
    delete ui;
    delete functionbox;
    delete teachinDB;
    delete classManageMentDialog;
    delete sendQuestion;
    delete infoTabWidget;
    studentInfoList.clear();
}

void MainWindow::initWindowProfile()
{
    QDesktopWidget* desktopWidget = QApplication::desktop();
    screenRect = desktopWidget->screenGeometry();
    int winX = screenRect.width()-width()-WINX_OFFEST;
    this->setGeometry(QRect(winX,30,300,500));
    this->setWindowFlags(Qt::WType_TopLevel|Qt::WStyle_StaysOnTop );
   // ui->menuBar->hide();
    ServerStyle *style = new ServerStyle();
    style->styleWork(ui->tabWidget);//set style
    functionbox = new FunctionBox;
    ui->studenTree->viewport()->installEventFilter(this);
    ui->questionSetList->viewport()->installEventFilter(this);
    sendQuestion = new SendQuestionDialog;
    changePasswordDialog = new ChangePasswordDialog;
    classManageMentDialog = new ClassManagementDialog;
    createQuestionDialog = new CreateQuestion;
    // infoTabWidget
    infoTabWidget = new InfoTabWidget;
    infoTabWidget->setMaximumSize(QSize(630,400));
    infoTabWidget->setMinimumSize(QSize(630,400));
    infoTabWidget->setTabsClosable(true);
    infoTabWidget->setWindowTitle(VIEWINFO);
    infoTabWidget->setWindowIcon(QIcon(":/appFace/viewinfo"));
    studentInfoList.clear();
    //question socket
    socket = new QTcpSocket;
    createActions();
    createGlobalActions();
    setTooltips();
    startMovie();
}

void MainWindow::createActions()
{
    connect(ui->logoutAction,SIGNAL(triggered()),this,SLOT(emitLogoutSignal()));
    connect(ui->quitAction,SIGNAL(triggered()),this,SLOT(quitApp()));
    connect(ui->aboutAction,SIGNAL(triggered()),this,SLOT(about()));
    connect(ui->menuChangeAction,SIGNAL(triggered()),ui->menuBar,SLOT(hide()));
    connect(ui->functionBoxBtn,SIGNAL(clicked()),functionbox,SLOT(show()));
    connect(ui->refreshBtn,SIGNAL(clicked()),this,SLOT(refreshData()));
    //student tree
    connect(ui->studenTree,SIGNAL(itemPressed(QTreeWidgetItem*,int)),this,SLOT(itemPress(QTreeWidgetItem*,int)));
    connect(ui->studenTree,SIGNAL(itemDoubleClicked(QTreeWidgetItem*,int)),this,SLOT(itemDbClick(QTreeWidgetItem*,int)));
    //questionset tree
    connect(ui->questionSetList,SIGNAL(itemPressed(QTreeWidgetItem*,int)),this,SLOT(itemPress(QTreeWidgetItem*,int)));
    connect(ui->questionSetList,SIGNAL(itemDoubleClicked(QTreeWidgetItem*,int)),this,SLOT(itemDbClick(QTreeWidgetItem*,int)));
    //password manage
    connect(ui->changePasswordAction,SIGNAL(triggered()),changePasswordDialog,SLOT(exec()));
    connect(changePasswordDialog,SIGNAL(emitNewPassword(QString)),this,SLOT(emitNewPassword(QString)));
    //class manage
    connect(ui->classManageBtn,SIGNAL(clicked()),this,SLOT(classManage()));
    connect(classManageMentDialog,SIGNAL(emitNewClassInfo(QString,QString)),this,SLOT(addNewClass(QString,QString)));
    connect(this,SIGNAL(addNewClassSuccess()),classManageMentDialog,SLOT(addNewClassSuccess()));
    connect(classManageMentDialog,SIGNAL(deleteClassbyName(QString)),this,SLOT(deleteClassbyName(QString)));
    //send question
    connect(sendQuestion,SIGNAL(refreshQuestionSet()),this,SLOT(refreshData()));
    connect(sendQuestion,SIGNAL(emitNewValue(QString,QString,QString,QString,QString,QString,QString)),
            this,SLOT(updateQuestion(QString,QString,QString,QString,QString,QString,QString)));
    connect(this,SIGNAL(updateQuestionResult(bool)),sendQuestion,SIGNAL(emtUpdateResult(bool)));
    //create question
    connect(ui->createQuestionBtn,SIGNAL(clicked()),createQuestionDialog,SLOT(exec()));
    connect(createQuestionDialog,SIGNAL(refreshChapterList()),this,SLOT(refreshData()));
    connect(createQuestionDialog,SIGNAL(addQuestion(QString,QString,QString,QString,QString,QString)),
            this,SLOT(addQuestion(QString,QString,QString,QString,QString,QString)));
    connect(this,SIGNAL(addQuestionResult(bool)),createQuestionDialog,SIGNAL(addQuestionResult(bool)));
    //viewstudentinfo
    connect(infoTabWidget,SIGNAL(tabCloseRequested(int)),this,SLOT(closeStudentTabWidgetByIndex(int)));
    connect(infoTabWidget,SIGNAL(clearList()),this,SLOT(clearStudenetInfoList()));
    connect(this,SIGNAL(emptyInfoTabWidget()),infoTabWidget,SLOT(emptyInfoTabWidget()));
    //broadCast
    connect(ui->weiBroadcastBtn,SIGNAL(clicked()),SLOT(broadCast()));
    //refresh question list
    connect(ui->refreshQuestionBtn,SIGNAL(clicked()),this,SLOT(refreshData()));
    //socket
    connect(socket, SIGNAL( readyRead()), SLOT(receiveQuestionAnswer()));
    connect(sendQuestion,SIGNAL(sentQuestion(QString)),SLOT(sendQuestionInfo(QString)));
}

void MainWindow::addNewClass(QString className, QString studentCount){
    if(teachinDB->addNewClass(className,studentCount)){
        refreshData();
        QMessageBox::information(this,INSERTNEWCLASSPROMPT,INSERTNEWCLASSSUCCESS,QMessageBox::Ok);
        emit addNewClassSuccess();
    }
    else{
        QMessageBox::information(this,INSERTNEWCLASSPROMPT,INSERTNEWCLASSFAILURE,QMessageBox::Ok);
    }
}

void MainWindow::emitLogoutSignal(){
    ui->studenTree->clear();
    teachinDB->closeDB();
    emit logout();
    this->close();
}

void MainWindow::about(){
    QMessageBox::about(this,ABOUTPROMPT,ABOUTPROMPTMOREINFO);
}

void MainWindow::keyPressEvent(QKeyEvent *e)
{
    if(e->key()==Qt::Key_Alt){
        if(ui->menuBar->isHidden()){
            ui->menuBar->show();
        }
        else{
            ui->menuBar->hide();
        }
    }
    if (e->modifiers() == (Qt::ShiftModifier | Qt::ControlModifier) && e->key() == Qt::Key_E)
    {
        //pressed
        qDebug() <<"run";
    }
}

void MainWindow::setTooltips()
{
    ui->weiBroadcastBtn->setToolTip(BCTOOLTIP);
    ui->messageBoxBtn->setToolTip(MESSAGEBOXTOOLTIP);
    ui->functionBoxBtn->setToolTip(FUNCTIONBOXTOOLTIP);
}



void MainWindow::closeEvent(QCloseEvent *e)
{
    emit minMe();
    e->accept();
}

void MainWindow::setCurrentTeacherUser(){
    //setting the teacher item
    QTreeWidgetItem *teacherItem = new QTreeWidgetItem(ui->studenTree,TEACHER_ITEM);
    QString userName = tr("jsp001");
    QString currentTearcherUserName = userName+IAMHERE;
    teacherItem->setText(0,currentTearcherUserName);
    teacherItem->setIcon(0,QIcon(":/appFace/teacher_on"));
    QString teacherTooltip=tr("<table><tr><td><img src=':/appFace/teacher_on' /></td><td><table><tr><td>\
                              <span style='font-size:15pt; font-weight:600; color:blue;'>")+userName+tr("</span></td></tr>\
                              <tr><td><img src=':/appFace/star'/><img src=':/appFace/star'/><img src=':/appFace/star'/>\
                              </td></tr><tr><td>")+IDENTITY+tr("[<font color='gray'>")+TEACHERIDENTITY+tr("</font>]</td></tr></table></td></tr></table>");
                              teacherItem->setToolTip(0,teacherTooltip);
            ui->studenTree->insertTopLevelItem(0,teacherItem);
}

void MainWindow::setTreeItemsList()
{
    ui->studenTree->clear();
    setCurrentTeacherUser();
    int classCount = teachinDB->getClassCount();
    for(int nClass=0;nClass<classCount;nClass++){
        //font
        QFont classfont("Times New Roman");
        classfont.setBold(true);
        //add class items
        QTreeWidgetItem *classItem = new QTreeWidgetItem(ui->studenTree,CLASS_ITEM);
        classItem->setFont(0,classfont);
        TeachingRoomClass *currentClass = teachinDB->getClassFromDB(nClass);
        classItem->setText(0,currentClass->getClassName()+"   ["+currentClass->getClassStudentsCount()+"]");
        classItem->setExpanded(true);
        //add student items
        int studentCount = teachinDB->getStudentsCountByClassName(currentClass->getClassName());
        for(int nStudent=0;nStudent<studentCount;nStudent++){
            QTreeWidgetItem *studentItem = new QTreeWidgetItem(classItem,STUDENT_ITEM);
            TeachingRoomStudents *currentStudent = teachinDB->getStudentsByClassFromDB(currentClass->getClassName(),nStudent);
            QString stuentItemShowText = currentStudent->getStudentID()+currentStudent->getStudentName();
            studentItem->setText(0,stuentItemShowText);//setting text
            //setting usericon
            QIcon studentIcon;
            studentIcon.addFile(":/appFace/student_off");//default offline
            QString userStar = ":/appFace/student_off";
            QString statusText = VIEWINFO_STATUS_OFF;
            if(currentStudent->getStudentStatus()=="on"){//online
                studentIcon.addFile(":/appFace/student_on");
                userStar = ":/appFace/student_on";
                statusText = VIEWINFO_STATUS_ON;
            }
            studentItem->setIcon(0,studentIcon);
            QString studentTooltip=tr("<table><tr><td><img src='")+userStar+tr("' /></td><td><table><tr><td>\
                                                                               <span style='font-size:15pt; font-weight:600; color:blue;'>")\
                                                                               +currentStudent->getStudentName()+tr("</span><br/><span style='font-size:10pt; color:gray;'>")+statusText+tr("</span></td></tr>\
                                                                                                                                                                                            <tr><td><img src=':/appFace/star'/><img src=':/appFace/star'/><img src=':/appFace/star'/>\
                                                                                                                                                                                            </td></tr><tr><td>")+IDENTITY+tr("[<font color='gray'>")+STUDENTIDENTITY+tr("</font>]</td></tr>\
                                                                                                                                                                                            <tr><td>")+STUDENTID+tr("[<font color='gray'>")+currentStudent->getStudentID()+tr("</font>]</td></tr>\
                                                                                                                                                                                            <tr><td>")+COMEFROM+tr("[<font color='gray'>")+currentStudent->getClassMajor()+tr("</font>]</td></tr></table></td></tr></table>");
                                                                                                                                                                                            studentItem->setToolTip(0,studentTooltip);
        }
    }
}

void MainWindow::startMovie()
{
    QMovie *movie1 = new QMovie(":/appFace/sysad");
    ui->adlabel0->setMovie(movie1);
    movie1->start();
}

bool MainWindow::eventFilter(QObject *o, QEvent *e)
{
    event = e;
    return QMainWindow::eventFilter(o,event);
}


void MainWindow::itemDbClick(QTreeWidgetItem *item,int column){
    if(event->type() == QEvent::MouseButtonDblClick){
        QMouseEvent *mouseEvent = static_cast<QMouseEvent*>(event);
        if(mouseEvent->button() == Qt::LeftButton && item->type() == STUDENT_ITEM){
            if(teachinDB->getStudentByIDandName(item->text(column))->getStudentStatus()=="on"){
                sendQuestion->setCurrentUser(teachinDB->getStudentByIDandName(item->text(column)));
                sendQuestion->exec();
            }
        }
        if(mouseEvent->button() == Qt::LeftButton && item->type() == QUESTION_ITEM){
            ViewQuestionInfo *viewQuestionInfo = new ViewQuestionInfo;
            viewQuestionInfo->show();
        }
    }
}
void MainWindow::itemPress(QTreeWidgetItem *item, int column)
{
    if(event->type() == QEvent::MouseButtonPress){
        QMouseEvent *mouseEvent = static_cast<QMouseEvent*>(event);
        if(mouseEvent->button() == Qt::RightButton){
            QMenu *onContentMenu = new QMenu;
            if(item->type() == STUDENT_ITEM){
                //send question action
                QAction *sendQuestionAction = new QAction(QIcon(":/appFace/sendquestion"),SENDQUESTIONTOUSER,this);
                // sendQuestionAction->setIconVisibleInMenu(true);
                TeachingRoomStudents *currentStudent = teachinDB->getStudentByIDandName(item->text(column));
                if(currentStudent->getStudentStatus()=="on"){
                    sendQuestion->setCurrentUser(currentStudent);
                    onContentMenu->addAction(sendQuestionAction);
                    connect(sendQuestionAction,SIGNAL(triggered()),sendQuestion,SLOT(exec()));
                    onContentMenu->addSeparator();
                }
                //delete student
                QAction *deleteStudentAction = new QAction(QIcon(":/appFace/deletestudent"),DELETESTUDENT,this);
                onContentMenu->addAction(deleteStudentAction);
                connect(deleteStudentAction,SIGNAL(triggered()),this,SLOT(deleteStudent()));
                //set score zero
                QAction *setStudentZeroAction = new QAction(QIcon(":/appFace/setstudentzero"),SETSTUDENTZEOR,this);
                onContentMenu->addAction(setStudentZeroAction);
                connect(setStudentZeroAction,SIGNAL(triggered()),this,SLOT(setStudentZero()));
                /*
                onContentMenu->addSeparator();
                //management student
                QAction *studentManageAction = new QAction(QIcon(":/appFace/studentmm"),STUDENTMANAGEMENT,this);
                onContentMenu->addAction(studentManageAction);
                */
                //view student info
                onContentMenu->addSeparator();
                QAction *viewStudentInfoAction = new QAction(QIcon(":/appFace/viewstudent"),VIEWSTUDENT,this);
                onContentMenu->addAction(viewStudentInfoAction);
                connect(viewStudentInfoAction,SIGNAL(triggered()),this,SLOT(viewStudentInfoSlot()));
            }
            if(item->type() == QUESTION_ITEM){
                QAction *viewQuestionInfoAction = new QAction(QIcon(":/appFace/viewquesitonaction"),VIEWQUESTION,this);
                onContentMenu->addAction(viewQuestionInfoAction);
            }
            onContentMenu->exec(mouseEvent->globalPos());
        }
    }
}

void MainWindow::settingSever(QString host, QString port)
{
    this->host = host;
    this->port = port;
}

bool MainWindow::initDatabase()
{
    teachinDB = new TeachingDB(host,port);//init db connection
    if(teachinDB->getConnectionResult()){
        teachinDB->initData();//init data(tree list)
        setTreeItemsList();
        setQuestionSet();//get questionset from database and add to the sendquestion dialog
        return true;
    }
    else{
        return false;
    }
}

void MainWindow::refreshData()
{
    teachinDB->closeDB();
    socket->write(QString("refreshdata\n").toUtf8());
    initDatabase();
}

void MainWindow::quitApp()
{
    teachinDB->closeDB();
    socket->disconnectFromHost();
    socket->close();
    qApp->quit();
}



void MainWindow::emitNewPassword(QString newPassword){
    if(teachinDB->changePassword(newPassword)){
        QMessageBox::information(this,CHANGEPASSWORDPROMPT,CHANGEPASSWORDSUCCESSPROMPT,QMessageBox::Ok);
    }
    else{
        QMessageBox::information(this,CHANGEPASSWORDPROMPT,CHANGEPASSWORDFAILUREPROMPT,QMessageBox::Ok);
    }
}

bool MainWindow::checkLoginingUser(QString userPassword)
{
    if(teachinDB->checkLoginingUser(userPassword)){
        return true;
    }
    else{
        return false;
    }
}

void MainWindow::classManage()
{
    refreshData();
    int classCount = teachinDB->getClassCount();
    classManageMentDialog->setClassCount(classCount);
    for(int nClass=0;nClass<classCount;nClass++){
        //add class items
        TeachingRoomClass *currentClass = teachinDB->getClassFromDB(nClass);
        for(int columnIndex=0;columnIndex<2;columnIndex++){
            classManageMentDialog->setClassItems(nClass,columnIndex,currentClass);//row,column,classItemData
        }
        classManageMentDialog->setManageBtn(nClass);
    }
    classManageMentDialog->exec();
}

void MainWindow::setQuestionSet()
{
    int questionSetSize = teachinDB->getQuestionSetSize();
    for(int quesionIndex=0; quesionIndex<questionSetSize;quesionIndex++){
        sendQuestion->setQuestionSet(teachinDB->getQuestionFromSet(quesionIndex));
    }

    createQuestionDialog->clearQuestionList();
    ui->questionSetList->clear();
    int chapterListSize = teachinDB->getChapterListSize();
    for(int chapterIndex=0;chapterIndex<chapterListSize;chapterIndex++){
        createQuestionDialog->setChapterList(teachinDB->getChapterFromList(chapterIndex));
        //chapter root item
        QTreeWidgetItem *chapterItem = new QTreeWidgetItem(ui->questionSetList,CHAPTER_ITEM);
        QString chapterID = teachinDB->getChapterFromList(chapterIndex);
        chapterItem->setText(0,chapterID);
        chapterItem->setIcon(0,QIcon(":/appFace/chapter"));
        chapterItem->setExpanded(true);
        //questlist item
        teachinDB->getQuestionListByChapterID(chapterID);
        int questionlistSize = teachinDB->getQuestionListSize();
        for(int i=0; i<questionlistSize;i++){
            QString questionKey = teachinDB->getQuestionKeyByIndex(i);
            QTreeWidgetItem *questionItem = new QTreeWidgetItem(chapterItem,QUESTION_ITEM);
            questionItem->setText(0,questionKey);
            questionItem->setIcon(0,QIcon(":/appFace/questionlisticon"));
        }
    }
}

void MainWindow::updateQuestion(QString questionIndex,
                                QString chapterID,
                                QString questionTitle,
                                QString questionContext,
                                QString limitTime,
                                QString questionScore,
                                QString anwser)
{
    bool result = teachinDB->updateQuestion(questionIndex,
                                            chapterID,
                                            questionTitle,
                                            questionContext,
                                            limitTime,
                                            questionScore,
                                            anwser);
    if(result == true){
        emit refreshOnTrayMessage();
    }
    emit updateQuestionResult(result);
}

void MainWindow::deleteStudent()
{
    QString studentIDandName = ui->studenTree->currentItem()->text(0);
    TeachingRoomStudents *student = teachinDB->getStudentByIDandName(studentIDandName);
    bool result = teachinDB->deleteStudent(student->getStudentID());
    if(result==true){
        refreshData();
    }else{
        QMessageBox::information(this,SYSTEMPROMPT,SYSTEMERRORPROMPT);
    }
    //remove from infotabwidget
    int index = infoTabWidget->indexOf(studentInfoList.value(studentIDandName));
    if(index == 0){//only page widget
        studentInfoList.clear();
        emit emptyInfoTabWidget();
    }
    infoTabWidget->removeTab(index);
}

void MainWindow::setStudentZero()
{
    QString studentIDandName = ui->studenTree->currentItem()->text(0);
    TeachingRoomStudents *student = teachinDB->getStudentByIDandName(studentIDandName);
    bool result = teachinDB->setStudentScoreZero(student->getStudentID());
    if(result==true){
        refreshData();
    }else{
        QMessageBox::information(this,SYSTEMPROMPT,SYSTEMERRORPROMPT);
    }
}

void MainWindow::addQuestion(QString chapterID,
                             QString questionTitle,
                             QString questionContext,
                             QString questionLimitTime,
                             QString questionScore,
                             QString answer)
{
    bool result = teachinDB->addQuestion(chapterID,
                                         questionTitle,
                                         questionContext,
                                         questionLimitTime,
                                         questionScore,
                                         answer);
    if(result == true){
        emit refreshOnTrayMessage();
    }
    emit addQuestionResult(result);
}

void MainWindow::viewStudentInfoSlot()
{
    //reget data
    teachinDB->initData();
    QString studentIDandName = ui->studenTree->currentItem()->text(0);
    ViewStudentInfo *studentInfo = new ViewStudentInfo;
    TeachingRoomStudents *student = teachinDB->getStudentByIDandName(studentIDandName);
    studentInfo->setStudentInfo(student->getStudentID(),
                                student->getStudentName(),
                                student->getStudentSex(),
                                student->getClassMajor(),
                                student->getStudentStatus(),
                                student->getClassCount(),
                                student->getClassTime(),
                                student->getStudentScore());
    teachinDB->preperGetAnswerQuestionList(studentIDandName);
    int answeredQuestionSize = teachinDB->getAnswerQuestionListSize();
    studentInfo->setAnsweredRows(answeredQuestionSize);
    for(int index=0;index < answeredQuestionSize;index++){
        studentInfo->addAnsweredQuestion(index,teachinDB->getAnswerQuestion(index));
    }
    int index = -1;
    QIcon icon;
    QString status = teachinDB->getStudentStatusByName(studentIDandName);
    if(status == "on"){
        icon = QIcon(":/appFace/student_on");
    }
    else{
        icon = QIcon(":/appFace/student_off");
    }
    /*
        change var Name error
    */
    if(studentInfoList.contains(studentIDandName) == false){
        infoTabWidget->addTab(studentInfo,icon,studentIDandName);
        studentInfoList.insert(studentIDandName,studentInfo);
        index = infoTabWidget->indexOf(studentInfo);
    }
    else{
        //old index
        index = infoTabWidget->indexOf(studentInfoList.value(studentIDandName));
        //update data:must operation,to get the old index in next time.
        studentInfoList.insert(studentIDandName,studentInfo);
        infoTabWidget->removeTab(index);
        //new index
        index = infoTabWidget->insertTab(index,studentInfo,icon,studentIDandName);
    }
    infoTabWidget->setCurrentIndex(index);
    infoTabWidget->show();
}

void MainWindow::closeStudentTabWidgetByIndex(int index){
    QString studentName  = infoTabWidget->tabText(index);
    QHash<QString,ViewStudentInfo*>::iterator i = studentInfoList.find(studentName);
    while (i != studentInfoList.end() && i.key() == studentName) {
        if (i.value() == studentInfoList.value(studentName)) {
            i = studentInfoList.erase(i);
        } else {
            ++i;
        }
    }
    infoTabWidget->removeTab(index);
    if(infoTabWidget->count() == 0){
        infoTabWidget->clear();
        studentInfoList.clear();
        infoTabWidget->close();
    }
}

void MainWindow::clearStudenetInfoList()
{
    studentInfoList.clear();
}

void MainWindow::deleteClassbyName(QString className)
{
    bool result = teachinDB->deleteClassbyName(className);
    if(result==true){
        refreshData();
        QMessageBox::information(this,SYSTEMPROMPT,SYSTEMESUCCESSPROMPT,QMessageBox::Ok);
    }else{
        QMessageBox::information(this,SYSTEMPROMPT,SYSTEMERRORPROMPT);
    }
}


void MainWindow::createGlobalActions()
{
    //global shortcut
    //show  of hide main window
    QxtGlobalShortcut * showMainSc = new QxtGlobalShortcut(QKeySequence("Ctrl+Alt+M"), this);
    connect(showMainSc, SIGNAL(activated()),this, SIGNAL(showMe()));

    //exit app shourcut
    QxtGlobalShortcut * exitSc = new QxtGlobalShortcut(QKeySequence("Alt+X"), this);
    connect(exitSc, SIGNAL(activated()),this, SLOT(quitApp()));
}


//socket
bool MainWindow::connectQuestionServer(){
    if(socket->state() ==QAbstractSocket::UnconnectedState){
        socket->connectToHost(serverIP, TRANSFERQUESTION);
    } 
    if(socket->state() == QAbstractSocket::ConnectedState){
        return true;
    }
    else{
        return false;
    }
}


void MainWindow::receiveQuestionAnswer(){
    while (socket->canReadLine())
    {
        QString line = QString::fromUtf8(socket->readLine()).trimmed();
        QStringList messageList = line.split(QRegExp("/"));
        if(messageList.at(0)=="updateStatus"){
            refreshData();
        }
        //the teacher data format :teacher/studentid/questionid
        //the student data format : student/studentid/questionid/questionanswer
        //data from student
        if(messageList.at(0)==QString("student")){
            updateStudentScore(messageList.at(1),messageList.at(2),messageList.at(3));
        }
    }
}

void MainWindow::setServerHost(QString hostIP)
{
    serverIP = hostIP;
}


void MainWindow::closeDB()
{
    teachinDB->closeDB();
}

void MainWindow::sendQuestionInfo(QString questionInfo)
{
    socket->write(questionInfo.toUtf8());
}

void MainWindow::updateStudentScore(QString studentID, QString questionID, QString questionAnswer)
{
    QuestionSet *currentQuestion = teachinDB->getQuestionByID(questionID);
    QString correctAnswer = currentQuestion->getQuestionAnwser();
    if(questionAnswer == correctAnswer){
        int score = currentQuestion->getQuestionScore().toInt();
        int studentCurrentScore = teachinDB->getStudentScore(studentID).toInt();
        int newScore = studentCurrentScore+score;
        //update the score
        teachinDB->updateStudentScore(studentID,newScore);
    }
    AnsweredQuestion  *answered = new AnsweredQuestion;
    answered->setQuestionID(questionID);
    answered->setStudentID(studentID);
    answered->setStudentAnswer(questionAnswer);
    teachinDB->studentAnsweredQuestion(answered);
}

void MainWindow::broadCast()
{
    BroadCast *broadCast = new BroadCast;
    if(broadCast->exec()){
        socket->write(QString("broadcast/"+broadCast->getBroadCastContent()+"\n").toUtf8());
        ui->broadCastList->addItem(new QListWidgetItem(broadCast->getBroadCastContent(),ui->broadCastList));
    }
}
