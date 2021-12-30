#ifndef JSON_DATAS_H
#define JSON_DATAS_H

#include <QJsonArray>
#include <QJsonObject>
#include <QJsonDocument>
#include <QJsonParseError>

#include "./Huawei_cloud/hmacsha256.h"

class Json_datas
{
public:
    Json_datas();

    QByteArray X_Auth_Token;
    QString device_name;
    QString node_id;
    QString _IAMEndpoint;
    QString _IOTDAEndpoint;
    QString _project_id;
    QString _product_id;

    QString client_id;
    QString secret;
    QString device_id;

    QByteArray token_post_json();
    QByteArray register_post_json();
    void parse_id_secret(QByteArray parse_datas);

private:
    HmacSHA256 hash_256;

private:

};

#endif // JSON_DATAS_H
