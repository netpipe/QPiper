#include <QCoreApplication>
#include <QProcess>
#include <QDebug>
#include <qobject.h>
//https://stackoverflow.com/questions/41848939/reading-and-writing-to-qprocess-in-qt-console-application

//QString cmd = "cat file | grep string";
//QProcess *process = new QProcess;
//process->start(cmd);
//process->waitForBytesWritten();
//process->waitForFinished();
//qDebug() << process->readAll();


class MyProcess : public QProcess
{
    Q_OBJECT

public:
    MyProcess(QObject *parent = 0);
    ~MyProcess() {}

public slots:
    void myReadyRead();
    void myReadyReadStandardOutput();
};

MyProcess::MyProcess(QObject *parent)
{
    connect(this,SIGNAL(readyRead()),
            this,SLOT(myReadyRead()));
    connect(this,SIGNAL(readyReadStandardOutput()),
            this,SLOT(myReadyReadStandardOutput()));
}

void MyProcess::myReadyRead() {
    QTextStream s(stdin);
    QString value = s.readLine();
    qDebug() << Q_FUNC_INFO;
}

void MyProcess::myReadyReadStandardOutput() {
    qDebug() << Q_FUNC_INFO;
    // Note we need to add \n (it's like pressing enter key)


    this->write(QString("myname" + QString("\n")).toLatin1());
   // this->write(QString("myname").toLatin1());
    // Next line no required
    // qDebug() << this->readAll();
    qDebug() << this->readAllStandardOutput();

}

int main(int argc, char *argv[])
{
    QCoreApplication a(argc, argv);

    MyProcess *myProcess = new MyProcess();

    QString program = "./myscript.sh";

    myProcess->start("/bin/sh", QStringList() << program);

    a.exec();
}

#include "main.moc"
