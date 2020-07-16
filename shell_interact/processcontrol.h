#ifndef PROCESSCONTROL_H
#define PROCESSCONTROL_H

#include <QObject>
#include <QProcess>
#include <iostream>
#include <QSocketNotifier>

using namespace std;

class ProcessControl : public QObject
{
    Q_OBJECT
public:
    explicit ProcessControl(QObject *parent = nullptr);

signals:

public slots:
    void execute();
    void showOutput();
private slots:
    void readCommand();
private:
    QString m_user_input;
//    QProcess* m_process;
//    QString m_input_str;
    QSocketNotifier *m_notifier;
};

#endif // PROCESSCONTROL_H
