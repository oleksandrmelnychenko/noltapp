#include "PersonEntity.h"

PersonEntity::PersonEntity(long id, QUuid netUiId, QDate createDate,
                               QString firstName, QString lastName, QString email, QString phone, QString birthday)
    : BaseEntity(id, netUiId, createDate),
      mFirstName(firstName),
      mLastName(lastName),
      mEmail(email),
      mPhone(phone),
      mBirthday(birthday)
{

}

PersonEntity::PersonEntity(QString firstName, QString lastName, QString email, QString phone, QString birthday) :
    mFirstName(firstName),
    mLastName(lastName),
    mEmail(email),
    mPhone(phone),
    mBirthday(birthday)
{

}

PersonEntity::PersonEntity()
{

}

void PersonEntity::setFirstName(QString firstName)
{
    mFirstName = firstName;
}

QString PersonEntity::getFirstName() const
{
    return mFirstName;
}

void PersonEntity::setLastName(QString lastName)
{
    mLastName = lastName;
}

QString PersonEntity::getLastName() const
{
    return mLastName;
}

void PersonEntity::setEmail(QString email)
{   
    mEmail = email;
}

QString PersonEntity::getEmail() const
{
    return mEmail;
}

void PersonEntity::setPhone(QString phone)
{   
    mPhone = phone;
}

QString PersonEntity::getPhone() const
{
    return mPhone;
}

void PersonEntity::setBirthday(QString birthday)
{
    mBirthday = birthday;
}

QString PersonEntity::getBirthday() const
{
    return mBirthday;
}
