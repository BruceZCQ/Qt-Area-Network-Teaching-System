#ifndef QUESTIONWIDGET_H
#define QUESTIONWIDGET_H

#include <QtCore>
#include <QtGui>

namespace Ui {
    class QuestionWidget;
}

class QuestionWidget : public QWidget
{
    Q_OBJECT

public:
    explicit QuestionWidget(QWidget *parent = 0);
    ~QuestionWidget();
    void setQuestionInfo(QString answer,QString content);
private slots:
    void submitAnswer();
private:
    Ui::QuestionWidget *ui;
    enum RESULT{OK,NO};
    void setMovie(int result);
    void createActions();
    QString correctAnswer;
    QTimer *sendNext;
signals:
    void nextQuestion();
};

#endif // QUESTIONWIDGET_H
