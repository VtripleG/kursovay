#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
#include "QPainter"
#include "QMouseEvent"
#include "fstream"

QT_BEGIN_NAMESPACE
namespace Ui { class MainWindow; }
QT_END_NAMESPACE

class MainWindow : public QMainWindow
{
    Q_OBJECT

public:
    MainWindow(QWidget *parent = nullptr);
    ~MainWindow();
    void paintEvent (QPaintEvent*) override;

    void mousePressEvent(QMouseEvent *event) override ;
    void mouseMoveEvent(QMouseEvent *event)override;
    void mouseReleaseEvent(QMouseEvent *event) override;

    void read_file ();
    void write_file ();
    void search_cntrlp();



    QPoint start_point = QPoint (100, 500);
    QPoint reserv_start_point = QPoint (100, 500);
    QPoint click_point;
    std::vector <double> values;
    std::vector <double> control_points;
    bool clicl_check = false;

    void set_vector ();



private slots:
    void on_replease_button_clicked();

    void on_repaint_button_clicked();

    void on_left_moove_button_clicked();

    void on_right_moove_button_clicked();

    void on_d_right_moove_button_clicked();

    void on_t_right_moove_button_clicked();

    void on_d_left_moove_button_clicked();

    void on_t_left_moove_button_clicked();

private:
    Ui::MainWindow *ui;
};
#endif // MAINWINDOW_H
