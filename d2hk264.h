
#ifndef D2HK264_H
#define D2HK264_H

#include <QObject>
#include <QVector>
#include <QDebug>


class d2hk264 : public QObject
{
    Q_OBJECT
public:
    explicit d2hk264(QObject *parent = nullptr);
    void get_status();
    bool analyze_answer();

public slots:
    void expand_antenna_ra_264();
    void fold_antenna_ra_264();
    void received_msg(QByteArray msg);

signals:
    void send_request(QByteArray);

private:
    int adress = 0x6a;
    QVector <int> command = {0x06, 0x1b, 0x0d};
    QVector <int> informBites = {0b00000000, 0b00000000, 0b00000000, 0b00000000};
    QByteArray answer;  // переменная для анализа ответа
                        // функции analyze_answer() которая
                        //вызывается после запроса из drivecells
    int request_status[5] = {0x7e, 0x00, 0x00, 0x00, 0x7e};
    QByteArray request;

    void bild_send_message();
};

#endif // D2HK264_H
