#ifndef D2VK023_H
#define D2VK023_H

#include <QObject>
#include <QDebug>

class d2vk023 : public QObject
{
    Q_OBJECT
public:
    explicit d2vk023(QObject *parent = nullptr);
    void get_status();
    bool analyze_answer();

signals:
    void send_request(QByteArray);

public slots:
    void received_msg(QByteArray);

private:
    QByteArray answer;  // переменная для анализа ответа
                        // функции analyze_answer() которая
                        //вызывается после запроса из drivecells
    int request_status[5] = {0x7e, 0x66, 0x00, 0x99, 0x7e};
    QByteArray request;
};

#endif // D2VK023_H
