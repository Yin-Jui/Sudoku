#ifndef FINISHT_H
#define FINISHT_H

#include <QDialog>

namespace Ui {
class finisht;
}

class finisht : public QDialog
{
    Q_OBJECT

public:
    explicit finisht(QWidget *parent = 0);
    ~finisht();

    void settime(QString&);

private:
    Ui::finisht *ui;
};

#endif
