#ifndef COLLEAGUES_H
#define COLLEAGUES_H

#include <QObject>

class Colleagues
{

public:
    Colleagues( QString name = "ss");
    void setName(QString name);
    QString getName();

private:
    QString mName;
};

#endif // COLLEAGUES_H
