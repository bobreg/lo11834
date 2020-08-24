#ifndef DRIVECELLS_H
#define DRIVECELLS_H

#include <QObject>
#include <QTimer>
#include <QMap>
#include "d2hk264.h"
#include "d2vv048.h"
#include "d2va010.h"
#include "d2py081.h"
#include "d2vk024.h"
#include "d2vk023.h"
#include "d2ag022.h"
#include "d2pa019.h"
#include "mysocket.h"

class driveCells : public QObject
{
    Q_OBJECT
public:
    explicit driveCells(QObject *parent = nullptr);

signals:
    void asku_status(bool);
    void drive_dn(bool);
    void send_flag_connect(bool); //см. get_and_send_flag_connect


public slots:
    // заспуск опроса когда есть соединение с сервером
    void requests_go(bool);

    void expand_antenna_ra_dc();
    void fold_antenna_ra_dc();
    void change_flag_request(bool);  //переключение флага разрешения опроса
    void get_and_send_flag_connect(bool); //передача флага из серв. окна в сокет

private:
    QTimer timer_requests;
    MySocket socket;

    d2vv048 cell_48;
    d2va010 cell_10_21{21};
    d2va010 cell_10_22{22};
    d2va010 cell_10_23{23};
    d2py081 cell_81;
    d2vk024 cell_24;
    d2vk023 cell_23;
    d2ag022 cells_22;
    d2pa019 cells_19;

    QByteArray answer;
    bool enable_request = true;

    bool flag_status_cell_48;
    bool flag_status_cell_10_21;
    bool flag_status_cell_10_22;
    bool flag_status_cell_10_23;
    bool flag_status_cell_81;
    bool flag_status_cell_24;
    bool flag_status_cell_23;
    QMap <char, bool> flag_status_cells_22;
    QMap <char, bool> flag_status_cells_19;
    void requests_in_process();
};

#endif // DRIVECELLS_H
