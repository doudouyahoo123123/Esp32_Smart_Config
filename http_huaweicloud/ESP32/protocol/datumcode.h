#ifndef DATUMCODE_H
#define DATUMCODE_H
#include <QString>
#include "./ESP32/CRC/crc_8_maxim.h"

class DatumCode
{
public:
    DatumCode();
    char datumcode_create(QString SSID,QString PWD,QString IPv4_Address,QString Mac_Address);

    unsigned char totaldata_len;
    unsigned char password_len;
    unsigned char ssid_crc8;
    unsigned char bssid_crc8;
    unsigned char total_data_xor;
    char ssid_len;
    unsigned char bssid[6];
    unsigned char ipv4[4];
    unsigned char *ssid;
    unsigned char *pwd;

private:
    CRC_8_MAXIM crc_8;
    void Mac_Parse(QString input);
    void IPv4_Parse(QString input);
    void Total_Data_xor(unsigned char Totaldata_Len,unsigned char Password_Len,
                        unsigned char Ssid_Crc8,unsigned char Bssid_Crc8, unsigned char *Ipv4,
                        unsigned char *Pwd,unsigned char *Ssid);


};

#endif // DATUMCODE_H
