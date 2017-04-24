#include "BaseEntity.h"


BaseEntity::BaseEntity(long id, QUuid netUiId, QDate createDate, QDate updateDate)
    : mId(id),
      mNetUiId(netUiId),
      mCreateDate(createDate),
      mUpdateDate(updateDate)
{

}

BaseEntity::BaseEntity()
{

}

long BaseEntity::Id() const
{
    return mId;
}

QUuid BaseEntity::NetUiID() const
{
    return mNetUiId;
}

QDate BaseEntity::CreateDate() const
{
    return mCreateDate;
}

void BaseEntity::setUpdateDate(QDate updateDate)
{
    mUpdateDate = updateDate;
}

QDate BaseEntity::UpdateDate() const
{
    return mUpdateDate;
}
