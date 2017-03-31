#ifndef PERSONENTITIES_H
#define PERSONENTITIES_H

#include <QString>
#include "Entities/BaseEntities.h"

class PersonEntities : public BaseEntities
{
public:
    PersonEntities(long id, QUuid netUiId, Qdate createDate,
                   QString firstName, QString lastName, QString email, QString phone);

    void setFirstName(const QString *firstName);
    QString getFirstName()const;

    void setLastName(const QString *lastName);
    QString getLastName()const;

    void setEmail(const QString *email);
    QString getEmail()const;

    void setPhone(const QStrinf *email);
    QString getPhone()const;

private:
    QString mFirstName;
    QString mLastName;
    QString mEmail;
    QString mPhone;
};

#endif // PERSONENTITIES_H
