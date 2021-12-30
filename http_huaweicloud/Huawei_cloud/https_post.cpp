#include "./Huawei_cloud/https_post.h"

https_post::https_post(QObject *parent) : QObject(parent)
{
    m_accessManager= new QNetworkAccessManager(this);
    Json_datas json_datas;
    connect(m_accessManager, SIGNAL(finished(QNetworkReply*)), this, SLOT(slot_replayFinished(QNetworkReply*))); //关联信号和槽
}

void https_post::slot_replayFinished(QNetworkReply *reply)
{
  if(get_token)
    for( int i=0; i< reply->rawHeaderPairs().size(); ++i)
    {
        if(reply->rawHeaderPairs().at(i).first=="X-Subject-Token")
           {
            json_datas.X_Auth_Token = reply->rawHeaderPairs().at(i).second;
            qDebug() << "X-Subject-Token" << "get";
           }
    }
  get_token = false;

  if(get_register)
    {
       json_datas.parse_id_secret(reply->readAll());
       get_register = false;
       emit regist_done(true);
    }
    reply->deleteLater();//最后要释放replay对象
}

void https_post::token_post()
{
    get_token = true;
    QNetworkRequest request;
    QString url = QString("https://%1/v3/auth/tokens").arg(json_datas._IAMEndpoint);

    request.setUrl(QUrl(url));
    request.setRawHeader("Content-Type","application/json");

    QByteArray byteArray = json_datas.token_post_json();
    m_accessManager->post(request,byteArray);
}

void https_post::register_post()
{
    get_register = true;
    QNetworkRequest request;
    QString url = QString("https://%1/v5/iot/%2/devices").arg(json_datas._IOTDAEndpoint).arg(json_datas._project_id);

    request.setUrl(QUrl(url));
    request.setRawHeader("Content-Type","application/json");
    request.setRawHeader("X-Auth-Token",json_datas.X_Auth_Token);

    QByteArray byteArray = json_datas.register_post_json();
    m_accessManager->post(request,byteArray);
}

