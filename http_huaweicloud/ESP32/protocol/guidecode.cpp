#include "guidecode.h"

GuideCode::GuideCode()
{
    guide_data = new uint16_t[4];
    memset(guide_data,0,sizeof(guide_data)*2);
}

void GuideCode::guidecode_create()
{
    guide_data[0] = 515;
    guide_data[1] = 514;
    guide_data[2] = 513;
    guide_data[3] = 512;

}
