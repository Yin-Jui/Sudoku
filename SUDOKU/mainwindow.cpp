#include "mainwindow.h"
#include "ui_mainwindow.h"
#include<stdio.h>
#include<QHeaderView>
#include"delegate.h"
#include<QTableView>
#include <QDebug>
#include<QTableWidgetItem>
#include<QAbstractItemView>
#include<QApplication>
#include<QProcess>
#include<cstdlib>
#include<ctime>
#include<QDateTime>

#define UNASSIGNED 0


MainWindow::MainWindow(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::MainWindow)
{
    f=new finisht();
    timee = new QTimer(this);
    l=new QLCDNumber(this);

    connect(timee,SIGNAL(timeout()),this,SLOT(timer()));
    timee->start(1000);
    easymode=false;
    mediummode=false;
    hardmode=false;



    user.assign(9,0);
    user_sudoku.assign(9,user);

    ui->setupUi(this);
    ui->restart->setStyleSheet("background-color:rgb(220,20,60)");
    ui->solve->setStyleSheet("background-color:rgb(255,140,0)");
    ui->random->setStyleSheet("background-color:rgb(255,140,0)");
    ui->manual->setStyleSheet("background-color:rgb(255,140,0)");
    ui->check->setStyleSheet("background-color:rgb(255,140,0)");
    ui->start->setStyleSheet("background-color:rgb(255,140,0)");
    ui->line->setLineWidth(0.01);
    ui->line_2->setLineWidth(0.01);
    ui->line_3->setLineWidth(0.01);
    ui->line_4->setLineWidth(0.01);
    ui->line_2->setStyleSheet("background-color:rgb(255,140,0)");
    ui->line_3->setStyleSheet("background-color:rgb(255,140,0)");
    ui->line_4->setStyleSheet("background-color:rgb(255,140,0)");
    ui->line->setStyleSheet("background-color:rgb(255,140,0)");
    ui->label->setStyleSheet("color:rgb(0,0,255)");
    ui->tableWidget->setStyleSheet("selection-background-color:rgb(255,255,0)");
    ui->tableWidget->setSelectionMode(QAbstractItemView::SingleSelection);
}


MainWindow::~MainWindow()
{
    delete ui;
}

void MainWindow::on_tableWidget_cellChanged(int row, int column)
{
ui->tableWidget->setItemDelegate(new Delegate);
    QFont font;
    font.setPointSize(30);
    for(int i=0;i<=8;i++){
        for(int j=0;j<=8;j++){
            ui->tableWidget->item(i,j)->setFont(font);
            ui->tableWidget->item(i,j)->setTextAlignment(Qt::AlignCenter);

        }
    }

}

void MainWindow::on_checkBox_clicked(bool checked)
{
    if(checked){
        for(int i=0;i<=8;i++){
            for(int j=0;j<=8;j++){
                ui->tableWidget->item(i,j)->setBackgroundColor(Qt::black);
                if(ui->tableWidget->item(i,j)->textColor()!=Qt::red){
                ui->tableWidget->item(i,j)->setTextColor(QColor(255,136,0));}

            }

        }
    }
    if(!checked){
        for(int i=0;i<=8;i++){
            for(int j=0;j<=8;j++){
                ui->tableWidget->item(i,j)->setBackgroundColor(Qt::white);
                ui->tableWidget->item(i,j)->setTextColor(QColor(0,0,0));

            }
        }

    }
}

void MainWindow::on_manual_clicked()
{
    ui->tableWidget->setItemDelegate(new Delegate);
    for(int i=0; i<9; ++i)
    {
        for(int j=0; j<9; ++j){
           user_sudoku[i].at(j) =0;
           ui->tableWidget->item(i,j)->setText(QString::number(user_sudoku[i].at(j)));
           if(ui->tableWidget->item(i,j)->text()=="0"){
           ui->tableWidget->item(i,j)->setText("");
           }

        }
    }
}

bool start;

void MainWindow::on_start_clicked()
{
    start=true;
    for(int i=0;i<=8;i++){
        for(int j=0;j<=8;j++){
            if(ui->tableWidget->item(i,j)->text().toInt()!=0){
                ui->tableWidget->item(i,j)->setTextColor(Qt::red);
                ui->tableWidget->item(i,j)->setFlags(Qt::ItemIsSelectable|Qt::ItemIsEditable);
            }
        }
    }

}


void MainWindow::on_restart_clicked()
{
    qApp->quit();
    QProcess::startDetached(qApp->arguments()[0],qApp->arguments());
}


bool MainWindow::isCorrect()
{
    bool check_result;
    int check_arr[9];

    // check rows
    for(int i=0; i<9; ++i)
    {
        for(int j=0; j<9; ++j){
            check_arr[j] = user_sudoku[i].at(j);

        }
        check_result = checkUnity(check_arr);
        if(!check_result){
            return false;
        }
    }

    // check columns
    for(int i=0; i<9; ++i)
    {
        for(int j=0; j<9; ++j){
            check_arr[j] = user_sudoku[j][i];
        }
        check_result = checkUnity(check_arr);
        if(!check_result){
            return false;
        }
    }

    // check cells
    for(int k=0; k<3; ++k){
        for(int x=0; x<9; x+=3)
        {
            for(int y=0; y<9; ++y)
            {
                int x_tmp = x + y/3;
                int y_tmp = y%3 + k*3;
                check_arr[y] = user_sudoku[y_tmp][x_tmp];
            }
            check_result = checkUnity(check_arr);
            if(!check_result)

                return false;
        }
    }
    return true;
}

bool MainWindow::checkUnity(int arr[])
{
    int arr_unity[9];
    for(int i=0; i<9; ++i)
        arr_unity[i] = 0;
    for(int i=0; i<9; ++i)
        ++arr_unity[arr[i]-1];
    for(int i=0; i<9; ++i)
        if(arr_unity[i] != 1)
            return false;
    return true;
}

bool MainWindow::on_random_clicked()
{
int rando;

srand((unsigned)time(NULL));
while(true){
    for(int i=0; i<9; ++i)
    {
        for(int j=0; j<9; ++j){

            user_sudoku[i].at(j)=0;

        }
    }
    for(int i =0;i<=8;i++)
    {

        rando=rand()%9;
        rando+=1;
        user_sudoku[i][i]=rando;
        // qDebug("%d\n",rando);
    }
    for(int i =0;i<=45;i++){
        int ranrow=rand()%9;
        int randcol=rand()%9;
        rando=rand()%9;
        rando+=1;
        if(isSafe(ranrow,randcol,rando)){

            user_sudoku[ranrow][randcol]=rando;
        }
    }

    if(SolveSudoku()){
        if(easymode==true){
            for(int i =0;i<=25;i++){
                int ranrow=rand()%9;
                int randcol=rand()%9;

                user_sudoku[ranrow][randcol]=0;


            }
        }
        if(hardmode==true){
            for(int i =0;i<=90;i++){
                int ranrow=rand()%9;
                int randcol=rand()%9;

                user_sudoku[ranrow][randcol]=0;


            }
        }
        if(mediummode==true)
        {
            for(int i =0;i<=50;i++){
                int ranrow=rand()%9;
                int randcol=rand()%9;

                user_sudoku[ranrow][randcol]=0;


            }
        }
    for(int i=0; i<9; ++i)
    {
        for(int j=0; j<9; ++j){
    ui->tableWidget->item(i,j)->setText(QString::number(user_sudoku[i].at(j)));
    if(ui->tableWidget->item(i,j)->text()=="0"){
    ui->tableWidget->item(i,j)->setText("");
    }
        }
    }
    return true;
}   

else{
    continue;
}
}
}

void MainWindow::on_check_clicked()
{


    for(int i=0; i<9; ++i)
    {
        for(int j=0; j<9; ++j){
            user_sudoku[i][j]= ui->tableWidget->item(i,j)->text().toInt();
        }
    }
    if (isCorrect()){

        ui->label->setText("Bingo!");

        f->settime(text);

        f->show();
    }
    else{

        ui->label->setText("Wrong!");
    }
}


bool MainWindow::SolveSudoku()
{
    int row, col;
    if (!FindUnassignedLocation(row, col))
       return true;

    for (int num = 1; num <= 9; num++)
    {
        if (isSafe(row, col, num))
        {
            user_sudoku[row][col] = num;

            if (SolveSudoku())
                return true;

          user_sudoku[row][col] = UNASSIGNED;
        }
    }
    return false;
}
bool MainWindow::FindUnassignedLocation(int &row, int &col)
{
    for (row = 0; row < 9; row++)
        for (col = 0; col < 9; col++)
            if (user_sudoku[row][col] == UNASSIGNED)
                return true;
    return false;
}

bool MainWindow::UsedInRow(int row, int num)
{
    for (int col = 0; col < 9; col++)
        if (user_sudoku[row][col] == num)
            return true;
    return false;
}
bool MainWindow::UsedInCol(int col, int num)
{
    for (int row = 0; row < 9; row++)
        if (user_sudoku[row][col] == num)
            return true;
    return false;
}

bool MainWindow::UsedInBox(int boxStartRow, int boxStartCol, int num)
{
    for (int row = 0; row < 3; row++)
        for (int col = 0; col < 3; col++)
            if (user_sudoku[row+boxStartRow][col+boxStartCol] == num)
                return true;
    return false;
}

int i=1;

void MainWindow::timer()
{
if(start){
    QTime t(0,0,0);
   // t.start();
QTime lasting=t.addSecs(i++);

    text = lasting.toString("h:m:s");
    QFont font;
    font.setPointSize(10);


    ui->lcd->setDigitCount(8);
    ui->lcd->setStyleSheet("background-color:rgb(0,0,0)");
    ui->lcd->setPalette(Qt::blue);
    ui->lcd->display(text);

}
}
bool MainWindow::isSafe(int row, int col, int num)
{

    return !UsedInRow( row, num) &&
           !UsedInCol( col, num) &&
           !UsedInBox( row - row%3 , col - col%3, num);
}


void MainWindow::on_solve_clicked()
{
    for(int i=0; i<9; ++i)
    {
        for(int j=0; j<9; ++j){
           user_sudoku[i][j]= ui->tableWidget->item(i,j)->text().toInt();
        }
    }

        if(SolveSudoku()){
        for(int i=0; i<9; ++i)
        {
            for(int j=0; j<9; ++j){

               ui->tableWidget->item(i,j)->setText(QString::number(user_sudoku[i].at(j)));

            }
        }
ui->label->setText(("solved"));
    }
    else {
        qDebug()<<"unsolvable";
        ui->label->setText("unsolvable");
          }
}



void MainWindow::on_easy_clicked(bool checked)
{
    if(!checked)
    {
        easymode=false;
    }
    if(checked)
    {
        easymode=true;

    }
}

void MainWindow::on_medium_clicked(bool checked)
{
    if(!checked){
        mediummode = false;}
    if(checked){
        mediummode = true;
    }
}


void MainWindow::on_hard_clicked(bool checked)
{
    if(!checked){
        hardmode=false;}
    if(checked){
        hardmode=true;
    }
}
