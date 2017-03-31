#include "BaseEntities.h"


BaseEntities::BaseEntities(long id, QUuid netUiId, QDate createDate)
    : mId(id),
      mNetUiId(netUiId),
      mCreateDate(createDate)
{

}

long BaseEntities::Id() const
{
    return mId;
}

QUuid BaseEntities::NetUiID() const
{
    return mNetUiId;
}

QDate BaseEntities::CreateDate() const
{
    return mCreateDate;
}

void BaseEntities::setUpdateDate(QDate updateDate)
{
    mUpdateDate = updateDate;
}

QDate BaseEntities::UpdateDate() const
{
    return mUpdateDate;
}
