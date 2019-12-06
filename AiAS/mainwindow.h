#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>

namespace Ui {
class MainWindow;
}

class MainWindow : public QMainWindow
{
    Q_OBJECT

public:
    explicit MainWindow(QWidget *parent = 0);
    int main_work(int number_of_segments, int gen_or_wr);
    ~MainWindow();

private slots:
    void on_spinBox_valueChanged(int arg1);

    void on_checkBox_2_stateChanged(int arg1);

    void on_pushButton_clicked();

private:
    Ui::MainWindow *ui;
};

#endif // MAINWINDOW_H
