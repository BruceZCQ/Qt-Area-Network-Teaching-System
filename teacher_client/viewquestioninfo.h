#ifndef VIEWQUESTIONINFO_H
#define VIEWQUESTIONINFO_H

#include <QWidget>

namespace Ui {
    class ViewQuestionInfo;
}

class ViewQuestionInfo : public QWidget
{
    Q_OBJECT

public:
    explicit ViewQuestionInfo(QWidget *parent = 0);
    ~ViewQuestionInfo();

private:
    Ui::ViewQuestionInfo *ui;
private slots:
    void enableAll();
    void changeBtnTxt();
};

#endif // VIEWQUESTIONINFO_H
