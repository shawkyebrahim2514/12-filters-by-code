#include <iostream>
#include <fstream>
#include <cstring>
#include <algorithm>
#include <cmath>
#include <vector>
#include "bmplib.cpp"
using namespace std;
int n_enlarge;
unsigned char image[SIZE][SIZE][RGB];
unsigned char image2[SIZE][SIZE][RGB];
// we will take the original intervals from image, the first is the first_start, the second is the first_end, the third is the second_start, the fourth is the second_end
vector<vector<int>>intervals{{0,0,0,0},{0,SIZE/2,0,SIZE/2},{0,SIZE/2,SIZE/2,SIZE},{SIZE/2,SIZE,0,SIZE/2},{SIZE/2,SIZE,SIZE/2,SIZE}};
int change_h,change_v;
void loadImage ();
void saveImage ();
void enlarge ();
void take_choice();
bool check_state();
void start();
int main()
{
    start();
}
//------------------------------------------------
void loadImage () {
    char imageFileName[100];

    // Get RGB scale image file name
    cout << "Enter the source image file name: ";
    cin >> imageFileName;

    // Add to it .bmp extension and load image
    strcat (imageFileName, ".bmp");
    readRGBBMP(imageFileName, image);
}
//------------------------------------------------
void take_choice(){
    cout << "Which quarter to enlarge 1, 2, 3 or 4?";
    cin >> n_enlarge;
    if(n_enlarge < 1 || n_enlarge > 4){
        cout << "Please choose correct choice\n";
        take_choice();
    }
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

void enlarge(){
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
    take_choice();
    enlarge();
    saveImage();
    if(check_state()){
        start();
    }
}