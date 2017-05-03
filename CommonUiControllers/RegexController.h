#ifndef REGEXCONTROLLER_H
#define REGEXCONTROLLER_H

#include <QObject>

class RegexController
{
public:
    RegexController();

private:
    QString mRegName = ("[a-zA-Z0-9_\\-\\.]{1,30}");
    QString mRegEmail = ("([a-zA-Z0-9_\\-\\.]+)@([a-zA-Z0-9_.-])+\\.([a-zA-Z]{2,4}|[0-9]{1,3})");
    QString mRegPhone = ("\\([0-9]{3}\\)\\s[0-9]{3}-[0-9]{2}-[0-9]{2}");  // (097) 231-23-52;
};

#endif // REGEXCONTROLLER_H
