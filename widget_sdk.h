#ifndef SDKWIDGET_H
#define SDKWIDGET_H

#include <QWidget>
#include <QFont>
#include <QMenu>
#include <QVBoxLayout>
#include <QLabel>
#include <QProgressBar>

class widgetSdk : public QWidget
{
    Q_OBJECT
public:
    widgetSdk(QString name="",QString res="",QString all="",int rate=0,QString url="",QWidget *parent = nullptr);
    ~widgetSdk();
protected:
    void enterEvent(QEvent*);
    void leaveEvent(QEvent*);
    void mousePressEvent(QMouseEvent *event);
private:
        int rateCheck ;
        QString moutPoint;
        QMenu *contextMenu;
        QAction *addAction;
        QHBoxLayout *layoutH;
        QVBoxLayout *layoutV;
        QLabel *labelName;
        QLabel *labelStatus;
        QProgressBar *pConectBar;
        QFont ft1{"黑体", 13, 87};
        QFont ft2{"Times", 10};
        QFont fileFont;
        QFont dirFont;


};

QString readableFilesize( qint64 filesize);
#endif // SDKWIDGET_H
