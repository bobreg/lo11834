#include "d2ag022.h"

d2ag022::d2ag022(QObject *parent) : QObject(parent)
{

}


void d2ag022::get_status(unsigned char adr){
    adress = adr;
    control_summ = 0xff - (adr + 0x00);
    request_status[1] = adress;
    request_status[3] = control_summ;
    for(auto i : request_status){
        request += i;
    }
    qDebug() << "запрос к 22 ячейке по адресу:" << adress<< request.toHex(' ').toUpper();
    emit send_request(request);
    request.clear();
}


bool d2ag022::analyze_answer(){
    qDebug() << "ответ" << answer.toHex(' ') << "\n";
    if(answer[3] == (char)0x03){
        answer.clear();
        return true;
    }else{
        answer.clear();
        return false;
    }
}


void d2ag022::received_msg(QByteArray msg){
    answer = msg;
}
