#include "d2hk264.h"

d2hk264::d2hk264(QObject *parent) : QObject(parent)
{

}

void d2hk264::get_status(){

}

bool d2hk264::analyze_answer(){
    return true;
}

void d2hk264::received_msg(QByteArray msg){
    Q_UNUSED(msg);
}


void d2hk264::expand_antenna_ra_264(){

}


void d2hk264::fold_antenna_ra_264(){
    qDebug() << "сворачиваем антенну в РА";
}


void d2hk264::bild_send_message(){ // нет проверки 7E 7D

}
