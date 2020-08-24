#ifndef D2AG022_H
#define D2AG022_H

#include <QObject>
#include <QDebug>
#include <iostream>
#include <string>

class d2ag022 : public QObject
{
    Q_OBJECT
public:
    explicit d2ag022(QObject *parent = nullptr);
    void get_status(unsigned char adr);
    bool analyze_answer();

public slots:
    void received_msg(QByteArray);

signals:
    void send_request(QByteArray);

private:
    unsigned char adress = 0x00;
    unsigned char control_summ = 0x00;
    QByteArray answer;  // переменная для анализа ответа
                        // функции analyze_answer() которая
                        //вызывается после запроса из drivecells
    int request_status[5] = {0x7e, 0x00, 0x00, 0x00, 0x7e};
    QByteArray request;

};

#endif // D2AG022_H
