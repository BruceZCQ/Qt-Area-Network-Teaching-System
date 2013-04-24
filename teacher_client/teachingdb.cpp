#include <QtCore>
#include <QtGui>
#include <QObject>
#include "teachingdb.h"
#include "constvar.h"

TeachingDB::TeachingDB(QString host,QString port)
{
    //init list
    studentsList.clear();
    studentsSet.clear();
    students.clear();
    classList.clear();
    questionSet.clear();
    questionSetList.clear();
    chapterList.clear();
    questionList.clear();
    questionHashList.clear();
    answeredQuenstionList.clear();
    //init database connect flag
    databaseConnectionSuccess = false;
    db = new QSqlDatabase(QSqlDatabase::addDatabase(QString::fromUtf8("QMYSQL")));
    db->setHostName(host);
    db->setPort(port.toInt());
    db->setDatabaseName("teachingroom");
    db->setUserName("root");
    db->setPassword("admin");
    bool dbConn = db->open();
    if (dbConn) {
        databaseConnectionSuccess = true;
    } else {
        databaseConnectionSuccess = false;
        QString errorInfo = db->lastError().text()+QObject::tr("\nPlease resetting your DB server");
        QMessageBox::critical(0,QObject::tr("Database Setting Error"),errorInfo);
    }
}

TeachingRoomStudents* TeachingDB::getStudentsByClassFromDB(QString className,int index)
{
    TeachingRoomStudents *student = new TeachingRoomStudents;
    student = studentsList.values(className).at(index);
    return student;
}

bool TeachingDB::getConnectionResult()
{
    return databaseConnectionSuccess;
}

void TeachingDB::initData()
{
    classList.clear();
    studentsList.clear();
    studentsSet.clear();
    students.clear();
    questionSet.clear();
    questionSetList.clear();
    chapterList.clear();
    questionList.clear();
    questionHashList.clear();
    //get class from database
    QSqlQuery selectClassQuery("SELECT * FROM CLASS;");
    while(selectClassQuery.next()){
        QString className = selectClassQuery.value(0).toString();
        QString classStudentCount = selectClassQuery.value(1).toString();
        classList.insert(className,classStudentCount);
    }
    //get student from database
    for(int i=0;i<classList.size();i++){
        QString selectStudentSql = "SELECT * FROM STUDENT WHERE STUEDNTCLASS='"+classList.keys().at(i)+"';";
        QSqlQuery selectStudentQuery(selectStudentSql);
        while(selectStudentQuery.next()){
            TeachingRoomStudents *student = new TeachingRoomStudents;
            QString studentID = selectStudentQuery.value(0).toString();
            QString studentName = selectStudentQuery.value(1).toString();
            student->setStudentID(studentID);//studentID
            student->setStudentName(studentName);//studentName
            student->setClassMajor(classList.keys().at(i));//studentClass
            student->setStudentSex(selectStudentQuery.value(2).toString());//studentSex
            student->setStudentStatus(selectStudentQuery.value(4).toString());//studentstatus
            student->setClassCount(selectStudentQuery.value(5).toString());//classCount
            student->setClassTime(selectStudentQuery.value(6).toString());//classDate
            student->setStudentScore(selectStudentQuery.value(7).toString());//studentscore
            QString ipAddress = selectStudentQuery.value(8).toString();//studentIP
            student->setIpAddRess(ipAddress);
            studentsList.insertMulti(classList.keys().at(i),student);
            students.insert(studentID+studentName,student);
            studentsSet.insert(studentID,student);
        }
    }
    //get questionset from database
    QSqlQuery selectQuestionSetQuery("SELECT * FROM QUESTIONSET");
    while(selectQuestionSetQuery.next()){
        QuestionSet *question = new QuestionSet;
        QString questionID = QString::number(selectQuestionSetQuery.value(0).toInt());
        question->setQustionID(questionID);
        QString chapterID = selectQuestionSetQuery.value(1).toString();
        question->setChapterID(chapterID);
        QString questionTitle = selectQuestionSetQuery.value(2).toString();
        question->setQuestionTitle(questionTitle);
        QString questionContent = selectQuestionSetQuery.value(3).toString();
        question->setQuestionContent(questionContent);
        QString questionLimitTime = selectQuestionSetQuery.value(4).toString();
        question->setQuestionLimitTime(questionLimitTime);
        QString questionPublicDate = selectQuestionSetQuery.value(5).toString();
        question->setQuestionPublicDate(questionPublicDate);
        QString questionScore = selectQuestionSetQuery.value(6).toString();
        question->setQuestionScore(questionScore);
        QString questionAnwser = selectQuestionSetQuery.value(7).toString();
        question->setQuestionAnwser(questionAnwser);
        questionSet.insert(questionID,question);
        questionSetList.append(question);
        QString key = "◎"+question->getQuestionID()
                +"●"+question->getQuestionTitle()+"Ю"+question->getQuestionPublicDate();
        questionHashList.insert(key,question);
    }
    //get chapterlist from database
    QSqlQuery selectChapterListQuery("SELECT * FROM CHAPTER");
    while(selectChapterListQuery.next()){
        QString chapterName = selectChapterListQuery.value(1).toString();
        chapterList.append(chapterName);
    }
}
void TeachingDB::getQuestionListByChapterID(QString chapterID){
    //clear the list data
    questionList.clear();
    //get questionlist from database
    QSqlQuery selectQuestionSetQuery("SELECT * FROM QUESTIONSET WHERE CHAPTERID = '"+chapterID+"';");
    while(selectQuestionSetQuery.next()){
        QuestionSet *question = new QuestionSet;
        QString questionID = QString::number(selectQuestionSetQuery.value(0).toInt());
        question->setQustionID(questionID);
        QString chapterID = selectQuestionSetQuery.value(1).toString();
        question->setChapterID(chapterID);
        QString questionTitle = selectQuestionSetQuery.value(2).toString();
        question->setQuestionTitle(questionTitle);
        QString questionContent = selectQuestionSetQuery.value(3).toString();
        question->setQuestionContent(questionContent);
        QString questionLimitTime = selectQuestionSetQuery.value(4).toString();
        question->setQuestionLimitTime(questionLimitTime);
        QString questionPublicDate = selectQuestionSetQuery.value(5).toString();
        question->setQuestionPublicDate(questionPublicDate);
        QString questionScore = selectQuestionSetQuery.value(6).toString();
        question->setQuestionScore(questionScore);
        QString questionAnwser = selectQuestionSetQuery.value(7).toString();
        question->setQuestionAnwser(questionAnwser);
        questionList.append(question);
    }
}

QString TeachingDB::getQuestionKeyByIndex(int index){
    QuestionSet *question = questionList.at(index);
    return "◎"+question->getQuestionID()+"●"+question->getQuestionTitle()+"Ю"+question->getQuestionPublicDate();
}

int TeachingDB::getQuestionListSize(){
    return questionList.size();
}

void TeachingDB::closeDB()
{
    QString dbname = db->connectionName();
    db->close();
    delete db;
    db = NULL;
    QSqlDatabase::removeDatabase(dbname);
}

bool TeachingDB::changePassword(QString newPassword)
{
    QString updatePassword = "UPDATE TEACHER SET TEACHERPASSWORD='"+newPassword+"';";
    QSqlQuery updateQuery(*db);
    updateQuery.prepare(updatePassword);
    if(updateQuery.exec()){
        return true;
    }
    else{
        db->rollback();
        return false;
    }
}

bool TeachingDB::checkLoginingUser(QString userPassword)
{
    QString checkLoginingUserSql = "SELECT * FROM TEACHER WHERE TEACHERNAME='jsp001';";
    QSqlQuery checkQuery(checkLoginingUserSql);
    if(checkQuery.exec()){
        while(checkQuery.next()){
            if(checkQuery.value(1).toString()==userPassword){
                return true;
            }
            else{
                return false;
            }
        }
    }
    else{
        db->rollback();
        return false;
    }
    return true;
}

TeachingRoomClass* TeachingDB::getClassFromDB(int index)
{
    TeachingRoomClass *currentClass = new TeachingRoomClass;
    currentClass->setClassName(classList.keys().at(index));
    currentClass->setClassStudentsCount(classList.values().at(index));
    return currentClass;
}

int TeachingDB::getClassCount()
{
    return classList.size();
}

int TeachingDB::getStudentsCountByClassName(QString className)
{
    return studentsList.values(className).size();
}

bool TeachingDB::addNewClass(QString className, QString studentCount)
{
    QString insertNewClassSql = "INSERT INTO CLASS VALUES('"+className+"','"+studentCount+"');";
    QSqlQuery insertQuery(*db);
    insertQuery.prepare(insertNewClassSql);
    if(insertQuery.exec()){
        return true;
    }
    else{
        db->rollback();
        return false;
    }
}


TeachingDB::~TeachingDB(){
    delete db;
    studentsList.clear();
    studentsSet.clear();
    students.clear();
    classList.clear();
    questionSet.clear();
    questionSetList.clear();
    chapterList.clear();
    questionList.clear();
    questionHashList.clear();
    answeredQuenstionList.clear();
}

int TeachingDB::getQuestionSetSize()
{
    return questionSetList.size();
}

QuestionSet * TeachingDB::getQuestionFromSet(int questionIndex)
{
    return questionSetList.value(questionIndex);
}

bool TeachingDB::updateQuestion(QString questionIndex,
                                QString chapterID,
                                QString questionTitle,
                                QString questionContext,
                                QString limitTime,
                                QString questionScore,
                                QString anwser)
{
    QString updateQuestion = "UPDATE QUESTIONSET SET CHAPTERID='"
            +chapterID+"',QUESTIONTITLE = '"
            +questionTitle+"',QUESTIONCONTENT='"
            +questionContext+"',QUESTIONLIMITTIME='"
            +limitTime+"',QUESTIONSCORE='"
            +questionScore+"',ANWSER='"
            +anwser+"' WHERE QUESTIONID='"+questionIndex+"';";
    QSqlQuery updateQuery(*db);
    updateQuery.prepare(updateQuestion);
    if(updateQuery.exec()){
        return true;
    }
    else{
        db->rollback();
        return false;
    }
}

int TeachingDB::getChapterListSize()
{
    return chapterList.size();
}

QString TeachingDB::getChapterFromList(int chapterIndex)
{
    return chapterList.at(chapterIndex);
}

bool TeachingDB::deleteStudent(QString deleteStudentKey)
{
    QString deleteStudent = "DELETE FROM STUDENT WHERE STUDENTID='"+deleteStudentKey+"';";
    QString deleteStudentAnsweredHistory = "DELETE FROM ANSWERHISTORY WHERE STUDENTID='"
            +deleteStudentKey+"';";
    QSqlQuery deleteStudentQuery(*db);
    deleteStudentQuery.prepare(deleteStudent);
    QSqlQuery deleteStudentAnsweredHistoryQuery(*db);
    deleteStudentAnsweredHistoryQuery.prepare(deleteStudentAnsweredHistory);
    if(deleteStudentQuery.exec()&&deleteStudentAnsweredHistoryQuery.exec()){
        return true;
    }
    else{
        db->rollback();
        return false;
    }
}

bool TeachingDB::addQuestion(QString chapterID,
                             QString questionTitle,
                             QString questionContext,
                             QString questionLimitTime,
                             QString questionScore,
                             QString answer)
{
    QString insertQuestion = "INSERT INTO QUESTIONSET VALUES (0,'"
            +chapterID+"','"+questionTitle+"','"
            +questionContext+"','"
            +questionLimitTime+"',NOW(),'"
            +questionScore+"','"+answer+"');";
    QSqlQuery addQuestionQuery(*db);
    addQuestionQuery.prepare(insertQuestion);
    if(addQuestionQuery.exec()){
        return true;
    }
    else{
        db->rollback();
        return false;
    }
}

TeachingRoomStudents * TeachingDB::getStudentByIDandName(QString key)
{
    return students.value(key);
}

QString TeachingDB::getStudentStatusByName(QString key)
{
    return students.value(key)->getStudentStatus();
}

QuestionSet * TeachingDB::getQuestionByKey(QString key)
{
    return questionHashList.value(key);
}
//set student has the key the grade is zero
bool TeachingDB::setStudentScoreZero(QString key)
{
    QString setStudent = "UPDATE STUDENT SET STUDENTTOTALGRADE='0' WHERE STUDENTID='"+key+"';";
    QSqlQuery setStudentQuery(*db);
    setStudentQuery.prepare(setStudent);
    if(setStudentQuery.exec()){
        return true;
    }
    else{
        db->rollback();
        return false;
    }
}
//delete class has ClassName
bool TeachingDB::deleteClassbyName(QString className)
{
    if(deleteStudents(className) == true){
        QString deleteClass = "DELETE FROM CLASS WHERE CLASSNAME='"+className+"';";
        QSqlQuery deleteStudentQuery(*db);
        deleteStudentQuery.prepare(deleteClass);
        if(deleteStudentQuery.exec()){
            return true;
        }
        else{
            db->rollback();
            return false;
        }
    }
    else{
        return false;
    }
}
//delete all students from class has className
bool TeachingDB::deleteStudents(QString className)
{
    QString deleteStudentsFromClass = "DELETE FROM STUDENT WHERE STUEDNTCLASS='"+className+"';";
    QSqlQuery deleteStudentQuery(*db);
    deleteStudentQuery.prepare(deleteStudentsFromClass);
    if(deleteStudentQuery.exec()){
        return true;
    }
    else{
        db->rollback();
        return false;
    }
}



QuestionSet* TeachingDB::getQuestionByID(QString questionID)
{
    return questionSet.value(questionID);
}

QString TeachingDB::getStudentScore(QString studentID)
{
    return studentsSet.value(studentID)->getStudentScore();
}

bool TeachingDB::updateStudentScore(QString studentID, int score)
{
    QString setStudent = "UPDATE STUDENT SET STUDENTTOTALGRADE='"+QString::number(score)
            +"' WHERE STUDENTID='"+studentID+"';";
    QSqlQuery setStudentQuery(*db);
    setStudentQuery.prepare(setStudent);
    if(setStudentQuery.exec()){
        return true;
    }
    else{
        db->rollback();
        return false;
    }
}

bool TeachingDB::studentAnsweredQuestion(AnsweredQuestion *answeredQuestion)
{
    //date
    QString currentDate = QString::number(QDate::currentDate().year())+"."
            +QString::number(QDate::currentDate().month())+"."
            +QString::number(QDate::currentDate().day()) ;
    currentDate = currentDate+QTime::currentTime().toString("  hh:mm:ss");
    QString insertAnsweredQuestion = "INSERT INTO ANSWERHISTORY VALUES ('"
            +answeredQuestion->getQuestionID()+"','"
            +answeredQuestion->getStudentID()+"','"
            +answeredQuestion->getStudentAnswer()+"','"
            +currentDate+"');";
    QSqlQuery addAnswerQuestionQuery(*db);
    addAnswerQuestionQuery.prepare(insertAnsweredQuestion);
    if(addAnswerQuestionQuery.exec()){
        return true;
    }
    else{
        db->rollback();
        return false;
    }
}


void TeachingDB::preperGetAnswerQuestionList(QString stundentIDAndName)
{
    TeachingRoomStudents * student = students.value(stundentIDAndName);
    getAnswerQuestionList(student->getStudentID());
}

void TeachingDB::getAnswerQuestionList(QString stundentID)
{
    answeredQuenstionList.clear();
    QString getAnswerQuestionSql = "SELECT * FROM ANSWERHISTORY WHERE STUDENTID='"+stundentID+"';";
    QSqlQuery checkQuery(getAnswerQuestionSql);
    if(checkQuery.exec()){
        while(checkQuery.next()){
            AnsweredQuestion *answeredquestion = new AnsweredQuestion;
            QString questionID = checkQuery.value(0).toString();
            QString studentAnswer = checkQuery.value(2).toString();
            QuestionSet *question = getQuestionByID(questionID);
            QString correctAnswer = question->getQuestionAnwser();
            answeredquestion->setQuestionID(questionID);
            answeredquestion->setQuestionTitle(question->getQuestionTitle());
            answeredquestion->setCorrectAnswer(correctAnswer);
            answeredquestion->setQuestionScore(question->getQuestionScore());
            answeredquestion->setStudentAnswer(studentAnswer);
            if(studentAnswer == correctAnswer){
                answeredquestion->setStudentScore(question->getQuestionScore());
            }
            else{
                answeredquestion->setStudentScore("0");
            }
            answeredQuenstionList.insertMulti(stundentID,answeredquestion);
        }
    }
}

int TeachingDB::getAnswerQuestionListSize()
{
    return answeredQuenstionList.size();
}

AnsweredQuestion * TeachingDB::getAnswerQuestion(int index)
{
    return answeredQuenstionList.values().at(index);
}

