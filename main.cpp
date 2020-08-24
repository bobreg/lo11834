#include "widget.h"
#include "mysocket.h"
#include "drivecells.h"
#include "form.h"


#include <QApplication>

int main(int argc, char *argv[])
{
    setlocale(LC_ALL, "");
    QApplication a(argc, argv);
    Widget w;
    Form f;
    driveCells dr_cells;
    w.show();
    f.show();

    //передача состояния что антенна развёрнута в окно
    QApplication::connect(&w, &Widget::expand_antenna_ra,
                          &dr_cells, &driveCells::expand_antenna_ra_dc);

    //передача состояния что антенна свёрнута в окно
    QApplication::connect(&w, &Widget::fold_antenna_ra,
                          &dr_cells, &driveCells::fold_antenna_ra_dc);

    //передача статуса состояния общения программы с ячейками
    //как статуса АСКУ в окно программы
    QApplication::connect(&dr_cells, &driveCells::asku_status,
                          &w, &Widget::asku_status);

    //передача статуса общения с ячейками управления ДН в окно программы
    QApplication::connect(&dr_cells, &driveCells::drive_dn,
                          &w, &Widget::drive_dn);

    //включение/выключение опроса из сервисного окна
    QApplication::connect(&f, &Form::enable_request,
                          &dr_cells, &driveCells::change_flag_request);

    //включение/выключение попыток приконнектиться
    QApplication::connect(&f, &Form::connect_on,
                          &dr_cells, &driveCells::get_and_send_flag_connect);

    return a.exec();
}


