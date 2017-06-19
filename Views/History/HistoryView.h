#ifndef HISTORYVIEW_H
#define HISTORYVIEW_H

#include <QWidget>

namespace Ui {
    class HistoryView;
}

class HistoryView : public QWidget
{
    Q_OBJECT

public:
    explicit HistoryView(QWidget *parent = 0);
    ~HistoryView();

private:
    Ui::HistoryView *ui;
};

#endif // HISTORYVIEW_H
