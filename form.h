#ifndef FORM_H
#define FORM_H

#include <QWidget>
#include <QDebug>

namespace Ui {
class Form;
}

class Form : public QWidget
{
    Q_OBJECT

public:
    explicit Form(QWidget *parent = nullptr);
    ~Form();

signals:
    void connect_on(bool);
    void enable_request(bool);

private slots:
    void on_checkBox_stateChanged(int arg1);

    void on_checkBox_2_stateChanged(int arg1);

private:
    Ui::Form *ui;
};

#endif // FORM_H
