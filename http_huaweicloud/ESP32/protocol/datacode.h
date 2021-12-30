#ifndef DATACODE_H
#define DATACODE_H
#include "./ESP32/CRC/crc_8_maxim.h"
#include "./ESP32/protocol/datumcode.h"
#include "./ESP32/protocol/guidecode.h""
class DataCode
{
public:
    DataCode();
   ~DataCode();
    char datacode_create(QString SSID,QString PWD,QString IPv4_Address,QString Mac_Address);
  //  unsigned char *udp_data_broadcast[];
    uint16_t *udp_data_broadcast_9bit;
    GuideCode guidecode;
    DatumCode datumcode;


private:
    unsigned char *udp_data_broadcast;
    CRC_8_MAXIM crc_single;


    void Data_Create();
    void Data_8bit_To_9bit();

};

#endif // DATACODE_H
