#ifndef TABLEVIEW_H
#define TABLEVIEW_H
#include "widget_sdk.h"
#include <QTableWidget>
#include <QMouseEvent>
#include <QModelIndex>
#include <QDataWidgetMapper>
#include <QDebug>
#include <QHeaderView>
#include <QTableWidgetItem>
#include <QStandardItemModel>
#include <ddiskmanager.h>
#include <dblockdevice.h>
#include <dudisksjob.h>

class myTableView:public QTableView
{
    Q_OBJECT
public:
    myTableView(int width,int height,QTableView *parent = nullptr);
    ~myTableView();
protected:

public slots:

signals:


private:
    QStandardItemModel *opModel;
    DBlockDevice * devJob;
    widgetSdk *mySdk;
    QMap<QString,QList<QString>>devices;
    QList<QString>devicesNames;
    int num =0;
    QString devMountPoint;
    QString devName;
    qint64 devUsd =0;
    qint64 devSize = 0;
    qint64 devStill =0;
    int devRate = 0;
    int row =0;
    int col =0;
    int myCol;
};

#endif // TABLEVIEW_H
