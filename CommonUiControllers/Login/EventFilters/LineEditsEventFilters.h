#ifndef LINEEDITEVENTFILTERS_H
#define LINEEDITEVENTFILTERS_H

#include <QObject>

class LineEditsEventFilters : public QObject
{
    Q_OBJECT
public:
    explicit LineEditsEventFilters(QObject *parent = 0);

signals:

public slots:
};

#endif // LINEEDITEVENTFILTERS_H
