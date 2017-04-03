#ifndef PERSONENTITIES_H
#define PERSONENTITIES_H

#include <QString>
#include "Entities/BaseEntities.h"

class PersonEntities : public BaseEntities
{
public:
    PersonEntities(long id, QUuid netUiId, QDate createDate,
                   QString firstName, QString lastName, QString email, QString phone);
    PersonEntities();

    void setFirstName(QString firstName);
    QString getFirstName()const;

    void setLastName(QString lastName);
    QString getLastName()const;

    void setEmail(QString email);
    QString getEmail()const;

    void setPhone(QString phone);
    QString getPhone()const;

private:
    QString mFirstName;
    QString mLastName;
    QString mEmail;
    QString mPhone;
};

#endif // PERSONENTITIES_H
