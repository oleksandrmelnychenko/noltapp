#include "Colleagues.h"

Colleagues::Colleagues(QString name) : mName(name)
{

}

void Colleagues::setName(QString name)
{
    mName = name;
}

QString Colleagues::getName()
{
    return mName;
}


