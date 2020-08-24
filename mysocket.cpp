#include "mysocket.h"

MySocket::MySocket()
{
    //timer_try_connect.start(1000);

    connect(&timer_try_connect, &QTimer::timeout,
            this, &MySocket::try_connect);
}

void MySocket::try_connect(){
    if(flag_connect == true){
        timer_try_connect.stop();
    }else{
        qDebug() << "попытка подключения";
        delete socket;
        socket = new QTcpSocket(this);
        socket->connectToHost("127.0.0.1", 4001);
        connect(socket, &QTcpSocket::connected, this,
                &MySocket::new_connect);

        connect(socket, &QTcpSocket::disconnected, this,
                &MySocket::connecting_lost);
    }
}


void MySocket::new_connect(){
    flag_connect = true;
    connect(socket, &QTcpSocket::readyRead,
            this, &MySocket::new_msg);
    qDebug() << "Есть соединение!";
    emit unblock();
    emit send_status_server(true);
}


void MySocket::new_msg(){
    // приём пакета
    QByteArray temp = socket->readAll();
    // разбор пакета и замена 7d
    for(int i = 0; i < temp.size(); i++){
        if(temp[i] != (char)0x7d){
            msg += temp[i];
        }else if(temp[i] == (char)0x7d ||
                 temp[i+1] == (char)0x5e){
            msg += (char)0x7e;
            i++;
        }else if(temp[i] == (char)0x7d ||
                 temp[i+1] == (char)0x5d){
            msg += (char)0x7d;
            i++;
        }
    }
    // проверка контрольной суммы
    unsigned char temp_ks = 0;
    for(int i = 1; i < msg.size() - 2; i++){
        temp_ks += msg[i];
    }
    control_sum -= temp_ks;
    if(control_sum == (unsigned char)msg[msg.size() - 2]){
        //emit got_new_msg(temp);
        switch (msg[1]) {
        case (char)0x19:
            emit got_new_msg_from_48_adr19(temp);
            break;
        case (char)0x15:
            emit got_new_msg_from_10_adr15(temp);
            break;
        case (char)0x16:
            emit got_new_msg_from_10_adr16(temp);
            break;
        case (char)0x17:
            emit got_new_msg_from_10_adr17(temp);
            break;
        case (char)0x76:
            emit got_new_msg_from_81_adr76(temp);
            break;
        case (char)0x5f:
            emit got_new_msg_from_24_adr5f(temp);
            break;
        case (char)0x66:
            emit got_new_msg_from_23_adr66(temp);
            break;
        }
        if(msg[1] >= (char)0x1f && msg[1] <= (char)0x4f){
            emit got_new_msg_from_22_adr1f_4f(temp);
        }
        if(msg[1] >= (char)0x6f && msg[1] <= (char)0x75){
            emit got_new_msg_from_19_adr6f_75(temp);
        }
    }else{
        qDebug() << "incorrect control sum  " << msg[1] << "  cs - " << control_sum << "  " << (unsigned char)msg[msg.size() - 2];
    }
    msg.clear();
    control_sum = 255;
}


void MySocket::send_msg(QByteArray smsg){
    socket->write(smsg);
    socket->waitForReadyRead(100);
}


void MySocket::connecting_lost(){
    socket->close();
    qDebug() << "нет соединения";
    emit send_status_server(false);
    flag_connect = false;
    if(flag_request == true){
        timer_try_connect.start(1000);
    }
}


void MySocket::start_timer_try_connect(bool flag){
    flag_request = flag;
    if(flag_connect == false && flag_request == true){
        timer_try_connect.start(1000);
    }else{
        timer_try_connect.stop();
    }
}
