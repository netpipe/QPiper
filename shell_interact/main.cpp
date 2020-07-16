#include <QCoreApplication>
#include "processcontrol.h"

int main(int argc, char *argv[])
{
    QCoreApplication a(argc, argv);

    ProcessControl p_control;
    p_control.execute();
    return a.exec();
}
