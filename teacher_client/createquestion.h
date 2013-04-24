#ifndef CREATEQUESTION_H
#define CREATEQUESTION_H

#include <QtCore>
#include <QtGui>

namespace Ui {
    class CreateQuestion;
}

class CreateQuestion : public QDialog
{
    Q_OBJECT

public:
    explicit CreateQuestion(QWidget *parent = 0);
    ~CreateQuestion();
    void setChapterList(QString chapterName);
    void clearQuestionList();
    void clearAddQuestionInfo();
private slots:
    void addQuestion();
    void currentIndexChanged(int index);
    void addQuestionResultSlot(bool);
private:
    Ui::CreateQuestion *ui;
signals:
    void refreshChapterList();
    void addQuestion(QString chapterID,
                     QString questionTitle,
                     QString questionContext,
                     QString questionLimitTime,
                     QString questionScore,
                     QString answer);
    void addQuestionResult(bool);
};

#endif // CREATEQUESTION_H
