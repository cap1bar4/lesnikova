#ifndef MYSERVER_H
#define MYSERVER_H
#include <QObject>
#include <QTcpServer>
#include <QAbstractSocket>

#include <QtNetwork>
#include <QByteArray>
#include <QDebug>

class MyTcpServer : public QObject
{
    Q_OBJECT
public:
    explicit MyTcpServer(QObject *parent = nullptr);
    ~MyTcpServer();
public slots:
    void slotNewConnection();
    void slotClientDisconnected();
    void slotServerRead();
    //void slotReadClient();
private:
    QTcpServer * mTcpServer;
    QMap<QTcpSocket*, int> Clients;
    int server_status;
};

#endif // MYSERVER_H







