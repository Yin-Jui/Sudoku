#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
#include<vector>
#include"finisht.h"
#include"delegate.h"
#include<QTimer>
#include<QLCDNumber>
using namespace std;


namespace Ui {
class MainWindow;
}

class MainWindow : public QMainWindow
{
    Q_OBJECT

public:
    explicit MainWindow(QWidget *parent = 0);
    ~MainWindow();
    bool isCorrect();
    bool checkUnity(int arr[]);

    bool FindUnassignedLocation( int &row, int &col);
    bool isSafe( int row, int col, int num);
    bool SolveSudoku();
    bool UsedInRow(int row, int num);
    bool UsedInCol(int col, int num);
    bool UsedInBox(int boxStartRow, int boxStartCol, int num);
    bool random();


public slots:
    void timer();

private slots:

    void on_tableWidget_cellChanged(int row, int column);

    void on_checkBox_clicked(bool checked);

    void on_manual_clicked();

    void on_start_clicked();

    void on_restart_clicked();

    bool on_random_clicked();

    void on_check_clicked();

    void on_solve_clicked();



    void on_easy_clicked(bool checked);

    void on_medium_clicked(bool checked);

    void on_hard_clicked(bool checked);

private:
    Ui::MainWindow *ui;
    vector<int> user;
    vector< vector<int> > user_sudoku;
    finisht *f;
    Delegate *d;
    QTimer *timee;
    QLCDNumber *l;
    QString text;
    bool easymode;
    bool mediummode;
    bool hardmode;


};

#endif // MAINWINDOW_H
