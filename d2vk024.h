#ifndef D2VK024_H
#define D2VK024_H

#include <QObject>
#include <QVector>
#include <QDebug>

class d2vk024 : public QObject
{
    Q_OBJECT
public:
    explicit d2vk024(QObject *parent = nullptr);
    void get_status();
    bool analyze_answer();

public slots:
    void received_msg(QByteArray);


signals:
    void send_request(QByteArray);

private:
    QByteArray answer;  // переменная для анализа ответа
                        // функции analyze_answer() которая
                        //вызывается после запроса из drivecells
    int request_status[5] = {0x7e, 0x5f, 0x01, 0x9f, 0x7e};
    QByteArray answer95 = QByteArrayLiteral("\x7e\x5f\x01\xff\xff\xa1\x7e");
    QByteArray request;
};

#endif // D2VK024_H
