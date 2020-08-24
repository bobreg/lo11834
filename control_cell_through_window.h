#ifndef CONTROL_CELL_THROUGH_WINDOW_H
#define CONTROL_CELL_THROUGH_WINDOW_H

#include <QObject>

class control_cell_through_window : public QObject
{
    Q_OBJECT
public:
    explicit control_cell_through_window(QObject *parent = nullptr);

signals:

};

#endif // CONTROL_CELL_THROUGH_WINDOW_H
