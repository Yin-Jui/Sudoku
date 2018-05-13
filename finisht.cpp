#include "finisht.h"
#include"mainwindow.h"
#include"ui_finisht.h"
#include<QString>

finisht::finisht(QWidget *parent) :
    QDialog(parent),
    ui(new Ui::finisht)
{
    ui->setupUi(this);
    ui->finishtime->setPalette(Qt::blue);

}


finisht::~finisht()
{
    delete ui;
}

void finisht::settime(QString& text)
{
    ui->finishtime->setText(text);
}
