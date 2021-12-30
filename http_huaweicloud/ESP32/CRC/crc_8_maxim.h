#ifndef CRC_8_MAXIM_H
#define CRC_8_MAXIM_H
#include <QDebug>


typedef unsigned char u8;
typedef unsigned char byte;

class CRC_8_MAXIM
{
public:
    CRC_8_MAXIM();
    unsigned char Crc8(unsigned char *p,int index);
    unsigned char Crc8(unsigned char byte,unsigned char seq);

private:
    unsigned char crc8;
};

#endif // CRC_8_MAXIM_H
