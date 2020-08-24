#include "d2py081.h"

d2py081::d2py081(QObject *parent) : QObject(parent)
{

}


void d2py081::get_status(){
    for(auto i : request_status){
        request += i;
    }
    qDebug() << "запрос к 81 ячейке" << request.toHex(' ').toUpper();
    emit send_request(request);
    request.clear();
}


void d2py081::unblock_channels(){
    for(auto i : request_unblock_channel){
        request += i;
    }
    qDebug() << "попытка разблокировать каналы 81 ячейки" << request.toHex(' ').toUpper();
    emit send_request(request);
    request.clear();
}


bool d2py081::analyze_answer(){
    if((answer[3] & 0b11111100) == 0b11111100){
        answer.clear();
        return true;
    }else{
        answer.clear();
        return false;
    }
}


void d2py081::received_msg(QByteArray msg){
    qDebug() << "ответ" << msg.toHex(' ') << "\n";
    answer = msg;
}
