#include "questionset.h"

QuestionSet::QuestionSet()
{
}

void QuestionSet::setQustionID(QString id)
{
    this->questionID = id;
}

void QuestionSet::setChapterID(QString id){
    this->chapterID = id;
}

void QuestionSet::setQuestionTitle(QString title){
    this->questionTitle = title;
}

void QuestionSet::setQuestionContent(QString content){
    this->questionContent = content;
}
void QuestionSet::setQuestionLimitTime(QString limitTime){
    this->questionLimitTime = limitTime;
}

void QuestionSet::setQuestionPublicDate(QString publicDate){
    this->questionPublicDate = publicDate;
}
void QuestionSet::setQuestionScore(QString score){
    this->questionScore = score;
}

QString QuestionSet::getQuestionID(){
    return this->questionID;
}
QString QuestionSet::getChapterID(){
    return this->chapterID;
}

QString QuestionSet::getQuestionTitle(){
    return this->questionTitle;
}
QString QuestionSet::getQuestionContent(){
    return this->questionContent;
}

QString QuestionSet::getQuestionLimitTime(){
    return this->questionLimitTime;
}

QString QuestionSet::getQuestionPublicDate(){
    return this->questionPublicDate;
}
QString QuestionSet::getQuestionScore(){
    return this->questionScore;
}

void QuestionSet::setQuestionAnwser(QString anwser)
{
    this->questionAnwser = anwser;
}

QString QuestionSet::getQuestionAnwser()
{
    return this->questionAnwser;
}
