#ifndef HTTPS_POST_H
#define HTTPS_POST_H

#include <QObject>
#include <QNetworkAccessManager>
#include <QNetworkReply>
#include <QNetworkRequest>

#include "./Huawei_cloud/json_datas.h"


class https_post : public QObject
{
    Q_OBJECT
public:
    explicit https_post(QObject *parent = nullptr);
    void token_post();
    void project_management_post();
    void register_post();
    Json_datas json_datas;

private:
    QNetworkAccessManager *m_accessManager;
    bool get_token = 0;
    bool get_register = 0;


private slots:
    void slot_replayFinished(QNetworkReply *reply);

signals:
    void regist_done(bool test);
};

#endif // WIDGET_H

