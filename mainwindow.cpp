#include "mainwindow.h"
#include "ui_mainwindow.h"
#include <QtGui/QColor>
#include <QtGui/QPen>
#include <QtGui/QBrush>

MainWindow::MainWindow(QWidget *parent)
    : QMainWindow(parent)
    , ui(new Ui::MainWindow)
{
    ui->setupUi(this);

    // ---------- Сцена и БПЛА ----------
    scene = new QGraphicsScene(this);
    scene->setSceneRect(0, 0, 800, 600);
    ui->graphicsView->setScene(scene);

    uav = scene->addEllipse(x, y, 20, 20,
                            QPen(Qt::black),
                            QBrush(Qt::red));
    uav->setPos(x, y);

    // ---------- Таймер ----------
    timer = new QTimer(this);
    connect(timer, &QTimer::timeout, this, &MainWindow::moveUAV);

    // ---------- Слайдер скорости ----------
    ui->sliderSpeed->setMinimum(1);
    ui->sliderSpeed->setMaximum(10);
    ui->sliderSpeed->setValue(2);
    ui->labelSpeed->setText("Скорость: 2");

    // ---------- Начальное состояние UI ----------
    ui->labelStatus->setText("Статус: Остановлен");
    ui->btnStart->setText("Старт");      // стартовый текст кнопки
}

MainWindow::~MainWindow()
{
    delete ui;
}

// ---------------------------------------------------------------
// Движение по периметру квадрата
// ---------------------------------------------------------------
void MainWindow::moveUAV()
{
    switch (dir) {
    case 0: x += speed; break;   // вправо
    case 1: y += speed; break;   // вниз
    case 2: x -= speed; break;   // влево
    case 3: y -= speed; break;   // вверх
    }

    if      (dir == 0 && x >= 250) { x = 250; dir = 1; }
    else if (dir == 1 && y >= 250) { y = 250; dir = 2; }
    else if (dir == 2 && x <= 50 ) { x = 50;  dir = 3; }
    else if (dir == 3 && y <= 50 ) { y = 50;  dir = 0; }

    uav->setPos(x, y);

    ui->labelStatus->setText(
        QString("Статус: Активен | X=%1, Y=%2, V=%3")
            .arg(int(x)).arg(int(y)).arg(speed));
}

// ---------------------------------------------------------------
// Одна кнопка: Старт / Стоп
// ---------------------------------------------------------------
void MainWindow::on_btnStart_clicked()
{
    if (timer->isActive()) {
        // --- Сейчас движение идёт → останавливаем ---
        timer->stop();
        ui->btnStart->setText("Старт");
        ui->labelStatus->setText(
            QString("Статус: Остановлен | X=%1, Y=%2")
                .arg(int(x)).arg(int(y)));
    } else {
        // --- Сейчас стоит → запускаем ---
        timer->start(20);
        ui->btnStart->setText("Стоп");
        ui->labelStatus->setText("Статус: Активен");
    }
}

// ---------------------------------------------------------------
// Задача 8: изменение скорости ползунком
// ---------------------------------------------------------------
void MainWindow::on_sliderSpeed_valueChanged(int value)
{
    speed = value;
    ui->labelSpeed->setText(QString("Скорость: %1").arg(value));
}