#include "mainwindow.h"
#include "ui_mainwindow.h"

#include <QTimer>
#include <QDebug>
#include <QKeyEvent>

#define BLOCK01_X_POS 300
#define BLOCK01_Y_POS 40
#define BLOCK02_X_POS 2300
#define BLOCK02_Y_POS 110
#define BLOCK03_X_POS 900
#define BLOCK03_Y_POS 190
#define BLOCK04_X_POS 2800
#define BLOCK04_Y_POS 260
#define BLOCK05_X_POS 1700
#define BLOCK05_Y_POS 310
#define BLOCK06_X_POS 1500
#define BLOCK06_Y_POS 140

/*
 * game_status
 * 0 => init
 * 1 => playing
 * 2 => pause
 * 3 => timeout
 * 4 => die
 */


MainWindow::MainWindow(QWidget *parent)
    : QMainWindow(parent)
    , ui(new Ui::MainWindow)
{
    ui->setupUi(this);

    game_status = 0;

    ui->block_01->setGeometry(QRect(-100, 0, 64, 64));
    ui->block_02->setGeometry(QRect(-100, 0, 64, 64));
    ui->block_03->setGeometry(QRect(-100, 0, 64, 64));
    ui->block_04->setGeometry(QRect(-100, 0, 64, 64));
    ui->block_05->setGeometry(QRect(-100, 0, 64, 64));
    ui->block_06->setGeometry(QRect(-100, 0, 64, 64));

    bgm_pos = 0;
    object_timer = new QTimer(this);
    connect(object_timer, SIGNAL(timeout()), this, SLOT(update_object()));
    object_timer->start(10);

    time = 30;
    clock_timer = new QTimer(this);
    connect(clock_timer, SIGNAL(timeout()), this, SLOT(update_time()));
    // clock_timer->start(1000);
}

MainWindow::~MainWindow()
{
    delete ui;
}

void MainWindow::update_object() {
    // qDebug() << "time's up!";
    bgm_pos -= 1;
    ui->background->setGeometry(QRect(bgm_pos, 0, 4800, 512));

    bgm_pos = (bgm_pos == -32) ? 0 : bgm_pos;

    if (game_status == 1) {
        car_distance += 1;
        ui->label_distance->setText("行駛距離: " + QString::number(car_distance, 'f', 0) + "公尺");
        move_car();
        move_blocks();
    }
}

void MainWindow::update_time() {
    time -= 1;
    ui->lcd_clock->display(time);

    if (time == 0) {
        game_status = 3;
        game_stop();
    }
}

void MainWindow::game_stop() {
    clock_timer->stop();
    object_timer->stop();
}

void MainWindow::on_button_start_game_clicked() {
    game_start();
}

void MainWindow::game_start() {
    game_status = 1;

    ui->label_title->setVisible(false);
    ui->button_start_game->setVisible(false);

    clock_timer->start(1000);
    time = 30;
    ui->lcd_clock->display(time);

    car_pos = 220;
    car_distance = 0;
    car_direction = 0;
}

void MainWindow::keyPressEvent(QKeyEvent *event) {
    switch(event->key()) {
        case Qt::Key_Up:
            car_direction = -1;
            qDebug() << "up";
            break;
        case Qt::Key_Down:
            car_direction = 1;
            qDebug() << "down";
            break;
    }
}

void MainWindow::move_car() {
    int car_new_pos = car_pos + car_direction;

    if (car_new_pos >= 30 && car_new_pos <= 410) {
        car_pos = car_new_pos;
        ui->car->setGeometry(QRect(10, car_pos, 237, 71));
    }
    else {
        game_status = 4;
        game_stop();
    }
}

void MainWindow::move_blocks() {
    ui->block_01->setGeometry((QRect(BLOCK01_X_POS - car_distance, BLOCK01_Y_POS, 64, 64)));
}
