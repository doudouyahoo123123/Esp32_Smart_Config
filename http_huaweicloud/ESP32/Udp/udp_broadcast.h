#ifndef UDP_BROADCAST_H
#define UDP_BROADCAST_H

#include <QObject>
#include <QUdpSocket>
#include <QVector>
#include <QElapsedTimer>
#include <QThread>

class Udp_Broadcast : public QThread
{
    Q_OBJECT
public:
    explicit Udp_Broadcast();
    void data_collection(uint16_t *guide_code,uint16_t *datacode,int lenth_datacode);
    int counter;
    bool broadcast_index;

public slots:
  //  void receive();

private:
    QUdpSocket *udp_socket;
  //  QUdpSocket *udp_socket_listen;
    QByteArray guide_557;
    QByteArray guide_556;
    QByteArray guide_555;
    QByteArray guide_554;
    QVector <QByteArray> *datacode_vector;
   // QUdpSocket *udp_socket;
    void stop_broadcast_rec(bool stop_index);
protected:
     void run();
signals:
     void SendText(QByteArray data);



};

#endif // UDP_BROADCAST_H
