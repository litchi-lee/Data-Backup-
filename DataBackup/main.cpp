#include "widget.h"
#include "configManager.h"
#include <QDebug>

#include <QApplication>

int main(int argc, char *argv[])
{
    QApplication a(argc, argv);

    Widget w;
    w.show();

//    测试configManager.h
//    qDebug() << ConfigManager::getDesPath();
//    ConfigManager::updateDesPath("D:\\Qt\\BackUp\\TestDes2");
//    qDebug() << ConfigManager::getDesPath();

    return a.exec();
//    return 0;
}
