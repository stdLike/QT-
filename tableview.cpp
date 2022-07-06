#include "tableview.h"
#include <QWidget>
#include <QStorageInfo>
#include <QTranslator>


myTableView::myTableView(int width,int height,QTableView *parent)
    :QTableView(parent)
{
    DDiskManager myDiskm;
    QStringList Urls = myDiskm.blockDevices();
    this->setStyleSheet("QTableView{background-color:#ffffff}");
    this->verticalHeader()->setDefaultSectionSize(200);
    this->horizontalHeader()->setDefaultSectionSize(300);
    this->verticalHeader()->setVisible(false);
    this->horizontalHeader()->setVisible(false);
    this->setShowGrid(false) ;
    this->setStyleSheet("selection-background-color: #eeeeee");
    myCol = width/(300);
    opModel = new QStandardItemModel();
    opModel->setColumnCount(myCol);
    opModel->setRowCount(width/myCol);
    this->setModel(opModel);
    this->setGeometry(0,0,width,height);

    for(auto url:Urls){
            QList<QString> devAttribute;
            devJob = myDiskm.createBlockDevice(url);
            devName = devJob->idLabel();
            if(devName=="")
                devName ="_spareDev"+QString("%1").arg(num++);
            QByteArrayList moutList = devJob->mountPoints();
            if(moutList.size()==0)
                continue;
            QStorageInfo *dev_info = new QStorageInfo(moutList.first());
            devStill = dev_info->bytesAvailable();
            devSize =  dev_info->bytesTotal();
            devUsd = devSize - devStill;
            devRate = static_cast<int>((devUsd*1.0)/(1.0*devSize)*100);
            devAttribute<<readableFilesize(devUsd)<<readableFilesize(devSize)<<QString::number(devRate)<<QString(moutList.first());
            devices.insert(devName,devAttribute);
            devicesNames.push_back(devName);
    }
    qSort(devicesNames.begin(),devicesNames.end());
    for(auto dev:devicesNames)
    {
        QList<QString> devAttribute=devices.value(dev);
        mySdk = new widgetSdk (dev,devAttribute[0],devAttribute[1],devAttribute[2].toInt(),devAttribute[3]);
        mySdk->setParent(this);
        mySdk->setMouseTracking(true);
        this->setIndexWidget(opModel->index(row,col),mySdk);
        if(++col==myCol){
            col=0;
            row++;
        }
    }
}

myTableView::~myTableView()
{
    delete(opModel);
    delete(devJob);
    delete (mySdk);
}

