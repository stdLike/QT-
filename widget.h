#ifndef WIDGET_H
#define WIDGET_H
#include "tableview.h"
#include <QWidget>
#include <QFont>
#include <QMouseEvent>
#include <QTableView>
#include <ddiskmanager.h>

class Widget : public QWidget
{
    Q_OBJECT

public:
    Widget(QWidget *parent = nullptr);
    ~Widget()override;
    virtual void resizeEvent(QResizeEvent *event) override;
signals:
    void send();
protected slots:
    void remake();

private:
    DDiskManager *mdiskm;
    myTableView *table;
};



#endif // WIDGET_H
