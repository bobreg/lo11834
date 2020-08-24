#include "d2va010.h"
#include <iostream>

d2va010::d2va010(int adress, QObject *parent) : QObject(parent), adress_cell(adress)
{
    //qDebug() << adress_cell;
}

void d2va010::get_status(){
    if(adress_cell == 21){
        for(auto i : request_get[0]){
            request += i;
        }
        qDebug() << "запрос к 10 ячейке по 21 адресу" << request.toHex(' ').toUpper();
        emit send_request(request);
        request.clear();
    }else if(adress_cell == 22){
        for(auto i : request_get[1]){
            request += i;
        }
        qDebug() << "запрос к 10 ячейке по 22 адресу" << request.toHex(' ').toUpper();
        emit send_request(request);
        request.clear();
    }else if(adress_cell == 23){
        for(auto i : request_get[2]){
            request += i;
        }
        qDebug() << "запрос к 10 ячейке по 23 адресу" << request.toHex(' ').toUpper();
        emit send_request(request);
        request.clear();
    }else{
        qDebug() << "неверный адрес ячейки Д2ВА010: " << adress_cell;
    }
}


bool d2va010::analyze_answer(){
    if(answer[1] == (char)0x15 && adress_cell == 21){
        //qDebug() << (int)answer[1] << " " << (answer == answer21) << "\n";
        if(answer == answer21){
            answer.clear();
            return true;
        }else{
            answer.clear();
            return false;
        }
    }else if (answer[1] == (char)0x16 && adress_cell == 22) {
        //qDebug() << (int)answer[1] << " " << (answer == answer22) << "\n";
        if(answer == answer22){
            answer.clear();
            return true;
        }else{
            answer.clear();
            return false;
        }
    }else if (answer[1] == (char)0x17 && adress_cell == 23) {
        //qDebug() << (int)answer[1] << " " << (answer == answer23) << "\n";
        if(answer == answer23){
            answer.clear();
            return true;
        }else{
            answer.clear();
            return false;
        }
    }else{
        answer.clear();
        return false;
    }
}


void d2va010::received_msg(QByteArray msg){
    qDebug() << "ответ" << msg.toHex(' ') << "\n";
    answer = msg;
}
