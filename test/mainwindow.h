#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
#include <QProcess>
#include <QPlainTextEdit>
#include <QThread>

namespace Ui {
class MainWindow;
}

class MyThread;

class QUserEvent : public QEvent {
public:
    QUserEvent(QEvent::Type type, int wparam = 0, int lparam = 0);

    int wParam() { return iwParam; }
    int lParam() { return ilParam; }
    void setParam(int wparam, int lparam) { iwParam = wparam; ilParam = lparam; }

private:
    int iwParam;
    int ilParam;
};

class MainWindow : public QMainWindow
{
    Q_OBJECT

public:
    explicit MainWindow(QWidget *parent = nullptr);
    ~MainWindow();
    void showOutput(QString out);
    virtual bool    EventUser(int uMsg, int wParam, int lParam);
private:
    Ui::MainWindow *ui;
    QProcess *process;
    QString keyText;
    QPlainTextEdit *pet;
    MyThread *cmdThread;
    QString output;
public:
    int cmdType;
protected:
    void    customEvent(QEvent * event);

private slots:
    void asd(int);
//    void on_plainTextEdit_textChanged();
//    void on_plainTextEdit_blockCountChanged(int newBlockCount);
    void on_lineEdit_editingFinished();
    void on_cmbType_currentIndexChanged(int index);
    void on_btnClear_clicked();
};

class MyThread : public QThread
{
public:
    MyThread();
    virtual void run();
    void setMainInstance(MainWindow* hInst);
    void setCommand(QString _cmd);
private:
    MainWindow* mMainInst;
    QString cmd;
};

#endif // MAINWINDOW_H
