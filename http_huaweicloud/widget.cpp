#include "widget.h"
#include "ui_widget.h"

#include <QMessageBox>

Widget::Widget(QWidget *parent) :
    QWidget(parent),
    ui(new Ui::Widget)
{
    ui->setupUi(this);
    ui->Show_textEdit->setText("请将手机连接wifi，且所连wifi设备对应左部框内信息");
    ui->SSID_lineEdit->setText("MechMaker");
    ui->PWD_lineEdit->setText("05922181196");
    ui->SSID_checkBox->setChecked(true);
    ui->PWD_checkBox->setChecked(true);
    ui->SSID_lineEdit->setDisabled(true);
    ui->PWD_lineEdit->setDisabled(true);
  //  ui->pushButton->hide();

    qDebug() << "Device supports OpenSSL: " << QSslSocket::supportsSsl();
    udp_broadcast = new Udp_Broadcast();
    tcp_server = new Tcp_Server;
    post = new https_post;

    post->token_post();

    Get_IPv4_Address();
    Get_Mac_Address();

    connect(tcp_server,&Tcp_Server::SendText,this,&Widget::RecText);
    connect(post,&https_post::regist_done,this,&Widget::Rec_Regist);
}

Widget::~Widget()
{
    delete ui;
}


void Widget::on_pushButton_clicked()
{
    QString temp = ui->comboBox->currentText();
    temp.replace("\n","");
    post->json_datas.device_name = temp + "_" + ui->textEdit_2->toPlainText();

    switch( ui->comboBox->currentIndex())
        {
            case 0:    temp = "temperature_huminity"; break;
            case 1:    temp = "carbon_dioxide";break;
            default:   temp = "none"; break;
        }
   // post.json_datas.node_id = temp + "_" + ui->textEdit_2->toPlainText();

    post->json_datas.node_id = "ESP32_Test" + ui->textEdit_2->toPlainText();
    post->register_post();
}

void Widget::on_BroadCast_pushButton_clicked()
{
    datacode.datacode_create(ui->SSID_lineEdit->text(),ui->PWD_lineEdit->text(),IPv4_Address,Mac_Address);
    udp_broadcast->data_collection(datacode.guidecode.guide_data,datacode.udp_data_broadcast_9bit,(int)datacode.datumcode.totaldata_len*3);
    udp_broadcast->start();
}

void Widget::RecText(QByteArray data)
{
    ui->Show_textEdit->setText(data);
    if(data == "SmartConfig is over")
     {
        ui->pushButton->show();
        udp_broadcast->broadcast_index = false;
    }
    else if(data.contains("Esp32_id"))
    {
         post->json_datas.node_id = data.mid(9);  // 例如Esp32_id：test12345678,则node_id为test12345678
         post->json_datas.device_name = ui->textEdit_2->toPlainText();//用来给客户自定义备注
         post->register_post();                //将获取到的ESP32信息注册到华为云上，由于https过程是信号和槽完成，有时间差，所以在此用Rec_Regist进行转发
    }
}


void Widget::Get_IPv4_Address()
{
    QString localHostName = QHostInfo::localHostName();
    QHostInfo info = QHostInfo::fromName(localHostName);

    foreach(QHostAddress address,info.addresses())
    {
         if(address.protocol() == QAbstractSocket::IPv4Protocol)
           {  qDebug() <<"IPv4_address" <<address.toString();
             }
        ui->Show_textEdit->append(address.toString());
         ui->Show_textEdit->append("哎呀");
    }
    IPv4_Address = "192.168.1.110";

}


void Widget::Get_Mac_Address()
{
    QString text;
    foreach(QNetworkInterface interface, QNetworkInterface::allInterfaces())
        {
            text += "Interface:"+interface.hardwareAddress()+"\n";
            if (!(interface.flags() & QNetworkInterface::IsRunning))
            {
              text = interface.hardwareAddress();
             // qDebug() <<"Mac Address" << text;
           //   qDebug() <<"Mac Address" << interface.name();
            }
    Mac_Address = "C2:5B:D8:D9:1A:73";
}
}


void Widget::Rec_Regist(bool test)
{
    tcp_server->tcp_send(post->json_datas.client_id);
    tcp_server->tcp_send(post->json_datas.device_id);
    tcp_server->tcp_send(post->json_datas.secret);
}

void Widget::on_SSID_checkBox_clicked(bool checked)
{
    if(checked)
        ui->SSID_lineEdit->setDisabled(true);
      else
        ui->SSID_lineEdit->setDisabled(false);
}

void Widget::on_PWD_checkBox_clicked(bool checked)
{
    if(checked)
        ui->PWD_lineEdit->setDisabled(true);
      else
        ui->PWD_lineEdit->setDisabled(false);
}
