#include "mainwindow.h"
#include "ui_mainwindow.h"
#include "qmessagebox.h"
#include "qprocess.h"
#include "qstring.h"
#include "qcoreapplication.h"
#include "qobject.h"
#include <QDebug>
#include <QEvent>

#define CMDOUTPUT 	(QEvent::User + 101)

MainWindow::MainWindow(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::MainWindow)
{
    ui->setupUi(this);
    this->pet = new QPlainTextEdit();
    pet = ui->plainTextEdit;
    pet->setReadOnly(true);
    cmdType = 0;
//    connect(pet, SIGNAL(blockCountChanged(int)), this, SLOT());
    cmdThread = new MyThread();
}

MainWindow::~MainWindow()
{
    delete ui;
}

void MainWindow::asd(int qwe)
{
    QString oldTexts = this->keyText;
    QString currentTexts = this->pet->toPlainText();
    QString commandText = currentTexts.remove(oldTexts);
    QProcess process;
    process.start("cmd /c "+currentTexts+"");
    process.waitForFinished(-1);
    QByteArray out = process.readAllStandardOutput();

    ui->plainTextEdit->setPlainText(currentTexts+"\n"+QString::fromUtf8(out));
    connect(pet, SIGNAL(blockCountChanged(int)), this, SLOT(asd(int)));
    connect(pet, SIGNAL(blockCountChanged(int)), this, 0);

    process.start("cmd /c "+currentTexts+"");
    process.waitForFinished(-1);

    connect(pet, SIGNAL(blockCountChanged(int)), this, SLOT(0));
    ui->plainTextEdit->appendPlainText(QString::fromUtf8(out));
    this->keyText += QString::fromUtf8(out);

    ui->plainTextEdit->setFocus();
}

void MainWindow::on_lineEdit_editingFinished()
{
    if(ui->lineEdit->text() != ""){
        //ui->lineEdit->setEnabled(false);
        QString currentTexts = ui->plainTextEdit->toPlainText();
        QProcess *process = new QProcess();
        process->setProcessChannelMode(QProcess::MergedChannels);
#ifdef _WIN32
        process->start("cmd /c "+ui->lineEdit->text()+"");
#else
        process->start(ui->lineEdit->text()+"");
#endif

        if(process->waitForFinished(-1)) {
            QByteArray out = process->readAll();
            currentTexts += ">>"+ui->lineEdit->text()+"\n"+QString::fromUtf8(out)+"\n";
        } else {
            QString err = process->errorString();
            currentTexts += ">>"+ui->lineEdit->text()+"\n"+err+"\n";
        }

        cmdThread->setMainInstance(this);
        cmdThread->setCommand(ui->lineEdit->text());
        cmdThread->start();
        ui->lineEdit->setText("");
        ui->lineEdit->setEnabled(true);
        ui->lineEdit->setFocus();
//        ui->plainTextEdit->setPlainText(currentTexts);
    }
    else {
        ui->lineEdit->setFocus();
    }
}

void MainWindow::showOutput(QString out){
    output = out;
    QUserEvent *ev = new QUserEvent((QEvent::Type) CMDOUTPUT);
    QApplication::postEvent(this, ev);
    qDebug()<<"showoutput";
}

void MainWindow::customEvent(QEvent * event){
    QUserEvent *ev = (QUserEvent*)event;
    EventUser(ev->type(), ev->wParam(), ev->lParam());
    qDebug()<<"customevent";
}

QUserEvent::QUserEvent(QEvent::Type type, int wparam, int lparam) : QEvent(type) {
    iwParam = wparam;
    ilParam = lparam;
    qDebug()<<"quserevent";
}

bool MainWindow::EventUser(int uMsg, int wParam, int lParam)
{
    qDebug()<<"eventuser";
    switch(uMsg){
    case CMDOUTPUT:
        QString out = ui->plainTextEdit->toPlainText();
        out += output;
        ui->plainTextEdit->setPlainText(out);
        break;
    }
    return true;
}


MyThread::MyThread()
{
    mMainInst = NULL;
}

void MyThread::run()
{
    QString output;
    QProcess *process = new QProcess();
    process->setProcessChannelMode(QProcess::MergedChannels);
#ifdef _WIN32
    if(!mMainInst->cmdType)
        process->start("cmd /c "+cmd+"");
    else
        process->start("cmd /c python -c "+QString(QChar(34))+cmd+QString(QChar(34))+"");
#else
    process->start(cmd+"");
#endif

    if(process->waitForFinished(-1)) {
        QByteArray out = process->readAll();
        output = ">>"+cmd+"\n"+QString::fromUtf8(out)+"\n";
    } else {
        QString err = process->errorString();
        output = ">>"+cmd+"\n"+err+"\n";
    }
    mMainInst->showOutput(output);
}

void MyThread::setMainInstance(MainWindow *hInst)
{
    mMainInst = hInst;
}

void MyThread::setCommand(QString _cmd)
{
    cmd = _cmd;
}

void MainWindow::on_cmbType_currentIndexChanged(int index)
{
    cmdType = index;
}

void MainWindow::on_btnClear_clicked()
{
    output = "";
    ui->plainTextEdit->setPlainText("");
}
