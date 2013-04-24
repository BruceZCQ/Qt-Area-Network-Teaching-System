#include "codingwindow.h"
#include "ui_codingwindow.h"

CodingWindow::CodingWindow(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::CodingWindow)
{
    ui->setupUi(this);
    this->setWindowFlags(Qt::WType_TopLevel|Qt::WStyle_StaysOnTop |Qt::WindowTitleHint);
    QDesktopWidget* desktopWidget = QApplication::desktop();
    QRect screenRect = desktopWidget->screenGeometry();
    ui->jspCodeText->setMinimumWidth(screenRect.width()/3);
    ui->javaCodeText->setSize();//custom function
    ui->resultView->hide();
    ui->resultView->setContextMenuPolicy(Qt::NoContextMenu);
    ui->javaCodeText->hide();
    ui->viewJavaCodeBtn->setEnabled(false);
    ui->runCodeBtn->setEnabled(false);
    ui->clearCodeBtn->setEnabled(false);
    ui->searchCodeBtn->setEnabled(false);
    jspHighlighter = new Highlighter(ui->jspCodeText->document());
    //ui->jspCodeText->clear();
    javaHighlighter = new Highlighter(ui->javaCodeText->document());
    isShowViewWin = false;
    isRun = false;
    shouldSavetoServerPath = false;
    //  currentFilePath = QString();
    jspfilesDir= qApp->applicationDirPath();
    QDir dir(jspfilesDir);
    if(dir.cdUp()){
        jspfilesDir = dir.path()+"/exercise/student";
    }
    createActions();
    // createGlobalActions();
}

CodingWindow::~CodingWindow()
{
    delete ui;
}


void CodingWindow::createActions()
{
    connect(ui->openFileAction,SIGNAL(triggered()),this,SLOT(openFile()));
    connect(ui->quitAction,SIGNAL(triggered()),this,SLOT(close()));
    connect(ui->runCodeBtn,SIGNAL(clicked()),this,SLOT(runCode()));
    connect(ui->clearCodeBtn,SIGNAL(clicked()),this,SLOT(clearViewWin()));
    connect(ui->jspCodeText,SIGNAL(textChanged()),this,SLOT(changeButtonState()));
    connect(ui->viewJavaCodeBtn,SIGNAL(clicked()),this,SLOT(showJavaCode()));
    connect(ui->viewJavaCodeBtn,SIGNAL(clicked()),ui->javaCodeText,SLOT(show()));
    //server
    connect(ui->startServerAction,SIGNAL(triggered()),this,SLOT(startServer()));
    connect(ui->stopServerAction,SIGNAL(triggered()),this,SLOT(stopServer()));
    //get select text
    connect(ui->jspCodeText,SIGNAL(cursorPositionChanged()),SLOT(searchCusorText()));
    connect(ui->searchCodeBtn,SIGNAL(clicked()),ui->javaCodeText,SLOT(setSearchBarFocus()));
    connect(ui->quitAction,SIGNAL(triggered()),ui->javaCodeText,SLOT(removeSeachBarFocus()));
}

void CodingWindow::searchCusorText(){
    if(!ui->jspCodeText->textCursor().selectedText().isNull()){
        ui->javaCodeText->seachText(ui->jspCodeText->textCursor().selectedText());
    }
}

void CodingWindow::runCode()
{
    if(isRun){
        if(ui->jspCodeText->toPlainText().length() != 0){
            if(shouldSavetoServerPath){
                currentFilePath = QString();
                shouldSavetoServerPath = false;
            }
            if(currentFilePath.isNull()){
                //check need resave or not
                bool shouldReSave = false;
                do {
                    currentFilePath = QFileDialog::getSaveFileName(this,tr("Save File to Server Workhome"),jspfilesDir,tr("JSPFiles(*.jsp)"));
                    QStringList appPathList = qApp->applicationDirPath().split(QRegExp("/"));
                    QString appPath=QString();
                    for(int index=0;index<appPathList.size()-1;index++){
                        appPath +=appPathList.at(index)+ "/";
                    }
                    QString filePath=QString();
                    QStringList pathList = currentFilePath.split(QRegExp("/"));
                    for(int index=0;index<pathList.size()-3;index++){
                        filePath +=pathList.at(index)+ "/";
                    }
                    if(appPath!=filePath){
                        shouldReSave = true;
                        QMessageBox::information(this,tr("Prompt"),SHOULDSAVETOSERVERPATH);
                    }
                    else{
                        shouldReSave = false;
                    }
                }while(shouldReSave);
            }
            QFile file(currentFilePath);
            if(file.open(QFile::WriteOnly| QFile::Text)) {
                QTextStream out(&file);
                out << ui->jspCodeText->toPlainText();//put data to file
                QStringList list = currentFilePath.split(QRegExp("/"));
                QString prePath;
                for(int index=0;index<list.size()-1;index++){
                    prePath+=list.at(index)+"/";
                }
                setResultView(prePath, list.at(list.size()-1));
                ui->resultView->show();
            }
        }
        ui->viewJavaCodeBtn->setEnabled(true);
        ui->viewjavalabel->setText(CANVIEWJAVACODE);
    }
    else{
        QMessageBox::information(this,tr("Prompt"),STARTSERVER);
    }
}

void CodingWindow::setResultView(QString prePath,QString currentFileName)
{
    this->prePath = prePath;
    this->currentFileName = currentFileName;
    ui->resultView->setUrl(QUrl("http://localhost:1012/student/"+currentFileName));
    showJavaCode();
}

void CodingWindow::showJavaCode()
{
    //copy java code
    system("cpjavacode.vbs");
    QString filePath = prePath+"javacodes/"+currentFileName.split(QRegExp("\\.")).at(0)+"_jsp.java";
    QFile file(filePath);
    if (file.open(QFile::ReadOnly | QFile::Text))
        ui->javaCodeText->setPlainText(file.readAll());
    ui->searchCodeBtn->setEnabled(true);
    ui->searchlabel->setText(CANSEACHER);
}



void CodingWindow::setViewWindows()
{
    if(!isShowViewWin){
        ui->resultView->show();
        isShowViewWin=true;
    }
    else{
        ui->resultView->hide();
        isShowViewWin=false;
    }
}


void CodingWindow::openFile()
{
    clearViewWin();
    if (currentFilePath.isNull())
        currentFilePath = QFileDialog::getOpenFileName(this,
                                                       tr("Choose a JSP file"), jspfilesDir, "JSP Files (*.jsp)");

    if (!currentFilePath.isEmpty()) {
        QFile file(currentFilePath);
        if (file.open(QFile::ReadOnly | QFile::Text))
            ui->jspCodeText->setPlainText(file.readAll());
        //check should resave or not
        QStringList appPathList = qApp->applicationDirPath().split(QRegExp("/"));
        QString appPath=QString();
        for(int index=0;index<appPathList.size()-1;index++){
            appPath +=appPathList.at(index)+ "/";
        }
        QString filePath=QString();
        QStringList pathList = currentFilePath.split(QRegExp("/"));
        for(int index=0;index<pathList.size()-3;index++){
            filePath +=pathList.at(index)+ "/";
        }
        if(appPath!=filePath){
            shouldSavetoServerPath = true;
        }
    }
}

void CodingWindow::clearViewWin()
{
    ui->resultView->hide();
    ui->javaCodeText->hide();
    ui->jspCodeText->clear();
    ui->javaCodeText->clear();
    ui->javaCodeText->removeSeachBarFocus();
    ui->viewJavaCodeBtn->setEnabled(false);
    ui->runCodeBtn->setEnabled(false);
    ui->clearCodeBtn->setEnabled(false);
    ui->searchCodeBtn->setEnabled(false);
    ui->searchlabel->setText(QString());
    ui->viewjavalabel->setText(QString());
    ui->clearlabel->setText(QString());
    ui->runlabel->setText(QString());
    currentFilePath=QString();
}





void CodingWindow::close()
{
    if(isRun){
        stopServer();
        emit exitCoding();
    }
    clearViewWin();
    QMainWindow::close();
}

void CodingWindow::startServer()
{
    //start tomcat server
    system("startserver.vbs");
    emit serverStarted();
    this->showFullScreen();
    isRun = true;
}

void CodingWindow::stopServer()
{
    //stop tomcat server
    system("stopserver.vbs");
    isRun = false;
}



void CodingWindow::changeButtonState()
{
    bool state = false;
    if(ui->jspCodeText->toPlainText().length() != 0){
        state = true;
        ui->runlabel->setText(CANRUN);
        ui->clearlabel->setText(CANCLEAR);
        ui->viewJavaCodeBtn->setEnabled(!state);
        ui->resultView->hide();
    }
    else{
        state = false;
        ui->searchCodeBtn->setEnabled(state);
        ui->viewJavaCodeBtn->setEnabled(state);
    }
    ui->javaCodeText->hide();
    ui->runCodeBtn->setEnabled(state);
    ui->clearCodeBtn->setEnabled(state);
    ui->searchlabel->setText(QString());
    ui->viewjavalabel->setText(QString());
}


