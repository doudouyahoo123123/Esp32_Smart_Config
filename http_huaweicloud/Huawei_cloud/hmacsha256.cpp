#include "./Huawei_cloud/hmacsha256.h"

HmacSHA256::HmacSHA256()
{

}

bool HmacSHA256::secret_encrypt(QString &client_id,QString &username,QString &password,QString time)
{
    QString  temp_time = time.mid(0,8) + time.mid(9,2);
    password = QMessageAuthenticationCode::hash(password.toLatin1(), temp_time.toLatin1(), QCryptographicHash::Sha256).toHex();
    client_id = username + "_0_0_" +temp_time;

}

