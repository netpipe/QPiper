#include "processcontrol.h"
#include <QCoreApplication>

ProcessControl::ProcessControl(QObject *parent) : QObject(parent)
{
    m_notifier = new QSocketNotifier(fileno(stdin), QSocketNotifier::Read, this);
}

void ProcessControl::execute()
{
   std::cout << "Enter application name to execute:" << std::endl;
   std::cout << "> " << std::flush;
   connect(m_notifier, SIGNAL(activated(int)), this, SLOT(readCommand()));
}
void ProcessControl::readCommand()
{
    std::string line;
    std::getline(std::cin, line);
    if (std::cin.eof() || line == "quit") {
        std::cout << "Good bye!" << std::endl;
        qApp->quit();
   } else {
        QString app_name = QString::fromStdString(line);
        const char* ch_app_name = app_name.toLocal8Bit();
        system(ch_app_name);
    }
}
void ProcessControl::showOutput()
{
//    QByteArray bytes = m_process->readAllStandardOutput();

//    QStringList lines = QString(bytes).split("\n");
//    std::string line = lines.first().toStdString();

//    std::cout << "Echo: " << line << std::endl;
//    std::cout << "> " << std::flush;
}
