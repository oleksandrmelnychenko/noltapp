#ifndef BASEENTITIES_H
#define BASEENTITIES_H

#include <QDate>
#include <QUuid>

class BaseEntities
{
public:
    BaseEntities(long id, QUuid netUiId, QDate createDate);

protected:
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
