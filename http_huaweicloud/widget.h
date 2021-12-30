#ifndef WIDGET_H
#define WIDGET_H

#include <QWidget>
#include <QHostAddress>
#include <QHostInfo>
#include <QNetworkInterface>
#include <QNetworkConfigurationManager>

#include "./ESP32/protocol/datacode.h"
#include "./ESP32/protocol/datumcode.h"
#include "./ESP32/protocol/guidecode.h"
#include "./ESP32/Udp/udp_broadcast.h"
#include "./ESP32/Tcp/tcp_server.h"
#include "./Huawei_cloud/https_post.h"

namespace Ui {
class Widget;
}

class Widget : public QWidget
{
    Q_OBJECT

public:
    explicit Widget(QWidget *parent = 0);
    ~Widget();

private slots:
    void on_pushButton_clicked();
    void on_BroadCast_pushButton_clicked();

    void on_SSID_checkBox_clicked(bool checked);

    void on_PWD_checkBox_clicked(bool checked);

private:
    Ui::Widget *ui;
    https_post *post;

    DataCode datacode;
    QString IPv4_Address;
    QString Mac_Address;
    Udp_Broadcast *udp_broadcast;
    Tcp_Server *tcp_server;

    void Get_IPv4_Address();
    void Get_Mac_Address();
    void RecText(QByteArray data);
    void Rec_Regist(bool test);

signals:

};

#endif // WIDGET_H
