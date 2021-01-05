#include <iostream>
#include "iniciodialog.h"
#include "registrodialog.h"
#include "menuprincipal.h"
#include "usuario.h"
#include <QApplication>
#include <QCoreApplication>
#include <QFile>
#include <QTextStream>
#include <QDebug>

int main(int argc, char *argv[])
{


    QApplication a(argc, argv);

    inicioDialog w;

    w.show();

    return a.exec();
}
