#include "PersonEntities.h"

PersonEntities::PersonEntities(long id, QUuid netUiId, Qdate createDate,
                               QString firstName, QString lastName, QString email, QString phone)
    : BaseEntities(id,netUiID,createDate),
      mFirstName(firstName),
      mLastName(lastName),
      mEmail(email),
      mPhone(phone)
{

}

void PersonEntities::setFirstName(const QString *firstName)
{
    mFirstName = firstName;
}

QString PersonEntities::getFirstName() const
{
    return mFirstName;
}

void PersonEntities::setLastName(const QString *lastName)
{
    mLastName = lastName;
}

QString PersonEntities::getLastName() const
{
    return mLastName;
}

void PersonEntities::setEmail(const QString *email)
{
    if() // check email
    mEmail = email;
}

QString PersonEntities::getEmail() const
{
    return mEmail;
}

void PersonEntities::setPhone(const QString *phone)
{
    if() // check telephone
    mPhone = phone;
}

QString PersonEntities::getPhone() const
{
    return mPhone;
}
