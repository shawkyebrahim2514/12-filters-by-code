#include <iostream>
#include <fstream>
#include <cstring>
#include <cmath>
#include "bmplib.cpp"
#include <vector>
using namespace std;
vector<pair<int,int>>detect_dir{{0,1},{1,0},{-1,0},{0,-1}};
unsigned char image[SIZE][SIZE];
unsigned char image2[SIZE][SIZE];
void loadImage ();
void saveImage ();
void black_and_white();
void detect_edges();
bool check_state();
void start();
int main()
{
    start();
}
//------------------------------------------------
void loadImage () {
    char imageFileName[100];

    // Get gray scale image file name
    cout << "Enter the source image file name: ";
    cin >> imageFileName;

    // Add to it .bmp extension and load image
    strcat (imageFileName, ".bmp");
    readGSBMP(imageFileName, image);
}
//------------------------------------------------
void saveImage () {
    char imageFileName[100];

    // Get gray scale image target file name
    cout << "Enter the target image file name: ";
    cin >> imageFileName;

    // Add to it .bmp extension and load image
    strcat (imageFileName, ".bmp");
    writeGSBMP(imageFileName, image2);
}
//------------------------------------------------

void black_and_white() {
    int mid_size = 0;
    for (int i = 0; i < SIZE; i++) {
        for (int j = 0; j< SIZE; j++) {
            mid_size += image[i][j];
        }
    }
    mid_size /= (SIZE * SIZE);
    for (int i = 0; i < SIZE; i++) {
        for (int j = 0; j< SIZE; j++) {
            if(image[i][j] > mid_size) {
                image[i][j] = 255;
            }else{
                image[i][j] = 0;
            }
        }
    }
}

void detect_edges(){
    for (int i = 0; i < SIZE; ++i) {
        for (int j = 0; j < SIZE; ++j) {
            int tmp = -4*(image[i][j]);
            for(auto val:detect_dir){
                int row = i + val.first, column = j + val.second;
                if( row < 0 || row >= SIZE || column < 0 || column >= SIZE){
                    continue;
                }
                tmp += image[row][column];
            }
            image2[i][j] = 255 - tmp;
        }
    }
}

bool check_state(){
    char tmp;
    cout << "Do you want to do another filter? (y)es or (n)o: ";
    cin >> tmp;
    if(tmp != 'y' && tmp != 'n'){
        cout << "Please enter correct choice.\n";
        check_state();
    }
    if(tmp == 'y'){
        return true;
    }
    return false;
}

void start(){
    loadImage();
    black_and_white();
    detect_edges();
    saveImage();
    if(check_state()){
        start();
    }
}