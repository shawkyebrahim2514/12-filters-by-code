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

private slots:
    void updateImg();
    void on_loadBtn_clicked();

    void on_invertBtn_clicked();

    void on_mergeBtn_clicked();

    void on_flipBtn_clicked();

    void on_blurBtn_clicked();

    void on_BlackAndWhiteBtn_clicked();

    void on_darkenBtn_clicked();

    void on_lightenBtn_clicked();

    void on_flip_v_clicked();

    void on_flip_h_clicked();

    void on_rotateBtn_clicked();

    void on_rotate_90_clicked();

    void on_rotate_180_clicked();

    void on_rotate_270_clicked();

    void on_detectBtn_clicked();

    void on_enlargeBtn_clicked();

    void on_enlarge_1_clicked();

    void on_enlarge_2_clicked();

    void on_enlarge_3_clicked();

    void on_enlarge_4_clicked();

private:
    Ui::MainWindow *ui;
};
#endif // MAINWINDOW_H
