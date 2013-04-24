#ifndef TEACHINGROOMCLASS_H
#define TEACHINGROOMCLASS_H

#include <QtCore>

class TeachingRoomClass
{
public:
    TeachingRoomClass();
    void setClassName(QString className);
    QString getClassName();
    void setClassStudentsCount(QString classStudentsCount);
    QString getClassStudentsCount();
private:
    QString className;
    QString classStudentsCount;
};

#endif // TEACHINGROOMCLASS_H
