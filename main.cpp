#include "widget.h"
#include <QApplication>
#include <QDBusMetaType>
#include <QTranslator>
int main(int argc, char *argv[])
{
    qDBusRegisterMetaType<QByteArrayList>();
    QApplication a(argc, argv);
//    QTranslator translator;
//    translator.load(QString(":/qm/main_widget_") + language_suffix);
//    a.installTranslator(&translator);
    Widget w;
    w.setMinimumSize(600,400);
    w.show();
    return a.exec();
}
