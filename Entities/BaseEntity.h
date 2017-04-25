#ifndef BASEENTITIES_H
#define BASEENTITIES_H

#include <QDate>
#include <QUuid>

class BaseEntity
{
public:
    BaseEntity(long id, QUuid netUiId, QDate createDate);
    BaseEntity();

    long Id() const;
    QUuid NetUiID() const;
    QDate CreateDate() const;
    void setUpdateDate(QDate updateDate);
    QDate UpdateDate() const;

private:
    long mId;
    QUuid mNetUiId;
    QDate mCreateDate;
    QDate mUpdateDate;
};

#endif // BASEENTITIES_H
