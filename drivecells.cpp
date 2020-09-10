#include "drivecells.h"

driveCells::driveCells(QObject *parent) : QObject(parent)
{ 
// инициализация словаря для хранения статусов 22 и 19 ячеек
    for(int i = 31; i < 79; i++){
        flag_status_cells_22.insert(i, false);
    }
    for(int i = 111; i < 118; i++){
        flag_status_cells_19.insert(i, false);
    }

//------
    connect(&socket, &MySocket::send_status_server,
            this, &driveCells::requests_go);


    connect(&timer_requests, &QTimer::timeout,
            this, &driveCells::requests_in_process);

    connect(this, &driveCells::send_flag_connect,
            &socket, &MySocket::start_timer_try_connect);

//соединение с сокетом 48 ячейки
    connect(&cell_48, &d2vv048::send_request,
            &socket, &MySocket::send_msg);
    connect(&socket, &MySocket::got_new_msg_from_48_adr19,
            &cell_48, &d2vv048::received_msg);
//соединение с сокетом 10 ячеек
    connect(&cell_10_21, &d2va010::send_request,
            &socket, &MySocket::send_msg);
    connect(&socket, &MySocket::got_new_msg_from_10_adr15,
            &cell_10_21, &d2va010::received_msg);

    connect(&cell_10_22, &d2va010::send_request,
            &socket, &MySocket::send_msg);
    connect(&socket, &MySocket::got_new_msg_from_10_adr16,
            &cell_10_22, &d2va010::received_msg);

    connect(&cell_10_23, &d2va010::send_request,
            &socket, &MySocket::send_msg);
    connect(&socket, &MySocket::got_new_msg_from_10_adr17,
            &cell_10_23, &d2va010::received_msg);

// соединение с сокетом 81 ячейки
    connect(&cell_81, &d2py081::send_request,
            &socket, &MySocket::send_msg);
    connect(&socket, &MySocket::got_new_msg_from_81_adr76,
            &cell_81, &d2py081::received_msg);

// соединение с сокетом 24 ячейки
    connect(&cell_24, &d2vk024::send_request,
            &socket, &MySocket::send_msg);
    connect(&socket, &MySocket::got_new_msg_from_24_adr5f,
            &cell_24, &d2vk024::received_msg);

// соединение с сокетом 23 ячейки
    connect(&cell_23, &d2vk023::send_request,
            &socket, &MySocket::send_msg);
    connect(&socket, &MySocket::got_new_msg_from_23_adr66,
            &cell_23, &d2vk023::received_msg);

// соединение с сокетом 22 ячейки
    connect(&cells_22, &d2ag022::send_request,
            &socket, &MySocket::send_msg);
    connect(&socket, &MySocket::got_new_msg_from_22_adr1f_4f,
            &cells_22, &d2ag022::received_msg);

// соединение с сокетом 19 ячейки
    connect(&cells_19, &d2pa019::send_request,
            &socket, &MySocket::send_msg);
    connect(&socket, &MySocket::got_new_msg_from_19_adr6f_75,
            &cells_19, &d2pa019::received_msg);

}

// если есть подключение к серверу и флаг опроса true, то опра4шиваем раз в секунду
void driveCells::requests_go(bool flag){
    if(flag == true){
        timer_requests.start(3000);
    }else{
        timer_requests.stop();
        emit asku_status(false);
    }
}


void driveCells::requests_in_process(){
    if(enable_request == true){
        qDebug() << "прошли по кругу-----------------------------------------------------";
        cell_48.get_status();  //опрос 48 ячейки
        flag_status_cell_48 = cell_48.analyze_answer(); //получение состояния 48 ячейки
        if(flag_status_cell_48 == true){ // если каналы ячейки открыты, то будем порашивать остальные ячейки
            emit asku_status(true);
            cell_10_21.get_status();  // опрос 21 ячеек
            flag_status_cell_10_21 = cell_10_21.analyze_answer();
            cell_10_22.get_status();
            flag_status_cell_10_22 = cell_10_22.analyze_answer();
            cell_10_23.get_status();
            flag_status_cell_10_23 = cell_10_23.analyze_answer();
            cell_81.get_status();
            flag_status_cell_81 = cell_81.analyze_answer();  // опрос 81 ячейки
            if(flag_status_cell_81 == false){ // если у 81 ячейки каналы закрыты, то попытаемся их открыть
                cell_81.unblock_channels();
            }else{  // опрос 22 ячеек
                for(int i = 31; i < 79; i++){
                    cells_22.get_status(i);
                    flag_status_cells_22.insert(i, cells_22.analyze_answer());
                }
            }
            cell_24.get_status();
            flag_status_cell_24 = cell_24.analyze_answer();
            cell_23.get_status();
            flag_status_cell_23 = cell_23.analyze_answer();
            for(int i = 111; i < 118; i++){
                cells_19.get_status(i);
                flag_status_cells_19.insert(i, cells_19.analyze_answer());
            }
            cell_264.get_status();
            flag_status_cell_264 = cell_264.analyze_answer();
            // вывод в debug состояния всех опрошенных ячеек
            qDebug() << "статус 81 ячейки: "<< flag_status_cell_81 << "\n";
            qDebug() << "статус 10-х ячеек: "<< flag_status_cell_10_21 << flag_status_cell_10_22 << flag_status_cell_10_23 << "\n";
            qDebug() << "статус 24 ячейки: "<< flag_status_cell_24 << "\n";
            qDebug() << "статус 23 ячейки: "<< flag_status_cell_23 << "\n";
            bool general_flag_cells_22 = true;  // общий флаг для 22 ячеек. нужен для того чтобы
            // если хоть одна ячейка false то будет далее брошен сигнал о проблеме управления ДН
            for(int i = 31; i < 79; i++){
                if(flag_status_cells_22[i] == false){
                    general_flag_cells_22 = false;
                }
                qDebug() << "статус 22 ячейки по адресу" << i << ":" << flag_status_cells_22[i] << "\n";
            }
            bool general_flag_cells_19 = true; // общий флаг для 19 ячеек
            for(int i = 111; i < 118; i++){
                if(flag_status_cells_19[i] == false){
                    general_flag_cells_19 = false;
                }
                qDebug() << "статус 19 ячейки по адресу" << i << ":" << flag_status_cells_19[i] << "\n";
            }
            if(flag_status_cell_10_21 == true &&
               flag_status_cell_10_22 == true &&
               flag_status_cell_10_23 == true &&
               flag_status_cell_81 == true &&
               flag_status_cell_24 == true &&
               flag_status_cell_23 == true &&
               general_flag_cells_22 == true &&
               general_flag_cells_19 == true){
                emit drive_dn(true);
            }else{
                emit drive_dn(false);
            }
        }else{
            emit asku_status(false);
            cell_48.unblock_channels();
        }
    }
}


void driveCells::expand_antenna_ra_dc(){
}


void driveCells::fold_antenna_ra_dc(){
}


void driveCells::change_flag_request(bool flag){
    enable_request = flag;
}


void driveCells::get_and_send_flag_connect(bool flag){
    emit send_flag_connect(flag);
}
