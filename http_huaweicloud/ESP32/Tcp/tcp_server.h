#ifndef TCP_SERVER_H
#define TCP_SERVER_H

#include <QObject>
#include <QTcpServer>
#include <QTcpSocket>

class Tcp_Server : public QObject
{
    Q_OBJECT
public:
    explicit Tcp_Server(QObject *parent = nullptr);
    void tcp_send(QString data);

private:
    int port;
    QTcpServer *tcp_server;
    QTcpSocket *tcp_socket;

private slots:
    void server_New_Connect();
    void socket_Read_Data();
    void socket_Disconnected();

signals:
    void SendText(QByteArray data);
};

#endif // TCP_SEVER_H
