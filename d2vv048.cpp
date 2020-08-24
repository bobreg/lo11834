#include "d2vv048.h"

d2vv048::d2vv048(QObject *parent) : QObject(parent)
{

}


void d2vv048::get_status(){
    for(auto i : request_status){
        request += i;
    }
    qDebug() << "запрос к 48 ячейке" << request.toHex(' ').toUpper();
    emit send_request(request);
    request.clear();
}


void d2vv048::unblock_channels(){
    for(auto i : request_unblock_channel){
        request += i;
    }
    qDebug() << "попытка разблокировать 48 ячейку" << request.toHex(' ').toUpper();
    emit send_request(request);
    request.clear();
}


bool d2vv048::analyze_answer(){
    qDebug() << "ответ" << answer.toHex(' ') << "\n";
    if(answer[2] == (char)0x5a && answer[3] == (char)0xff && answer[4] == (char)0x01){
        answer.clear();
        return true;
    }else{
        answer.clear();
        return false;
    }
}


void d2vv048::received_msg(QByteArray msg){
    answer = msg;
}
