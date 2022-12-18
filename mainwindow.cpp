#include "mainwindow.h"
#include "ui_mainwindow.h"
#include "QPainter"
#include "vector"
#include "cmath"
#include "QPoint"
#include "fstream"
#include "QMessageBox"
#define PI 3.14159265358

MainWindow::MainWindow(QWidget *parent)
    : QMainWindow(parent)
    , ui(new Ui::MainWindow)
{
    read_file();
    search_cntrlp();
    ui->setupUi(this);

}

MainWindow::~MainWindow()
{
    delete ui;
}

//реализация перемещения графика мышкой (возможно надо удалить)
void MainWindow::mousePressEvent (QMouseEvent *event)
{
    QPoint check = event->pos();
    if((check.x() <= this->start_point.x() + 100) && (check.x() >= this->start_point.x() - 100)
            &&
       (check.y() <= this->start_point.y() + 100) && (check.y() >= this->start_point.y() - 100))
        this->clicl_check = true;
}

void MainWindow::mouseMoveEvent(QMouseEvent *event)
{
    if(this->clicl_check == true)
    {
        this->start_point = event->pos();
        repaint();
    }
}

void MainWindow::mouseReleaseEvent(QMouseEvent *event)
{
    this->clicl_check = false;
}



//блок работы с файлами
void MainWindow::read_file()
{
    double buff;
    //std::ifstream read ("D:\\c++\\qt prolects\\kursovay\\kursovay\\data.txt");
    std::ifstream read ("..\\kursovay\\data.txt");

    while (!read.eof())
    {
        read >> buff;
        this->values.push_back(buff);
    }
    read.close();
}

void MainWindow::write_file()
{
    std::ofstream write;
   // write.open("D:\\c++\\qt prolects\\kursovay\\kursovay\\data.txt");
    write.open("..\\kursovay\\data.txt");
    for (int i = 0; i < this->values.size(); i++)
    {
        write << this->values[i] << std::endl;
    }
    write.close();
}






//рисование
void MainWindow::paintEvent(QPaintEvent*)
{


    QPainter painter (this);
    int step_x = 20;
    int step_y = 100;
    QPoint ellipse_center;//(this->start_point.x()+j*step_x, this->start_point.y() + this->values[j]*step_y)

    QPen pen(QColor (0, 0, 0) );
    pen.setWidth(4);
    painter.setPen(pen);
    //Вертикальная часть системы координат
    painter.drawLine(this->start_point.x(), this->start_point.y(), this->start_point.x(), this->start_point.y() - step_y*4);
    painter.drawLine(this->start_point.x(), this->start_point.y(), this->start_point.x(), this->start_point.y() + step_y*4);

    //стрелки на концах оси У
    painter.drawLine(this->start_point.x(), this->start_point.y() - step_y*4, this->start_point.x()+5, this->start_point.y() - step_y*4 + 5);
    painter.drawLine(this->start_point.x(), this->start_point.y() - step_y*4, this->start_point.x()-5, this->start_point.y() - step_y*4 + 5);

    painter.drawLine(this->start_point.x(), this->start_point.y() + step_y*4, this->start_point.x()+5, this->start_point.y() + step_y*4 - 5);
    painter.drawLine(this->start_point.x(), this->start_point.y() + step_y*4, this->start_point.x()-5, this->start_point.y() + step_y*4 - 5);


    //Горизонтальная часть системы координат
    painter.drawLine(this->start_point.x(), this->start_point.y(), this->start_point.x() + step_x*1000, this->start_point.y());

    pen.setWidth(1);
    painter.setPen(pen);
    //линии значений по У
    //-
    painter.drawLine(this->start_point.x(), this->start_point.y()+step_y, this->start_point.x() + step_x*1000, this->start_point.y()+step_y);
    painter.drawLine(this->start_point.x(), this->start_point.y()+step_y*2, this->start_point.x() + step_x*1000, this->start_point.y()+step_y*2);
    painter.drawLine(this->start_point.x(), this->start_point.y()+step_y*3, this->start_point.x() + step_x*1000, this->start_point.y()+step_y*3);
    //+
    painter.drawLine(this->start_point.x(), this->start_point.y()-step_y, this->start_point.x() + step_x*1000, this->start_point.y()-step_y);
    painter.drawLine(this->start_point.x(), this->start_point.y()-step_y*2, this->start_point.x() + step_x*1000, this->start_point.y()-step_y*2);
    painter.drawLine(this->start_point.x(), this->start_point.y()-step_y*3, this->start_point.x() + step_x*1000, this->start_point.y()-step_y*3);

    //подписи
    //+
    painter.drawText(this->start_point.x() - step_x, this->start_point.y()-step_y,"1");
    painter.drawText(this->start_point.x() - step_x, this->start_point.y()-step_y*2,"2");
    painter.drawText(this->start_point.x() - step_x, this->start_point.y()-step_y*3,"3");
    //-
    painter.drawText(this->start_point.x() - step_x, this->start_point.y()+step_y,"-1");
    painter.drawText(this->start_point.x() - step_x, this->start_point.y()+step_y*2,"-2");
    painter.drawText(this->start_point.x() - step_x, this->start_point.y()+step_y*3,"-3");


    //отрисочка линий графика
    //painter.setPen(QColor(100, 10, 10));
    pen.setWidth(2);
    pen.setColor(QColor(100, 10, 10));
    painter.setPen(pen);
    for (int j = 0; j < values.size(); j++)
        painter.drawLine(this->start_point.x()+j*step_x, this->start_point.y(), this->start_point.x()+j*step_x, this->start_point.y() - this->values[j]*step_y );


//отрисовка точке
painter.setBrush(QColor(100, 10, 10));
painter.setPen(Qt::NoPen);
for (int j = 0; j < values.size(); j++)
{
    ellipse_center.setX(this->start_point.x()+j*step_x);
    ellipse_center.setY(this->start_point.y() - this->values[j]*step_y);
    painter.drawEllipse(ellipse_center, 6, 6);
    for(int z = 0; z < this->control_points.size(); z++)
    {
        //проврка на отрисовку точек перегиба
        if (this->values[j] == this->control_points[z])
        {
            painter.setBrush(QColor(10, 10, 100));
            painter.setPen(Qt::NoPen);
            painter.drawEllipse(ellipse_center, 6, 6);
            painter.setBrush(QColor(100, 10, 10));
            painter.setPen(Qt::NoPen);
        }
    }
}

}

//работа с точками графика(создание, поиск точек перегиба)

void MainWindow::set_vector()
{
    srand(time(NULL));
        double a, b, c, d ,x;
        int count;

        double buff;

        for (size_t count_1 = 0; count_1 <= 50; count_1 ++){
            x= rand()%360;
            a = rand();
            b = rand();
            c = rand();
            d = rand();
            a/=10000;
            b/=10000;
            c/=10000;
            d/=10000;
            a = floor(a*100)/100;
            b = floor(b*100)/100;
            d = floor(d *100)/100;
            c = floor(c*100)/100;
            count = rand()%15 ;

            for(int count_2 = 0; count_2 <= count; count_2++ )
            {
                buff = a*sin(((x + b)*c/d)*PI/180);
                this->values.push_back(buff);
                x+=10;

            }
         }

}

void MainWindow::search_cntrlp()
{
    for(int i = 1; i < this->values.size() -1; i++ )
    {
        if (
                (this->values[i] < this->values[i-1])&&(this->values[i] < this->values[i+1])
                ||
                (this->values[i] > this->values[i-1])&&(this->values[i] > this->values[i+1])
            )
        {this->control_points.push_back(this->values[i]);}
    }
}



//кнопки взаимодействия с графиком
void MainWindow::on_replease_button_clicked()
{
    this->start_point = this->reserv_start_point;
    repaint();
}


void MainWindow::on_repaint_button_clicked()
{
    this->values.clear();
    set_vector();
    write_file();
    search_cntrlp();
    repaint();
}




//кнопки перемещения графика
void MainWindow::on_right_moove_button_clicked()
{
    this->start_point.setX(this->start_point.x() - 150);
    repaint();
}


void MainWindow::on_d_right_moove_button_clicked()
{
    this->start_point.setX(this->start_point.x() - 300);
    repaint();
}


void MainWindow::on_t_right_moove_button_clicked()
{
    this->start_point.setX(this->start_point.x() - 450);
    repaint();
}




void MainWindow::on_left_moove_button_clicked()
{
    this->start_point.setX(this->start_point.x() + 150);
    repaint();
}


void MainWindow::on_d_left_moove_button_clicked()
{
    this->start_point.setX(this->start_point.x() + 300);
    repaint();
}


void MainWindow::on_t_left_moove_button_clicked()
{
    this->start_point.setX(this->start_point.x() + 450);
    repaint();
}

