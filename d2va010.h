#ifndef D2VA010_H
#define D2VA010_H

#include <QObject>
#include <QVector>
#include <QDebug>

class d2va010 : public QObject
{
    Q_OBJECT
public:
    explicit d2va010(int adress = 0, QObject *parent = nullptr);
    void get_status();
    bool analyze_answer();

    int adress_cell;

public slots:
    void received_msg(QByteArray);


signals:
    void send_request(QByteArray);
private:

    QVector <int> request_get[5] = {
        {0x7e, 0x15, 0x00, 0xea, 0x7e},
        {0x7e, 0x16, 0x00, 0xe9, 0x7e},
        {0x7e, 0x17, 0x00, 0xe8, 0x7e},
    };
    QByteArray answer;  // переменная для анализа ответа
                        // функции analyze_answer() которая
                        //вызывается после запроса из drivecells
    QByteArray request;  // в эту переменную набираем сообщение
    QByteArray answer21 = QByteArrayLiteral("\x7e\x15\x00\x00\x00\x00\x00\xa8\xfe\x44\x7e");
    QByteArray answer22 = QByteArrayLiteral("\x7e\x16\x00\x00\x00\x00\x00\x00\x00\xe9\x7e");
    QByteArray answer23 = QByteArrayLiteral("\x7e\x17\x00\x80\x02\x00\x00\x00\x00\x66\x7e");
};

#endif // D2VA010_H


/* запросы
    7E 15 00 EA 7E
    7E 16 00 E9 7E
    7E 17 00 E8 7E

   ответы примерные
    7E 15 00 00 00 00 00 A8 FE 44 7E тут вопрос к
        байту 5 (не потока вент ВВ60)
    7E 16 00 00 00 00 00 00 00 E9 7E
    7E 17 00 80 02 00 00 00 00 66 7E

*/
