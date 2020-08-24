#include "widget.h"
#include "ui_widget.h"

Widget::Widget(QWidget *parent)
    : QWidget(parent)
    , ui(new Ui::Widget)
{
    ui->setupUi(this);
}

Widget::~Widget()
{
    delete ui;
}


void Widget::on_pushButton_2_clicked()
{
    ui->label_10->setDisabled(false);
    ui->label_11->setDisabled(false);
    ui->label_12->setDisabled(false);
    ui->label_13->setDisabled(false);
    ui->label_14->setDisabled(false);
    ui->label_21->setDisabled(false);
    ui->label_22->setDisabled(false);
    ui->radioButton->setDisabled(false);
    ui->radioButton_2->setDisabled(false);
    ui->pushButton_4->setDisabled(false);
    ui->pushButton->setDisabled(false);
    ui->pushButton_2->setDisabled(true);
}


void Widget::on_pushButton_4_clicked()
{
    ui->label_15->setDisabled(false);
    ui->label_16->setDisabled(false);
    ui->radioButton_3->setDisabled(false);
    ui->radioButton_4->setDisabled(false);
    ui->pushButton_4->setDisabled(true);
    ui->pushButton->setDisabled(true);
    ui->label_10->setDisabled(true);
    ui->label_11->setDisabled(true);
    ui->label_12->setDisabled(true);
    ui->label_13->setDisabled(true);
    ui->label_14->setDisabled(true);
    ui->label_21->setDisabled(true);
    ui->label_22->setDisabled(true);
}


void Widget::on_pushButton_clicked()
{

}


void Widget::on_pushButton_3_clicked()
{
    ui->label_10->setDisabled(true);
    ui->label_11->setDisabled(true);
    ui->label_12->setDisabled(true);
    ui->label_13->setDisabled(true);
    ui->label_14->setDisabled(true);
    ui->label_21->setDisabled(true);
    ui->label_22->setDisabled(true);
    ui->radioButton->setDisabled(true);
    ui->radioButton_2->setDisabled(true);
    ui->pushButton_4->setDisabled(true);
    ui->pushButton->setDisabled(true);
    ui->label_15->setDisabled(true);
    ui->label_16->setDisabled(true);
    ui->radioButton_3->setDisabled(true);
    ui->radioButton_4->setDisabled(true);
    ui->pushButton_2->setDisabled(false);
}


void Widget::on_radioButton_clicked()
{
    emit expand_antenna_ra();
}


void Widget::on_radioButton_2_clicked()
{
    emit fold_antenna_ra();
}


void Widget::asku_status(bool flag){
    if(flag == true){
        ui->label_19->setStyleSheet("background: #a1e579; "
                                    "border: 1px outset #018dc4; "
                                    "border-radius: 15px;");
    }else{
        ui->label_19->setStyleSheet("background: #e8d423; "
                                    "border: 1px outset #018dc4; "
                                    "border-radius: 15px;");
    }
}


void Widget::drive_dn(bool flag){
    if(flag == true){
        ui->label_20->setStyleSheet("background: #a1e579; "
                                    "border: 1px outset #018dc4; "
                                    "border-radius: 15px;");
    }else{
        ui->label_20->setStyleSheet("background: #e8d423; "
                                    "border: 1px outset #018dc4; "
                                    "border-radius: 15px;");
    }
}
// зелёный цвет (ок) #a1e579
//песочный цвет (ожидание) #e8d423
// серый цвет (неактивный) #dedede
