#include "widget.h"
#include "widget_sdk.h"
#include <QDebug>
#include <QProgressBar>
#include <math.h>
#include <QVBoxLayout>
#include <QLabel>
#include <QIcon>
#include <QDir>
#include <QIcon>
#include <QFont>
#include <QLabel>

widgetSdk::widgetSdk(QString name, QString res, QString all, int rate,QString url,QWidget *parent)
   : QWidget(parent)
{
    rateCheck = rate;
    moutPoint = url;
    QIcon undoicon = QIcon::fromTheme("drive-removable-media");
    QLabel *lab = new QLabel (this)  ;
    lab->setPixmap(undoicon.pixmap(64,64));
    this->setFixedWidth(200);
    this->setFixedHeight(120);
    layoutH = new QHBoxLayout();
    layoutV = new QVBoxLayout();
    labelName = new QLabel();
    labelStatus = new QLabel();
    labelName->setParent(this);
    labelStatus->setParent(this);
    labelName->setFont(ft1);
    labelStatus->setFont(ft2);
    labelName->setText(name);
    labelStatus->setText(res+"/"+all);
    pConectBar = new QProgressBar ();
    pConectBar->setParent(this);
    pConectBar->setRange(0,100);
    pConectBar->setStyleSheet("QProgressBar{font:9pt;text-align:center;}QProgressBar::chunk{background:#1E90FF}");
    if(rate>65)
        pConectBar->setStyleSheet("QProgressBar{font:9pt;text-align:center;}QProgressBar::chunk{background:red}");
    pConectBar->setValue(rate);
    layoutH->addWidget(lab);
    layoutV->addWidget(labelName);
    layoutV->addWidget(labelStatus);
    layoutV->addWidget(pConectBar);
    layoutH->addLayout(layoutV);
    this->setLayout(layoutH);
}

widgetSdk::~widgetSdk()
{
    delete(labelName);
    delete(labelStatus);
    delete(pConectBar);
    delete(layoutV);
}

void widgetSdk::enterEvent(QEvent *)
{
    this->setFixedWidth(250);
    this->setFixedHeight(150);
    this->setStyleSheet("background-color:Aquamarine;");

}
void widgetSdk::leaveEvent(QEvent *)
{
    this->setFixedWidth(200);
    this->setFixedHeight(120);
    this->setStyleSheet("background-color:white;");
}

void widgetSdk::mousePressEvent(QMouseEvent *event)
{
    if (event->button() == Qt::RightButton)
     {
          QDir dir(this->moutPoint);
          QStringList allFiles = dir.entryList(QDir::NoDotAndDotDot | QDir::AllEntries, QDir::Name);
          contextMenu = new QMenu;
          fileFont.setItalic(true);
          dirFont.setBold(true);
          if(allFiles.size()==0)
          {
              if(this->rateCheck!=0)
              {
                  addAction = new QAction(tr("PermissionDeny!"),this);
                  addAction->setFont(dirFont);
                  contextMenu->addAction(addAction);
              }else
              {
                  addAction = new QAction(tr("DeviceEmpty！"),this);
                  addAction->setFont(dirFont);
                  contextMenu->addAction(addAction);
              }
          }
          else
          {
              addAction = new QAction(tr("DeviceList："),this);
              contextMenu->addAction(addAction);
              QStringList alldirs;
              for(QString file:allFiles)
              {
                  addAction = new QAction(file,this);
                  if(file.contains('.'))
                      addAction->setFont(fileFont);
                  contextMenu->addAction(addAction);
              }
          }
          contextMenu->exec(event->globalPos());
          delete (contextMenu);
          delete (addAction);
    }
}
QString readableFilesize( qint64 filesize)
{
    QStringList units;
    units << "B" << "KB" << "MB" << "GB" << "TB" << "PB";
    double mod  = 1024.0;
    double size = filesize;
    int i = 0;
    long rest = 0;
    while (size >= mod && i < units.count()-1 )
    {
        rest= (long)size % (long)mod ;
        size /= mod;
        i++;
    }
    QString szResult = QString::number(floor(size));
    if( rest > 0)
    {
       szResult += QString(".") + QString::number(rest).left(2);
    }
    szResult += units[i];
    return  szResult;
}
