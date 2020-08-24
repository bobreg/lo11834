#ifndef D2PA019_H
#define D2PA019_H

#include <QObject>
#include <QDebug>

class d2pa019 : public QObject
{
    Q_OBJECT
public:
    explicit d2pa019(QObject *parent = nullptr);
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
    int request_status[5] = {0x7e, 0x00, 0x0a, 0x00, 0x7e};
    QByteArray request;
signals:

};

#endif // D2PA019_H
