#include "udp_broadcast.h"

Udp_Broadcast::Udp_Broadcast()
{
    broadcast_index = true;
 }

void Udp_Broadcast::run()
{
    udp_socket = new  QUdpSocket;
    QElapsedTimer timer;
    timer.start();
    counter = 0;
    QElapsedTimer timer1;

    while(broadcast_index){
    timer.restart();

    while (!timer.hasExpired(2000))        //单位ms
     {
        timer1.restart();
         udp_socket->writeDatagram(guide_557, QHostAddress::Broadcast,3333);
         while (!timer1.hasExpired(10))
         {}
        timer1.restart();
        // sleep(10);
         udp_socket->writeDatagram(guide_556, QHostAddress::Broadcast,3333);
         while (!timer1.hasExpired(10))
         {}
        timer1.restart();
       //  sleep(10);
         udp_socket->writeDatagram(guide_555, QHostAddress::Broadcast,3333);
         while (!timer1.hasExpired(10))
         {}
        timer1.restart();
      //   sleep(10);
         udp_socket->writeDatagram(guide_554, QHostAddress::Broadcast,3333);
         while (!timer1.hasExpired(10))
         {}
    }

    timer.restart();
    while(!timer.hasExpired(4000))
    {
        for(int i=0; i<datacode_vector->size();i++)
        {
            timer1.restart();
            udp_socket->writeDatagram(datacode_vector->at(i), QHostAddress::Broadcast,3333);
            while (!timer1.hasExpired(10))
            {}
        }
    }
    counter++;
    qDebug() << "done counter" << counter;

    if(counter == 10){
        qDebug() << "Udp_Broadcast timeout!!";
        delete udp_socket;
        break;
    }
    }
    qDebug() << "Udp_Broadcast is over";
    delete udp_socket;
}



void Udp_Broadcast::data_collection(uint16_t *guide_code,uint16_t *datacode,int lenth_datacode)
{
   datacode_vector = new QVector <QByteArray>;
  // datacode_vector->resize(4);
   guide_557.resize((int) guide_code[0]);
   guide_556.resize((int) guide_code[1]);
   guide_555.resize((int) guide_code[2]);
   guide_554.resize((int) guide_code[3]);

   guide_557.fill(1);
   guide_556.fill(1);
   guide_555.fill(1);
   guide_554.fill(1);

   for(int i = 0;i<lenth_datacode;i++)
   {
       QByteArray temp;
       temp.resize((int)datacode[i]);
       temp.fill(1);
       datacode_vector->push_back(temp);
   }

//   for(int i=0;i<datacode_vector->size();i++)
//    qDebug() << "test" << datacode_vector->at(i).size();
}
