#ifndef D2VV048_H
#define D2VV048_H


#include <QObject>
#include <QVector>
#include <QDebug>

class d2vv048 : public QObject
{
    Q_OBJECT
public:
    explicit d2vv048(QObject *parent = nullptr);
    void get_status();
    void unblock_channels();
    bool analyze_answer();

public slots:
    void received_msg(QByteArray);

signals:
    void send_request(QByteArray);


private:

    int get_status_command = 0x5a;
    int unblock_command = 0x5a;

    QByteArray answer;  // переменная для анализа ответа
                        // функции analyze_answer() которая
                        //вызывается после запроса из drivecells

    int request_status[5] = {0x7e, 0x19, 0x5a, 0x8c, 0x7e};
    int request_unblock_channel[7] = {0x7e, 0x19, 0x5b, 0xff, 0x01 , 0x8b, 0x7e};
    QByteArray request;   // в эту переменную набираем сообщение

};

#endif // D2VV048_H

/*
Запрос: 7E 19 5A 8C 7E
Ответ: 7E 19 5A 00 00 8C 7E
Запрос: 7E 19 5B FF 01 8B 7E
Ответ: 7E 19 5A FF 01 8C 7E
*/

