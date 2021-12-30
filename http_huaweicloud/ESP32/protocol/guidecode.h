#ifndef GUIDECODE_H
#define GUIDECODE_H
#include "./ESP32/CRC/crc_8_maxim.h"

class GuideCode
{
public:
    GuideCode();
    uint16_t *guide_data;
    void guidecode_create();
};

#endif // GUIDECODE_H
