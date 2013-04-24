#ifndef CUSTOMTEXTEDIT_H
#define CUSTOMTEXTEDIT_H

#include <QtCore>
#include <QtGui>

class CustomTextEdit : public QTextEdit
{
    Q_OBJECT
public:
    explicit CustomTextEdit(QWidget *parent = 0);
    void setSize();
    void seachText(QString searchTxt);
private:
    QLineEdit *searchBar;
    QTextCharFormat defaultFormat;
signals:

public slots:
    void setSearchBarFocus();
    void removeSeachBarFocus();
private slots:
    void searchCusorText(QString searchTxt);
    void searchCusorText();
};

#endif // CUSTOMTEXTEDIT_H
