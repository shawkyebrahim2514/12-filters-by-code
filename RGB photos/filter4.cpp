#include <iostream>
#include <fstream>
#include <cstring>
#include <cmath>
#include "bmplib.cpp"
using namespace std;

unsigned char image[SIZE][SIZE][RGB];
unsigned char image2[SIZE][SIZE][RGB];
int change_h,change_v;
void loadImage ();
void saveImage ();
void flip_image ();
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
    char choice;
    cout << "Flip (h)orizontally or (v)ertically ? ";
    cin >> choice;
    if(choice != 'h' && choice != 'v'){
        cout << "Please enter correct chocie.\n";
        take_choice();
        return;
    }
    if(choice == 'h'){
        change_h = SIZE - 1;
        change_v = 0;
    }else{
        change_v = SIZE - 1;
        change_h = 0;
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

void flip_image() {
    for (int i = 0; i < SIZE; i++) {
        for (int j = 0; j< SIZE; j++) {
            for (int k = 0; k < RGB; ++k) {
                image2[abs(change_v-i)][abs(change_h-j)][k] = image[i][j][k];
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
    take_choice();
    flip_image();
    saveImage();
    if(check_state()){
        start();
    }
}