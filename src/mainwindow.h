#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
#include <QtNetwork>
#include <host.h>
#include <client.h>

namespace Ui {
class MainWindow;
}

class MainWindow : public QMainWindow
{
    Q_OBJECT

public:
    explicit MainWindow(QWidget *parent = 0);
    ~MainWindow();

private:
    Ui::MainWindow *ui;
    Host *host;
    Client *client;
    QTimer *timer;

public slots:
    void startClient();
    void check4Host();
    void startHost();
    void updateClientList();
    void checkStartMatch();
private slots:
    void on_btn_ForceMatchStart_clicked();
};

#endif // MAINWINDOW_H
