#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
#include <QtWidgets/QGraphicsScene>
#include <QtWidgets/QGraphicsEllipseItem>
#include <QtCore/QTimer>

QT_BEGIN_NAMESPACE
namespace Ui { class MainWindow; }
QT_END_NAMESPACE

class MainWindow : public QMainWindow
{
    Q_OBJECT

public:
    MainWindow(QWidget *parent = nullptr);
    ~MainWindow();

private slots:
    void moveUAV();                              // движение по квадрату
    void on_btnStart_clicked();                  // Старт/Стоп
    void on_sliderSpeed_valueChanged(int value); // скорость

private:
    Ui::MainWindow *ui;

    QGraphicsScene       *scene = nullptr;
    QGraphicsEllipseItem *uav   = nullptr;
    QTimer               *timer = nullptr;

    double x = 50.0;
    double y = 50.0;
    int    dir = 0;        // 0 → вправо, 1 → вниз, 2 → влево, 3 → вверх
    double speed = 2.0;
};

#endif // MAINWINDOW_H