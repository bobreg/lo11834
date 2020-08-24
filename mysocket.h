#ifndef SOCKET_H
#define SOCKET_H

#include <QObject>
#include <QTcpSocket>
#include <QDebug>
#include <QTimer>

class MySocket : public QTcpSocket
{
    Q_OBJECT
public:
    MySocket();

signals:
    // куча сигнало где в зависимости от адреса ответа
    // кидаем ответ конкретной ячейке
    void got_new_msg_from_48_adr19(QByteArray);
    void got_new_msg_from_10_adr15(QByteArray);
    void got_new_msg_from_10_adr16(QByteArray);
    void got_new_msg_from_10_adr17(QByteArray);
    void got_new_msg_from_81_adr76(QByteArray);
    void got_new_msg_from_24_adr5f(QByteArray);
    void got_new_msg_from_23_adr66(QByteArray);
    void got_new_msg_from_22_adr1f_4f(QByteArray);
    void got_new_msg_from_19_adr6f_75(QByteArray);

    void unblock();    // это нужно чтобы разблокировать элементы окна
    void send_status_server(bool);

public slots:
    void new_connect();  // есть новое соединение с АСКУ
    void new_msg();      // получено новое сообщение
                         // разбор пакета и проверка КС
    void send_msg(QByteArray); // отправить новое сообщение
    void connecting_lost(); // закрыть соединение
    void start_timer_try_connect(bool); // переключение флага таймера и запуск таймера


private:
    QTcpSocket* socket = new QTcpSocket(this);
    QTimer timer_try_connect;
    bool flag_timer = false;  //флаг таймера, который можно менять из сервисного окна
                              //данный таймер разрешает запус таймера для попытки соединения
    bool flag_request = false; //флаг запускающий или останавливающий опрос ячеек, который можно менять из серв. окна

    QByteArray msg;
    unsigned char control_sum = 255;
    bool flag_connect = false;
    void try_connect();
};

#endif // SERVER_H
