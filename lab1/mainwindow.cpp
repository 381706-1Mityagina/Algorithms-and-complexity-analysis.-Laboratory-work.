#include "mainwindow.h"
#include "ui_mainwindow.h"
//#include "segments_generate.cpp"
#include "intersect.cpp"
#include "sweep_line.cpp"
#include "cubic_spline.h"
#include "qcustomplot.h"
#include <sstream>
#include <stdexcept>
#include <iostream>
#include <map>
#include <set>
#include <ctime>
#include <string>
#include <vector>

using namespace std;

double x_1[100], x_2[100];
double y_1[100], y_2[100];
int count_click = 0;
int flag = 0;
int click = 0;
int flag_2 = 0;
int number_of_experiments[100];
int count_experiments = 0;
int time_naive[100];
int time_eff[100];

//void auto_generation_choose_length() {
//    y2[i] = ui->doubleSpinBox_4->value();
//}

void auto_generation_choose_angle() {

}

void auto_generation_last_intersection_position_naive(std::vector<LineSegment> &segments, int number_of_segments) {
    for (int i = 0; i < number_of_segments - 2; i++) {
        segments.push_back(LineSegment("", MyVector(float(i) / 10, 1.0, 0.0, i, 0), MyVector(float(i) / 10 + 0.5, 4.0, 0.0, i, 1), Context(0.0001)));
    }

    segments.push_back(LineSegment("", MyVector(float(number_of_segments) / 10, 1.0, 0.0, number_of_segments - 2, 0), MyVector(float(number_of_segments) / 10 + 3.0, 4.0, 0.0, number_of_segments - 2, 1), Context(0.0001)));
    segments.push_back(LineSegment("", MyVector(float(number_of_segments) / 10 + 2.0, 1.0, 0.0, number_of_segments - 1, 0), MyVector(float(number_of_segments) / 10 + 1.0, 4.0, 0.0, number_of_segments - 1, 1), Context(0.0001)));
}

void auto_generation_last_intersection_position_sweep(std::vector<Segment> &segments, int number_of_segments) {
    for (int i = 0; i < number_of_segments - 2; i++) {
        segments.push_back(Segment(Point(' ', float(i) / 10, 1.0), Point(' ', float(i) / 10 + 0.5, 4.0)));
    }

    segments.push_back(Segment(Point(' ', float(number_of_segments) / 10, 1.0), Point(' ', float(number_of_segments) / 10 + 3.0, 4.0)));
    segments.push_back(Segment(Point(' ', float(number_of_segments) / 10 + 2.0, 1.0), Point(' ', float(number_of_segments) / 10 + 1.0, 4.0)));
}

void auto_generation_last_intersection_position_naive_sqw(std::vector<LineSegment> &segments, int number_of_segments) {
    for (int i = 0; i < number_of_segments; i++) {
        segments.push_back(LineSegment("", MyVector((float)(rand()) / RAND_MAX, (float)(rand()) / RAND_MAX, 0.0, i, 0), MyVector((float)(rand()) / RAND_MAX, (float)(rand()) / RAND_MAX, 0.0, i, 1), Context(0.0001)));
    }
}

void auto_generation_last_intersection_position_sweep_sqw(std::vector<Segment> &segments, int number_of_segments) {
    segments.clear();
    for (int i = 0; i < number_of_segments; i++) {
        segments.push_back(Segment(Point(' ', (float)(rand()) / RAND_MAX , (float)(rand()) / RAND_MAX ), Point(' ', (float)(rand()) / RAND_MAX , (float)(rand()) / RAND_MAX)));
    }
}

//void user_input_naive(std::vector<LineSegment> &segments, int number_of_segments) {
//    for (int i = 0; i < number_of_segments; i++) {
//        double input = MainWindow::ui->doubleSpinBox->value();
//        if (MainWindow::ui->doubleSpinBox->valueChanged(input) && MainWindow::ui->doubleSpinBox_2->valueChanged(input) && MainWindow::ui->doubleSpinBox_3->valueChanged(input) && MainWindow::ui->doubleSpinBox_4->valueChanged(input))
//        {
//            double x1 = MainWindow::ui->doubleSpinBox->value();
//            double x2 = MainWindow::ui->doubleSpinBox_3->value();
//            double y1 = MainWindow::ui->doubleSpinBox_3->value();
//            double y2 = MainWindow::ui->doubleSpinBox_4->value();
//        }
//        segments.push_back(LineSegment("", MyVector(x1, y1, 0.0, i, 0), MyVector(x2, y2, 0.0, i, 1), Context(0.0001)));
//    }
//}

//void user_input_sweep(std::vector<Segment> &segments, int number_of_segments) {
//    for (int i = 0; i < number_of_segments; i++) {
//        double input = MainWindow::ui->doubleSpinBox->value();
//        if (MainWindow::ui->doubleSpinBox->valueChanged(input) && MainWindow::ui->doubleSpinBox_2->valueChanged(input) && MainWindow::ui->doubleSpinBox_3->valueChanged(input) && MainWindow::ui->doubleSpinBox_4->valueChanged(input))
//        {
//            double x1 = MainWindow::ui->doubleSpinBox->value();
//            double x2 = MainWindow::ui->doubleSpinBox_3->value();
//            double y1 = MainWindow::ui->doubleSpinBox_3->value();
//            double y2 = MainWindow::ui->doubleSpinBox_4->value();
//        }
//        segments.push_back(Segment(Point(' ', x1, y1), Point(' ', x2, y2)));
//    }
//}

//void using_input(std::vector<LineSegment> &segments, int number_of_segments) {
//    double begin_x, begin_y, end_x, end_y;
//    for (int i = 0; i < number_of_segments; i++) {
//		std::cout << "Segment start x :\n";
//		std::cin >> begin_x;
//		std::cout << "Segment start y :\n";
//		std::cin >> begin_y;
//		std::cout << "Segment end x :\n";
//		std::cin >> end_x;
//		std::cout << "Segment end y :\n";
//		std::cin >> end_y;

//        segments.push_back(LineSegment("", MyVector(begin_x, begin_y, 0.0), MyVector(end_x, end_y, 0.0), Context(0.0001)));
//    }
//}


MainWindow::MainWindow(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::MainWindow)
{
    ui->setupUi(this);
//    ui->centralWidget->setStyleSheet("background-image: url(/home/dariamityagina/AiAS/gg.jpg);");
}

int MainWindow::main_work(int number_of_segments, int gen_or_wr) {
// Naive algorithm
//    if (gen_or_wr == 0)
    {
        float x1, x2, y1, y2;
        auto context = Context(0.0001);

        std::vector<LineSegment> segments;
        Result result2;
        segments.clear();

        std::vector<Point> intersections;
        std::vector<Segment> segments_new;
        segments_new.clear();

        if (gen_or_wr == 0)
            auto_generation_last_intersection_position_naive(segments, number_of_segments);
        else if (gen_or_wr == 1)
            auto_generation_last_intersection_position_naive_sqw(segments, number_of_segments);
        else if (gen_or_wr == 2)
        {
            for (int i = 0; i < number_of_segments; i++) {
                segments.push_back(LineSegment("", MyVector((float)x_1[i], (float)y_1[i], 0.0, i, 0), MyVector((float)x_2[i], (float)y_2[i], 0.0, i, 1), Context(0.0001)));
                segments_new.push_back(Segment(Point(' ', x_1[i], y_1[i]), Point(' ', x_2[i], y_2[i])));
            }
        }

        double t1, t2, dt;
        t1 = clock();
        for (int i = 0; i < number_of_segments; i++)
            for (int j = 0; j < number_of_segments, j != i; j++)
        {
            auto a = segments[i];
            auto b = segments[j];
            result2 = Intersect(a, b, context);
            if (result2.type > 0)
            {
                ui->lcdNumber_3->setDigitCount(10);
                ui->lcdNumber_3->display(i);
                ui->lcdNumber_3->show();

                ui->lcdNumber_4->setDigitCount(10);
                ui->lcdNumber_4->display(j);
                ui->lcdNumber_4->show();
                break;
            }
        }
        t2 = clock();
        dt = t2 - t1;
        time_naive[count_experiments] = dt;
        ui->lcdNumber->setDigitCount(10);
        ui->lcdNumber->display(dt);
        ui->lcdNumber->show();
    // --------------------------------------------------------------------------------------------------------------
    // Effective algorithm
    // --------------------------------------------------------------------------------------------------------------
        if (gen_or_wr == 0)
            auto_generation_last_intersection_position_sweep(segments_new, number_of_segments);
        else if (gen_or_wr == 1)
            auto_generation_last_intersection_position_sweep_sqw(segments_new, number_of_segments);

        double t1_2, t2_2, dt_2;
        t1_2 = clock();
        intersect(segments_new, intersections, false);
        // pain_work(segments, number_of_segments);
        t2_2 = clock();
        dt_2 = t2_2 - t1_2;
        time_eff[count_experiments] = dt_2;
        ui->lcdNumber_2->setDigitCount(10);
        ui->lcdNumber_2->display(dt_2);
        ui->lcdNumber_2->show();
    }
    return 0;
}

MainWindow::~MainWindow()
{
    delete ui;
}

void MainWindow::on_spinBox_valueChanged(int arg1)
{
//    if (arg1 > 0)
//    {
//        number_of_experiments[count_experiments] = arg1;
//        count_experiments++;
//    }
    if (arg1 > 0)
        flag = 1;
}

void MainWindow::on_checkBox_2_stateChanged(int arg1)
{
    if (arg1 > 0)
    {
        number_of_experiments[count_experiments] = ui->spinBox->value();
//        count_experiments++;
    }
    if (arg1 > 0 && flag == 1)
    {
        flag_2 = 2;
    }
}

void MainWindow::on_pushButton_clicked()
{
    if (flag_2 == 2)
    {
        main_work(ui->spinBox->value(), 0);
        count_experiments++;
    }
    if (flag_2 == 3)
    {
        main_work(ui->spinBox->value(), 1);
        count_experiments++;
    }
    if (flag_2 == 4)
    {
        main_work(ui->spinBox->value(), 2);
        count_experiments++;
    }
}

void MainWindow::on_checkBox_stateChanged(int arg1)
{
    if (arg1 > 0 && flag == 1)
    {
        flag_2 = 2;
    }
}

void MainWindow::on_pushButton_2_clicked()
{
    int i = count_click;

    y_2[i] = ui->doubleSpinBox_4->value();
    x_1[i] = ui->doubleSpinBox->value();
    y_1[i] = ui->doubleSpinBox_2->value();
    x_2[i] = ui->doubleSpinBox_3->value();

    count_click++;
//    if (count_click == ui->spinBox->value())
//    {
//        for (int i = 0; i < count_click; i++)
//        {
//            x_1[i] = 0;
//            x_2[i] = 0;
//            y_1[i] = 0;
//            y_2[i] = 0;
//        }
//    }
}

void MainWindow::on_checkBox_3_stateChanged(int arg1)
{
    if (arg1 > 0)
    {
        flag_2 = 3;
    }
}

void MainWindow::on_checkBox_4_stateChanged(int arg1)
{
    if (arg1 > 0)
    {
        flag_2 = 4;
    }
}
