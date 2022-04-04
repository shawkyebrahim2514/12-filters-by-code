#include <iostream>
#include <fstream>
#include <cstring>
#include <cmath>
#include "bmplib.cpp"
#include <vector>
using namespace std;
vector<pair<int,int>>detect_dir{{0,1},{1,0},{-1,0},{0,-1}};
unsigned char image[SIZE][SIZE][RGB];
unsigned char image2[SIZE][SIZE][RGB];
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

    // Get RGB ay scale image file name
    cout << "Enter the source image file name: ";
    cin >> imageFileName;

    // Add to it .bmp extension and load image
    strcat (imageFileName, ".bmp");
    readRGBBMP(imageFileName, image);
}
//------------------------------------------------
void saveImage () {
    char imageFileName[100];

    // Get RGB scale image target file name
    cout << "Enter the target image file name: ";
    cin >> imageFileName;

    // Add to it .bmp extension and load image
    strcat (imageFileName, ".bmp");
    writeRGBBMP(imageFileName, image2);
}
//------------------------------------------------

void black_and_white() {
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

void detect_edges(){
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