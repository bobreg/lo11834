#include "d2vk023.h"

d2vk023::d2vk023(QObject *parent) : QObject(parent)
{

}


void d2vk023::get_status(){
    for(auto i : request_status){
        request += i;
    }
    qDebug() << "запрос к 23 ячейке" << request.toHex(' ').toUpper();
    emit send_request(request);
    request.clear();
}


bool d2vk023::analyze_answer(){
    qDebug() << "ответ" << answer.toHex(' ') << "\n";
    if(answer[2] == (char)0x00 &&
       answer[3] == (char)0x00 &&
       answer[4] == (char)0x00 &&
       answer[5] == (char)0x00 &&
       answer[6] == (char)0x00 &&
       answer[7] == (char)0x00 &&
       answer[8] == (char)0x00 &&
       answer[9] == (char)0x00 &&
       answer[answer.size() - 2] == (char)0x19){
        answer.clear();
        return true;
    }else{
        answer.clear();
        return false;
    }
}


void d2vk023::received_msg(QByteArray msg){
    answer = msg;
}
