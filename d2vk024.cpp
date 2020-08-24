#include "d2vk024.h"

d2vk024::d2vk024(QObject *parent) : QObject(parent)
{

}


void d2vk024::get_status(){
    for(auto i : request_status){
        request += i;
    }
    qDebug() << "запрос к 24 ячейке" << request.toHex(' ').toUpper();
    emit send_request(request);
    request.clear();
}


bool d2vk024::analyze_answer(){
    qDebug() << "ответ" << answer.toHex(' ') << "\n";
    //if(answer[3] == (char)0x01){
    if(answer == answer95){
        answer.clear();
        return true;
    }else{
        answer.clear();
        return false;
    }
}


void d2vk024::received_msg(QByteArray msg){
    answer = msg;
}

