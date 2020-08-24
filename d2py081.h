#ifndef D2PY081_H
#define D2PY081_H

#include <QObject>
#include <QVector>
#include <QDebug>

class d2py081 : public QObject
{
    Q_OBJECT
public:
    explicit d2py081(QObject *parent = nullptr);
    void get_status();
    void unblock_channels();
    bool analyze_answer();

public slots:
    void received_msg(QByteArray);

signals:
    void send_request(QByteArray);

private:
    int get_status_command = 0x00;
    int unblock_command = 0x01;

    QByteArray answer;  // переменная для анализа ответа
                        // функции analyze_answer() которая
                        //вызывается после запроса из drivecells

    int request_status[5] = {0x7e, 0x76, 0x00, 0x89, 0x7e};
    int request_unblock_channel[6] = {0x7e, 0x76, 0x01, 0x07, 0x81, 0x7e};
    QByteArray request;   // в эту переменную набираем сообщение

};

#endif // D2PY081_H
