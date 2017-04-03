#include "PersonEntity.h"

PersonEntity::PersonEntity(long id, QUuid netUiId, QDate createDate,
                               QString firstName, QString lastName, QString email, QString phone)
    : BaseEntity(id,netUiId,createDate),
      mFirstName(firstName),
      mLastName(lastName),
      mEmail(email),
      mPhone(phone)
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
    QRegExp regEmail ("([a-zA-Z0-9_\\-\\.]+)@([a-zA-Z0-9_.-])+\\.([a-zA-Z]{2,4}|[0-9]{1,3})");
    if(regEmail.exactMatch(email))
        mEmail = email;
}

QString PersonEntity::getEmail() const
{
    return mEmail;
}

void PersonEntity::setPhone(QString phone)
{
    //if() // check telephone
        mPhone = phone;
}

QString PersonEntity::getPhone() const
{
    return mPhone;
}
