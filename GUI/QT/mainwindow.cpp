#include "mainwindow.h"
#include "ui_mainwindow.h"
#include <QFileDialog>
#include <QPixmap>
#include <bmplib.cpp>
unsigned char image[SIZE][SIZE][RGB];
unsigned char mergeImg[SIZE][SIZE][RGB];
vector<pair<int,int>>detect_dir{{0,1},{1,0},{-1,0},{0,-1}};
vector<pair<int,int>>all_dir{{1,1},{-1,-1},{1,-1},{-1,1},{0,1},{0,-1},{1,0},{-1,0}};
vector<vector<pair<int,int>>>rotation_map{ {{1,0},{0,1},{-1,0}}, {{1,1},{-1,0},{0,-1}}, {{0,1},{0,-1},{1,0}} };
vector<vector<int>>intervals{{0,0,0,0},{0,SIZE/2,0,SIZE/2},{0,SIZE/2,SIZE/2,SIZE},{SIZE/2,SIZE,0,SIZE/2},{SIZE/2,SIZE,SIZE/2,SIZE}};
int change_v, change_h;
QImage afterImg;

MainWindow::MainWindow(QWidget *parent)
    : QMainWindow(parent)
    , ui(new Ui::MainWindow)
{
    ui->setupUi(this);
    ui->flip_h->hide();
    ui->flip_v->hide();
    ui->rotate_90->hide();
    ui->rotate_180->hide();
    ui->rotate_270->hide();
    ui->enlarge_1->hide();
    ui->enlarge_2->hide();
    ui->enlarge_3->hide();
    ui->enlarge_4->hide();
}

MainWindow::~MainWindow()
{
    delete ui;
}


void MainWindow::on_loadBtn_clicked()
{
    QString imagePath = QFileDialog::getOpenFileName(this, "choose image","","Image (*.bmp)");
    QImage img;
    img.load(imagePath);
    ui->loadedImg->setPixmap(QPixmap::fromImage(img));
    ui->filteredImg->setPixmap(QPixmap::fromImage(img));
    std::string pathOfFile = imagePath.toUtf8().constData();
    readRGBBMP(pathOfFile.c_str(),image);
}

void MainWindow::updateImg(){
    writeRGBBMP("temp.bmp",image);
    afterImg.load("temp.bmp");
    ui->filteredImg->setPixmap(QPixmap::fromImage(afterImg));

}

void invert(){
    for (int i = 0; i < SIZE; i++)
    {
        for (int j = 0; j < SIZE; j++)
        {
            for (int k = 0; k < RGB; k++){

                image[i][j][k] = 255 - image[i][j][k];
            }
        }
    }
}


void MainWindow::on_invertBtn_clicked()
{
    invert();
    updateImg();
}

void merge() {
    for (int i = 0; i < SIZE; ++i) {
        for (int j = 0; j < SIZE; ++j) {
            for (int k = 0; k < RGB; ++k) {
                image[i][j][k] = (image[i][j][k] + mergeImg[i][j][k])/2;
            }
        }
    }
}


void MainWindow::on_mergeBtn_clicked()
{
    QString imagePath = QFileDialog::getOpenFileName(this, "choose image","","Image (*.bmp)");
    QImage img;
    img.load(imagePath);
    std::string pathOfFile = imagePath.toUtf8().constData();
    readRGBBMP(pathOfFile.c_str(),mergeImg);
    merge();
    updateImg();
}

void flip() {
    unsigned char image2[SIZE][SIZE][RGB];
    for (int i = 0; i < SIZE; i++) {
        for (int j = 0; j< SIZE; j++) {
            for (int k = 0; k < RGB; ++k) {
                image2[abs(change_v-i)][abs(change_h-j)][k] = image[i][j][k];
            }
        }
    }
    for (int i = 0; i < SIZE; i++) {
        for (int j = 0; j< SIZE; j++) {
            for (int k = 0; k < RGB; ++k) {
                image[i][j][k] = image2[i][j][k];
            }
        }
    }
}



void MainWindow::on_flipBtn_clicked()
{
    ui->flip_h->show();
    ui->flip_v->show();
}

void MainWindow::on_flip_v_clicked()
{
    ui->flip_h->hide();
    ui->flip_v->hide();
    change_h = SIZE - 1;
    change_v = 0;
    flip();
    updateImg();
}

void MainWindow::on_flip_h_clicked()
{
    ui->flip_h->hide();
    ui->flip_v->hide();
    change_v = SIZE - 1;
    change_h = 0;
    flip();
    updateImg();
}

void blur() {
    unsigned char image2[SIZE][SIZE][RGB];
    for (int i = 0; i < SIZE; i++) {
        for (int j = 0; j< SIZE; j++) {
            for (int k = 0; k < RGB; ++k) {
                int cnt = 1,avrge = image[i][j][k];
                for(auto val : all_dir){
                    int row = i + val.first, column = j + val.second;
                    if(row < 0 || row >= SIZE || column <0 || column >= SIZE){
                        continue;
                    }
                    cnt ++;
                    avrge += image[row][column][k];
                }
                image2[i][j][k] = avrge/cnt;
            }
        }
    }
    for (int i = 0; i < SIZE; i++) {
        for (int j = 0; j< SIZE; j++) {
            for (int k = 0; k < RGB; ++k) {
                image[i][j][k] = image2[i][j][k];
            }
        }
    }
}

void MainWindow::on_blurBtn_clicked()
{
    blur();
    updateImg();
}

void blackAndWhite() {
    for (int i = 0; i < SIZE; i++) {
        for (int j = 0; j< SIZE; j++) {
            int grey = 0;
            grey += image[i][j][0] *  0.3;
            grey += image[i][j][1] * 0.59;
            grey += image[i][j][2] * 0.11;
            for (int k = 0; k < RGB; ++k) {
                if(grey > 127)
                    image[i][j][k] = 255;
                else
                    image[i][j][k] = 0;
            }
        }
    }
}


void MainWindow::on_BlackAndWhiteBtn_clicked()
{
    blackAndWhite();
    updateImg();
}


void darken_lighten(string type) {
    int amount = 15;
    for (int i = 0; i < SIZE; i++) {
        for (int j = 0; j< SIZE; j++) {
            for (int k = 0; k < RGB; ++k) {
                if(type == "lighten") {
                    image[i][j][k] = min(255, image[i][j][k] + amount);
                }else{
                    image[i][j][k] = max(0, image[i][j][k] - amount);
                }
            }
        }
    }
}

void MainWindow::on_darkenBtn_clicked()
{
    darken_lighten("darken");
    updateImg();
}


void MainWindow::on_lightenBtn_clicked()
{
    darken_lighten("lighten");
    updateImg();
}




void rotate(int n_rotation) {
    n_rotation /= 90;
    n_rotation --;
    unsigned char image2[SIZE][SIZE][RGB];
    for (int i = 0; i < SIZE; ++i) {
        for (int j = 0; j < SIZE; ++j) {
            int tmp_row = (SIZE - 1)*rotation_map[n_rotation][0].first + i*rotation_map[n_rotation][1].first + j*rotation_map[n_rotation][2].first;
            int tmp_column = (SIZE - 1)*rotation_map[n_rotation][0].second + i*rotation_map[n_rotation][1].second + j*rotation_map[n_rotation][2].second;
            for (int k = 0; k < RGB; ++k) {
                image2[i][j][k] = image[tmp_row][tmp_column][k];
            }
        }
    }
    for (int i = 0; i < SIZE; i++) {
        for (int j = 0; j< SIZE; j++) {
            for (int k = 0; k < RGB; ++k) {
                image[i][j][k] = image2[i][j][k];
            }
        }
    }
}

void MainWindow::on_rotateBtn_clicked()
{
    ui->rotate_90->show();
    ui->rotate_180->show();
    ui->rotate_270->show();
}


void MainWindow::on_rotate_90_clicked()
{
    ui->rotate_90->hide();
    ui->rotate_180->hide();
    ui->rotate_270->hide();
    rotate(90);
    updateImg();
}


void MainWindow::on_rotate_180_clicked()
{
    ui->rotate_90->hide();
    ui->rotate_180->hide();
    ui->rotate_270->hide();
    rotate(180);
    updateImg();
}


void MainWindow::on_rotate_270_clicked()
{
    ui->rotate_90->hide();
    ui->rotate_180->hide();
    ui->rotate_270->hide();
    rotate(270);
    updateImg();
}

void detectEdges(){
    unsigned char image2[SIZE][SIZE][RGB];
    for (int i = 0; i < SIZE; ++i) {
        for (int j = 0; j < SIZE; ++j) {
            int tmp = -4*(image[i][j][0]);
            for(auto val:detect_dir){
                int row = i + val.first, column = j + val.second;
                if( row < 0 || row >= SIZE || column < 0 || column >= SIZE){
                    continue;
                }
                tmp += image[row][column][0];
            }
            for (int k = 0; k < RGB; ++k) {
                image2[i][j][k] = 255 - tmp;
            }
        }
    }
    for (int i = 0; i < SIZE; i++) {
        for (int j = 0; j< SIZE; j++) {
            for (int k = 0; k < RGB; ++k) {
                image[i][j][k] = image2[i][j][k];
            }
        }
    }
}

void MainWindow::on_detectBtn_clicked()
{
    detectEdges();
    updateImg();
}

void enlarge(int n_enlarge){
    unsigned char image2[SIZE][SIZE][RGB];
    int row = 1,column;
    for (int i = intervals[n_enlarge][0]; i < intervals[n_enlarge][1]; ++i) {
        column = 1;
        for (int j = intervals[n_enlarge][2]; j < intervals[n_enlarge][3]; ++j) {
            for (int k = 0; k < RGB; ++k) {
                image2[2*row - 2][2*column - 1][k] = image[i][j][k];
                image2[2*row - 1][2*column - 1][k] = image[i][j][k];
                image2[2*row - 1][2*column - 2][k] = image[i][j][k];
                image2[2*row - 2][2*column - 2][k] = image[i][j][k];
            }
            column ++;
        }
        row ++;
    }
    for (int i = 0; i < SIZE; i++) {
        for (int j = 0; j< SIZE; j++) {
            for (int k = 0; k < RGB; ++k) {
                image[i][j][k] = image2[i][j][k];
            }
        }
    }
}

void MainWindow::on_enlargeBtn_clicked()
{
    ui->enlarge_1->show();
    ui->enlarge_2->show();
    ui->enlarge_3->show();
    ui->enlarge_4->show();
}


void MainWindow::on_enlarge_1_clicked()
{
    ui->enlarge_1->hide();
    ui->enlarge_2->hide();
    ui->enlarge_3->hide();
    ui->enlarge_4->hide();
    enlarge(1);
    updateImg();
}


void MainWindow::on_enlarge_2_clicked()
{
    ui->enlarge_1->hide();
    ui->enlarge_2->hide();
    ui->enlarge_3->hide();
    ui->enlarge_4->hide();
    enlarge(2);
    updateImg();
}


void MainWindow::on_enlarge_3_clicked()
{
    ui->enlarge_1->hide();
    ui->enlarge_2->hide();
    ui->enlarge_3->hide();
    ui->enlarge_4->hide();
    enlarge(3);
    updateImg();
}


void MainWindow::on_enlarge_4_clicked()
{
    ui->enlarge_1->hide();
    ui->enlarge_2->hide();
    ui->enlarge_3->hide();
    ui->enlarge_4->hide();
    enlarge(4);
    updateImg();
}

