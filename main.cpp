#include "parserwindow.h"
#include <QApplication>
#include <QDir>
#include <QtDebug>

int main(int argc, char *argv[])
{
    QApplication a(argc, argv);
    ParserWindow w;
    w.show();

    return a.exec();
}
