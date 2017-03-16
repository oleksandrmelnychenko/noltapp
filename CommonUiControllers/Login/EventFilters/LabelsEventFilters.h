#ifndef LABELEVENTFILTERS_H
#define LABELEVENTFILTERS_H

#include <QObject>

class LabelsEventFilters : public QObject
{
    Q_OBJECT
public:
    explicit LabelsEventFilters(QObject *parent = 0);

signals:

public slots:
};

#endif // LABELEVENTFILTERS_H
