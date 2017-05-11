#ifndef PERSONENTITIES_H
#define PERSONENTITIES_H

#include <QString>
#include "Entities/BaseEntity.h"

class PersonEntity : public BaseEntity
{
public:
    PersonEntity(long id, QUuid netUiId, QDate createDate,
                   QString firstName, QString lastName, QString email, QString phone, QString birthday);

    PersonEntity(QString firstName, QString lastName, QString email, QString phone, QString birthday);

    PersonEntity();

    void setFirstName(QString firstName);
    QString getFirstName() const;

    void setLastName(QString lastName);
    QString getLastName() const;

    void setEmail(QString email);
    QString getEmail() const;

    void setPhone(QString phone);
    QString getPhone() const;

    void setBirthday(QString birthday);
    QString getBirthday() const;

private:
    QString mFirstName;
    QString mLastName;
    QString mEmail;
    QString mPhone;
    QString mBirthday;
};

#endif // PERSONENTITIES_H
