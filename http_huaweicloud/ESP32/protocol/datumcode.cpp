#include "datumcode.h"
#include <QDebug>
DatumCode::DatumCode()
{
   CRC_8_MAXIM crc_8;
}

 char DatumCode::datumcode_create(QString SSID,QString PWD,QString IPv4_Address,QString Mac_Address)
 {
    qDebug() << SSID << PWD << IPv4_Address << Mac_Address;

    IPv4_Parse(IPv4_Address);         //对IPv4_Address拆分
    Mac_Parse(Mac_Address);           //对Mac_Address拆分

    QByteArray temp_ssid = SSID.toLocal8Bit();   //对SSID拆分
    ssid = (unsigned char *)temp_ssid.data();

    QByteArray temp_pwd = PWD.toLocal8Bit();     //对PWD拆分
    pwd = (unsigned char *)temp_pwd.data();

    password_len = (char)PWD.length();
    ssid_len = (char)SSID.length();
    totaldata_len = password_len + ssid_len + 5 + 4;

    ssid_crc8 = crc_8.Crc8(ssid,(int)ssid_len);
    bssid_crc8 = crc_8.Crc8(bssid,sizeof(bssid));

    Total_Data_xor(totaldata_len,password_len,ssid_crc8,bssid_crc8,ipv4,pwd,ssid);

 }

void DatumCode::IPv4_Parse(QString input)
 {
     int temp = 0;
     QString temp1="";
     memset(bssid,0,sizeof(bssid));

     for(int i=0,j=0; i < input.length();i++)
     {
        if(input.at(i) >= '0' && input.at(i) <= '9')
         {
             temp1.append(input.at(i).toLatin1() - '0');
         }

      if(input.at(i) == "." || i == (input.length()-1))
        {
            if(temp1.length() == 3)
                temp = (int)temp1[0].toLatin1()*100 + (int)temp1[1].toLatin1()*10 + (int)temp1[2].toLatin1();
               else if(temp1.length() == 2)
                   temp = (int)temp1[0].toLatin1()*10 + (int)temp1[1].toLatin1();
                   else if(temp1.length() == 1)
                       temp = (int)temp1[0].toLatin1();

             temp1.clear();
             ipv4[j] = (unsigned char)temp;
             temp = 0;
             j++;
         }
}
}

void DatumCode::Mac_Parse(QString input)
 {
     int counter = 0;
     memset(bssid,0,sizeof(bssid));

     for(int i=0,j=0; i < input.length();i++)
     {
         char temp;

         if(input.at(i) != ":")
         {
             if(input.at(i) >= '0' && input.at(i) <= '9')
                 temp = input.at(i).toLatin1() - '0';
               else if(input.at(i) >= 'a' && input.at(i) <= 'z')
                     temp = input.at(i).toLatin1() - 'a' + 10;
                    else if(input.at(i) >= 'A' && input.at(i) <= 'Z')
                         temp = input.at(i).toLatin1() - 'A' + 10;

             if(!counter)
             {
                 bssid[j] = bssid[j] | (temp << 4);
                 counter = 1;
             }
             else
             {
                 bssid[j] = bssid[j] | (temp);
                 counter = 0;
                 j++;
             }
         }
     }
 }



void DatumCode::Total_Data_xor(unsigned char Totaldata_Len,unsigned char Password_Len,
                               unsigned char Ssid_Crc8,unsigned char Bssid_Crc8, unsigned char *Ipv4,
                               unsigned char *Pwd,unsigned char *Ssid)
{
    total_data_xor = 0;
    total_data_xor = total_data_xor ^ Totaldata_Len;
    total_data_xor = total_data_xor ^ Password_Len;
    total_data_xor = total_data_xor ^ Ssid_Crc8;
    total_data_xor = total_data_xor ^ Bssid_Crc8;

    for(int i=0; i < 4 ; i++ )
    total_data_xor = total_data_xor ^ Ipv4[i];

    for(int i=0; i < (int)Password_Len ; i++ )
    total_data_xor = total_data_xor ^ Pwd[i];

    for(int i=0; i < (int)ssid_len ; i++ )
    total_data_xor = total_data_xor ^ Ssid[i];

  //  qDebug() << "total_data_xor" << (int)total_data_xor;
}
