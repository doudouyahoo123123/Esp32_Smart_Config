#include "datacode.h"
#include <QDebug>
DataCode::DataCode()
{
    udp_data_broadcast = new unsigned char[datumcode.totaldata_len*3];
    memset(udp_data_broadcast,0,sizeof(udp_data_broadcast));
}
DataCode::~DataCode()
{
    delete udp_data_broadcast_9bit;
}


char DataCode::datacode_create(QString SSID,QString PWD,QString IPv4_Address,QString Mac_Address)
{
    guidecode.guidecode_create();
    datumcode.datumcode_create(SSID,PWD,IPv4_Address,Mac_Address);
    Data_Create();
    Data_8bit_To_9bit();

}


void DataCode::Data_Create()
{
    int index = 0;
    udp_data_broadcast[index*3] = crc_single.Crc8(datumcode.totaldata_len,index) & 0xF0;
    udp_data_broadcast[index*3] = udp_data_broadcast[index*3] | ((datumcode.totaldata_len & 0xF0) >> 4);

    udp_data_broadcast[index*3+1] = index;
    udp_data_broadcast[index*3+2] = (crc_single.Crc8(datumcode.totaldata_len,index) & 0x0F) << 4;
    udp_data_broadcast[index*3+2] = udp_data_broadcast[index*3+2] | ((datumcode.totaldata_len) & 0x0F);

    index++;
    udp_data_broadcast[index*3] = crc_single.Crc8(datumcode.password_len,index) & 0xF0;
    udp_data_broadcast[index*3] = udp_data_broadcast[index*3] | ((datumcode.password_len & 0xF0) >> 4);
    udp_data_broadcast[index*3+1] = index;
    udp_data_broadcast[index*3+2] = (crc_single.Crc8(datumcode.password_len,index) & 0x0F) << 4;
    udp_data_broadcast[index*3+2] = udp_data_broadcast[index*3+2] | ((datumcode.password_len) & 0x0F);

    index++;
    udp_data_broadcast[index*3] = crc_single.Crc8(datumcode.ssid_crc8,index) & 0xF0;
    udp_data_broadcast[index*3] = udp_data_broadcast[index*3] | ((datumcode.ssid_crc8 & 0xF0) >> 4);
    udp_data_broadcast[index*3+1] = index;
    udp_data_broadcast[index*3+2] = (crc_single.Crc8(datumcode.ssid_crc8,index) & 0x0F) << 4;
    udp_data_broadcast[index*3+2] = udp_data_broadcast[index*3+2] | ((datumcode.ssid_crc8) & 0x0F);

    index++;
    udp_data_broadcast[index*3] = crc_single.Crc8(datumcode.bssid_crc8,index) & 0xF0;
    udp_data_broadcast[index*3] = udp_data_broadcast[index*3] | ((datumcode.bssid_crc8 & 0xF0) >> 4);
    udp_data_broadcast[index*3+1] = index;
    udp_data_broadcast[index*3+2] = (crc_single.Crc8(datumcode.bssid_crc8,index) & 0x0F) << 4;
    udp_data_broadcast[index*3+2] = udp_data_broadcast[index*3+2] | ((datumcode.bssid_crc8) & 0x0F);

    index++;
    udp_data_broadcast[index*3] = crc_single.Crc8(datumcode.total_data_xor,index) & 0xF0;
    udp_data_broadcast[index*3] = udp_data_broadcast[index*3] | ((datumcode.total_data_xor & 0xF0) >> 4);
    udp_data_broadcast[index*3+1] = index;
    udp_data_broadcast[index*3+2] = (crc_single.Crc8(datumcode.total_data_xor,index) & 0x0F) << 4;
    udp_data_broadcast[index*3+2] = udp_data_broadcast[index*3+2] | ((datumcode.total_data_xor) & 0x0F);

    for(int i=0; i < 4; i++)
    {
        index++;
        udp_data_broadcast[index*3] = crc_single.Crc8(datumcode.ipv4[i],index) & 0xF0;
        udp_data_broadcast[index*3] = udp_data_broadcast[index*3] | ((datumcode.ipv4[i] & 0xF0) >> 4);
        udp_data_broadcast[index*3+1] = 0x100 + index;
        udp_data_broadcast[index*3+2] = (crc_single.Crc8(datumcode.ipv4[i],index) & 0x0F) << 4;
        udp_data_broadcast[index*3+2] = udp_data_broadcast[index*3+2] | ((datumcode.ipv4[i]) & 0x0F);
    }

    for(int i=0; i < datumcode.password_len; i++)
    {
        index++;
        udp_data_broadcast[index*3] = crc_single.Crc8(datumcode.pwd[i],index) & 0xF0;
        udp_data_broadcast[index*3] = udp_data_broadcast[index*3] | ((datumcode.pwd[i] & 0xF0) >> 4);
        udp_data_broadcast[index*3+1] = index;
        udp_data_broadcast[index*3+2] = (crc_single.Crc8(datumcode.pwd[i],index) & 0x0F) << 4;
        udp_data_broadcast[index*3+2] = udp_data_broadcast[index*3+2] | ((datumcode.pwd[i]) & 0x0F);
    }

    for(int i=0; i < datumcode.ssid_len; i++)
    {
        index++;
        udp_data_broadcast[index*3] = crc_single.Crc8(datumcode.ssid[i],index) & 0xF0;
        udp_data_broadcast[index*3] = udp_data_broadcast[index*3] | ((datumcode.ssid[i] & 0xF0) >> 4);
        udp_data_broadcast[index*3+1] = index;
        udp_data_broadcast[index*3+2] = (crc_single.Crc8(datumcode.ssid[i],index) & 0x0F) << 4;
        udp_data_broadcast[index*3+2] = udp_data_broadcast[index*3+2] | ((datumcode.ssid[i]) & 0x0F);
    }


    /*for(int i=0;i <26*3;i++)
    qDebug() << QString("udp_data_broadcast[%1]").arg(i/3) <<  QString::number((int)udp_data_broadcast[i],16); */ //末尾“99”
}



void DataCode::Data_8bit_To_9bit()
{
    udp_data_broadcast_9bit = new uint16_t[datumcode.totaldata_len*3];
    memset(udp_data_broadcast_9bit,0,sizeof(udp_data_broadcast_9bit));

    for(int i=0;i <datumcode.totaldata_len;i++)
    {
        udp_data_broadcast_9bit[i*3]   = (0x00 << 8) + udp_data_broadcast[i*3];
        udp_data_broadcast_9bit[i*3+1] = (0x01 << 8) + udp_data_broadcast[i*3+1];
        udp_data_broadcast_9bit[i*3+2] = (0x00 << 8) + udp_data_broadcast[i*3+2];
    }

    for(int i=0;i <datumcode.totaldata_len*3;i++)
        udp_data_broadcast_9bit[i] = udp_data_broadcast_9bit[i] + 40;

/*    for(int i=0;i <26*3;i++)
    qDebug() << "udp_data_broadcast_9bit" << udp_data_broadcast_9bit[i]; */   //末尾153
}


