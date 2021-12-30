#include "tcp_server.h"
#include <QDebug>

Tcp_Server::Tcp_Server(QObject *parent) : QObject(parent)
{
    tcp_server = new QTcpServer();
    port = 6666;
    if(!tcp_server->listen(QHostAddress::Any, port))
           {
               //若出错，则输出错误信息
               qDebug()<<tcp_server->errorString();
               return;
           }
           //修改按键文字
    else
        qDebug()<< "Listen succeessfully!";

        //连接信号槽
    QObject::connect(tcp_server,&QTcpServer::newConnection,this,&Tcp_Server::server_New_Connect);
}


void Tcp_Server::server_New_Connect()
{
    //获取客户端连接
       tcp_socket = tcp_server->nextPendingConnection();
       //连接QTcpSocket的信号槽，以读取新数据
       QObject::connect(tcp_socket, &QTcpSocket::readyRead, this, &Tcp_Server::socket_Read_Data);
       QObject::connect(tcp_socket, &QTcpSocket::disconnected, this, &Tcp_Server::socket_Disconnected);

       qDebug() << "A Client connect!";
}


void Tcp_Server::socket_Read_Data()
    {
        QByteArray buffer;
        //读取缓冲区数据
        buffer = tcp_socket->readAll();
        if(!buffer.isEmpty())
        {
           emit SendText(buffer);
           qDebug() << "buffer:" << buffer;
        }
    }

void Tcp_Server::socket_Disconnected()
{
    qDebug() << "Disconnected!";
    tcp_server->close();
    tcp_server->deleteLater();

    tcp_socket->close();
    tcp_socket->deleteLater();

    delete tcp_server;
    delete tcp_socket;
}

void Tcp_Server::tcp_send(QString data)
{
    tcp_socket->write(data.toLatin1());
    tcp_socket->flush();
}
