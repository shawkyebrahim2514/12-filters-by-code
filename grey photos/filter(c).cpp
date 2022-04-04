#include <iostream>
#include <fstream>
#include <cstring>
#include <cmath>
#include <vector>
#include "bmplib.cpp"
using namespace std;
vector<pair<int,int>>all_dir{{1,1},{-1,-1},{1,-1},{-1,1},{0,1},{0,-1},{1,0},{-1,0}};
unsigned char image[SIZE][SIZE];
void loadImage ();
void saveImage ();
void blur();
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
    writeGSBMP(imageFileName, image);
}
//------------------------------------------------

void blur() {
    for (int i = 0; i < SIZE; i++) {
        for (int j = 0; j< SIZE; j++) {
            int cnt = 1,avrge = image[i][j];
            for(auto val : all_dir){
                int row = i + val.first, column = j + val.second;
                if(row < 0 || row >= SIZE || column <0 || column >= SIZE){
                    continue;
                }
                cnt ++;
                avrge += image[row][column];
            }
            image[i][j] = avrge/cnt;
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
    for(int i = 1; i <= 3; i++){
        blur();
    }
    saveImage();
    if(check_state()){
        start();
    }
}