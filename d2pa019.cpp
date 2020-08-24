#include "d2pa019.h"

d2pa019::d2pa019(QObject *parent) : QObject(parent)
{

}


void d2pa019::get_status(unsigned char adr){
    adress = adr;
    control_summ = 0xff - (adr + 0x0a);
    request_status[1] = adress;
    request_status[3] = control_summ;
    for(auto i : request_status){
        request += i;
    }
    qDebug() << "запрос к 19 ячейке по адресу:" << adress<< request.toHex(' ').toUpper();
    emit send_request(request);
    request.clear();
}


bool d2pa019::analyze_answer(){
    qDebug() << "ответ" << answer.toHex(' ') << "\n";
    if((answer[3] & 0b11111110) == (char)0x00){
        answer.clear();
        return true;
    }else{
        answer.clear();
        return false;
    }
}


void d2pa019::received_msg(QByteArray msg){
    answer = msg;
}
