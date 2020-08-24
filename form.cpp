#include "form.h"
#include "ui_form.h"

Form::Form(QWidget *parent) :
    QWidget(parent),
    ui(new Ui::Form)
{
    ui->setupUi(this);
}

Form::~Form()
{
    delete ui;
}

void Form::on_checkBox_stateChanged(int arg1)
{
    if(arg1 == 2){
        emit connect_on(true);
    }else{
        emit connect_on(false);
    }
}

void Form::on_checkBox_2_stateChanged(int arg1)
{
    if(arg1 == 2){
        emit enable_request(true);
    }else{
        emit enable_request(false);
    }
}
