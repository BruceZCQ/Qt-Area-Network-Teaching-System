#ifndef EDITQUESTION_H
#define EDITQUESTION_H

#include <QtCore>
#include <QDialog>

namespace Ui {
    class EditQuestion;
}

class EditQuestion : public QDialog
{
    Q_OBJECT

public:
    explicit EditQuestion(QWidget *parent = 0);
    ~EditQuestion();
    void addItem(QString itemText);
    void setCurrentQuestionID(int questionIndex);
    void setValue(QString chapter,
                  QString questionTitle,
                  QString questionCotext,
                  QString limitTime,
                  QString score,
                  QString answer);
    void clearInfo();
private slots:
    void refreashQuestionDataSlot();
    void submitEditValue();
public slots:
    void slotUpdateResult(bool result);
private:
    Ui::EditQuestion *ui;
signals:
    void changeCurrentQuestionIndex(int index);
    void refreashQuestionData();
    void emitNewValue(QString questionIndex,
                      QString chapterID,
                      QString questionTitle,
                      QString questionContext,
                      QString limitTime,
                      QString questionScore,
                      QString anwser);
};

#endif // EDITQUESTION_H
