#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>

QT_BEGIN_NAMESPACE
namespace Ui { class MainWindow; }
QT_END_NAMESPACE

class MainWindow : public QMainWindow
{
        Q_OBJECT

    public:
        MainWindow(QWidget *parent = nullptr);
        ~MainWindow();

    protected:
        void keyPressEvent(QKeyEvent *);

    private slots:
        void update_time();
        void update_object();

        void on_button_start_game_clicked();

        void on_action_close_game_triggered();

        void on_action_start_game_triggered();

private:
        Ui::MainWindow *ui;

        int time;
        int game_status;
        int bgm_pos;
        int car_pos;
        int car_direction;
        float car_distance;

        QTimer *clock_timer;
        QTimer *object_timer;

        void game_start();
        void game_stop();
        void game_pause();
        void move_car();
        void move_blocks();
        void detect_blocks();
        bool is_collision(int x, int y);
};
#endif // MAINWINDOW_H
