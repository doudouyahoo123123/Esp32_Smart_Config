#include "./Huawei_cloud/json_datas.h"

#define IAMEndpoint "iam.cn-north-4.myhuaweicloud.com"
#define IOTDAEndpoint "a160ff9245.iotda.cn-north-4.myhuaweicloud.com"
#define IAMUserName "doudou"
#define IAMPassword "xiaodoudou123123"
#define IAMDoaminId "hid_n-rvm2sjo3v7ann"
#define region "cn-north-4"
#define project_id "0d1c48ebd4800f962f59c00ccd7f20cd"
#define product_id "6163e5d39fff74027dde2408"


Json_datas::Json_datas()
{
    _IAMEndpoint   = IAMEndpoint;
    _IOTDAEndpoint = IOTDAEndpoint;
    _project_id    = project_id;
}

QByteArray Json_datas::token_post_json()
{
    QJsonObject domain;
    domain.insert("name",IAMDoaminId);
    QJsonObject user;
    user.insert("domain",domain);
    user.insert("password",IAMPassword);
    user.insert("name",IAMUserName);
    QJsonObject password;
    password.insert("user",user);
    QJsonObject identity;
    QJsonArray Pa;
    Pa.append("password");
    identity.insert("methods",Pa);
    identity.insert("password",password);
    QJsonObject auth;
    auth.insert("identity",identity);
    QJsonObject scope;
    QJsonObject project;
    project.insert("name",region);
    scope.insert("project",project);
    auth.insert("scope",scope);
    QJsonObject json;//构建json对象json
    json.insert("auth",auth);

    QByteArray byteArray = QJsonDocument(json).toJson(QJsonDocument::Compact);
    return byteArray;
}

QByteArray Json_datas::register_post_json()
{
    QJsonObject auth_info;
    auth_info.insert("auth_type","SECRET");
    auth_info.insert("secure_access",true);
    auth_info.insert("fingerprint","dc0f1016f495157344ac5f1296335cff725ef22f");
    auth_info.insert("secret","3b935a250c50dc2c6d481d048cefdc3c");
    auth_info.insert("timeout",300);

    QJsonObject json;//构建json对象json
    json.insert("node_id",node_id);
    json.insert("device_name",device_name);
    json.insert("product_id",product_id);
    json.insert("auth_info",auth_info);
    json.insert("description","watermeter device");

    QByteArray byteArray = QJsonDocument(json).toJson(QJsonDocument::Compact);
    return byteArray;
}

void Json_datas::parse_id_secret(QByteArray parse_datas)
{

    QString create_time;


    QJsonParseError jsonError;
    QJsonDocument jsonDoc(QJsonDocument::fromJson(parse_datas, &jsonError));

    if(jsonError.error != QJsonParseError::NoError)
      {
        qDebug() << "json error!" << jsonError.errorString();
        return;
      }

    QJsonObject rootObj = jsonDoc.object();
    if(rootObj.contains("device_id"))
        device_id = rootObj["device_id"].toString();
    if(rootObj.contains("create_time"))
        create_time = rootObj["create_time"].toString();
    if(rootObj.contains("auth_info") && rootObj["auth_info"].isObject())
      {
        QJsonObject subObj = rootObj["auth_info"].toObject();
        if(subObj.contains("secret"))
            secret = subObj["secret"].toString();
      }

    hash_256.secret_encrypt(client_id,device_id,secret,create_time);

    qDebug() << "client_id" << client_id;
    qDebug() << "username" << device_id;
    qDebug() << "password" << secret;
}
