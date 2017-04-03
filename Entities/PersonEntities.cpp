#include "PersonEntities.h"

PersonEntities::PersonEntities(long id, QUuid netUiId, QDate createDate,
                               QString firstName, QString lastName, QString email, QString phone)
    : BaseEntities(id,netUiId,createDate),
      mFirstName(firstName),
      mLastName(lastName),
      mEmail(email),
      mPhone(phone)
{

}

PersonEntities::PersonEntities()
{

}

void PersonEntities::setFirstName(QString firstName)
{
    mFirstName = firstName;
}

QString PersonEntities::getFirstName() const
{
    return mFirstName;
}

void PersonEntities::setLastName(QString lastName)
{
    mLastName = lastName;
}

QString PersonEntities::getLastName() const
{
    return mLastName;
}

void PersonEntities::setEmail(QString email)
{
    //if() // check email
    mEmail = email;
}

QString PersonEntities::getEmail() const
{
    return mEmail;
}

void PersonEntities::setPhone(QString phone)
{
    //if() // check telephone
    mPhone = phone;
}

QString PersonEntities::getPhone() const
{
    return mPhone;
}
