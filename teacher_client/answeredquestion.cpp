#include "answeredquestion.h"

AnsweredQuestion::AnsweredQuestion()
{
}

QString AnsweredQuestion::getQuestionID()
{
    return this->questonID;
}

QString AnsweredQuestion::getStudentID()
{
    return this->studentID;
}

QString AnsweredQuestion::getStudentAnswer()
{
    return this->StudentAnswer;
}

void AnsweredQuestion::setQuestionID(QString questionID)
{
    this->questonID = questionID;
}

void AnsweredQuestion::setStudentID(QString studentID)
{
    this->studentID = studentID;
}

void AnsweredQuestion::setStudentAnswer(QString StudentAnswer)
{
    this->StudentAnswer =StudentAnswer;
}

QString AnsweredQuestion::getQuestionTitle()
{
    return this->questionTitle;
}

QString AnsweredQuestion::getCorrectAnswer()
{
    return this->correctAnswer;
}

QString AnsweredQuestion::getQuestionScore()
{
    return this->questionScore;
}

QString AnsweredQuestion::getStudentScore()
{
    return this->studentScore;
}

void AnsweredQuestion::setQuestionTitle(QString questionTitle)
{
    this->questionTitle = questionTitle;
}

void AnsweredQuestion::setCorrectAnswer(QString correctAnswer)
{
    this->correctAnswer = correctAnswer;
}

void AnsweredQuestion::setQuestionScore(QString questionScore)
{
    this->questionScore = questionScore;
}

void AnsweredQuestion::setStudentScore(QString studentScore)
{
    this->studentScore = studentScore;
}
