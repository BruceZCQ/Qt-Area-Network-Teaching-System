#include "teachingroomclass.h"

TeachingRoomClass::TeachingRoomClass()
{
}

void TeachingRoomClass::setClassName(QString className)
{
    this->className = className;
}

QString TeachingRoomClass::getClassName()
{
    return this->className;
}

void TeachingRoomClass::setClassStudentsCount(QString classStudentsCount)
{
    this->classStudentsCount = classStudentsCount;
}

QString TeachingRoomClass::getClassStudentsCount()
{
    return this->classStudentsCount;
}
