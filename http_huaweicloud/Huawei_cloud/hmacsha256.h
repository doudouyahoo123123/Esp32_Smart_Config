#ifndef HMACSHA256_H
#define HMACSHA256_H

#include <QString>
#include <QCryptographicHash>
#include <QMessageAuthenticationCode>
#include <QDebug>

class HmacSHA256
{
public:
    HmacSHA256();
    bool secret_encrypt(QString &client_id,QString &username,QString &password,QString time);
};

#endif // HMACSHA256_H
