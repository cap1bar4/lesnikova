#include "mytcpserver-ex.h"
#include "func.h"
#include <QDebug>
#include <QCoreApplication>

MyTcpServer::~MyTcpServer()
{
    mTcpServer->close(); // закрывает сервер
    server_status=0; // флаг для проверки статуса
}
MyTcpServer::MyTcpServer(QObject *parent) : QObject(parent){
    mTcpServer = new QTcpServer(this);
    connect(mTcpServer, &QTcpServer::newConnection,
            this, &MyTcpServer::slotNewConnection);

    if(!mTcpServer->listen(QHostAddress::Any, 33333)){
        qDebug() << "server is not started";
    } else {
        server_status=1;
        qDebug() << "server is started";
    }
}

void MyTcpServer::slotNewConnection(){
    if(server_status==1){
        qDebug() << "New client connected";

        QTcpSocket *mTcpSocket = mTcpServer->nextPendingConnection(); ///////////// важно
        mTcpSocket->write("Hello, World!!! I am echo server!\r\n");

        int connection_id = mTcpSocket->socketDescriptor();

        mTcpSocket->write("Your connection ID: ");
        mTcpSocket->write(QString::number(connection_id).toUtf8()); //отправлем номер подключения клиента к серверу закодированный в ютф8

        mTcpSocket->flush(); // насильно отправляет оставшуюся информацию на сокет

        Clients.insert(mTcpSocket, connection_id); ///////////// важно, заполняю Map

        connect(mTcpSocket, &QTcpSocket::readyRead,
                this,&MyTcpServer::slotServerRead);
        connect(mTcpSocket,&QTcpSocket::disconnected,
                this,&MyTcpServer::slotClientDisconnected);
    }
}

void MyTcpServer::slotServerRead(){
    QTcpSocket * mTcpSocket;
    mTcpSocket = (QTcpSocket*)sender(); // sender() возвращает указатель на объект, который отправил сигнал

    QByteArray array;
    QString string;

    while(mTcpSocket->bytesAvailable()>0)
    {
        array = mTcpSocket->readAll();
        string.append(array);
    }
    qDebug() << "recieve: "<<string;
    Parsing(string.toUtf8()); //отправляю в парсинг строку
}

void MyTcpServer::slotClientDisconnected(){
    QTcpSocket *mTcpSocket = (QTcpSocket*)sender();
    qDebug() << "Client disconnected";
    Clients.remove(mTcpSocket);
    mTcpSocket->close();
}
