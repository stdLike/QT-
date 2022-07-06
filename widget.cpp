#include "widget.h"
#include "widget_sdk.h"
#include <QDebug>

Widget::Widget(QWidget *parent)
    : QWidget(parent)
{
    mdiskm = new  DDiskManager() ;
    mdiskm->setWatchChanges(true);
    QStringList Urls = mdiskm->blockDevices();
    this->setGeometry(0,0,1000,650);
    connect(this,&Widget::send,this,&Widget::remake);
    connect(mdiskm,&DDiskManager::diskDeviceAdded,this,&Widget::remake);
    connect(mdiskm,&DDiskManager::blockDeviceRemoved,this,&Widget::remake);
}
Widget::~Widget()
{
    delete (table);
    delete (mdiskm);
}
void Widget::resizeEvent(QResizeEvent *event)
{
    emit this->send();
    QWidget::resizeEvent(event);
}

void Widget::remake()
{
    if(this->children().size()==1)
    {
        delete (this->children()[0]);
    }
    table = new myTableView(this->width(),this->height());
    table->setParent(this);
    table->show();
    this->update();
}


