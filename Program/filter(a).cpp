#include <iostream>
#include <fstream>
#include <cstring>
#include <cmath>
#include "bmplib.cpp"
using namespace std;

unsigned char image[SIZE][SIZE];
unsigned char newimage[SIZE][SIZE];
int start_first, start_second, end_first, end_second, change_h,change_v;
void loadImage ();
void saveImage ();
void mirror_image ();
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

    // Get gray scale image file name
    cout << "Enter the source image file name: ";
    cin >> imageFileName;

    // Add to it .bmp extension and load image
    strcat (imageFileName, ".bmp");
    readGSBMP(imageFileName, image);
}
//------------------------------------------------
void take_choice(){
    char choice;
    cout << "Mirror (l)eft, (r)ight, (u)pper, (d)own side? ";
    cin >> choice;
    if(choice != 'l' && choice != 'r' && choice != 'u' && choice != 'd'){
        cout << "Please enter correct chocie.\n";
        take_choice();
        return;
    }
    switch (choice) {
        case 'l':
            start_first = start_second = 0;
            end_first = SIZE;
            end_second = SIZE / 2;
            change_v = 0;
            change_h = SIZE - 1;
            break;
        case 'r':
            start_first = 0;
            start_second = SIZE / 2;
            end_first = end_second = SIZE;
            change_v = 0;
            change_h = SIZE - 1;
            break;
        case 'u':
            start_first = SIZE / 2;
            start_second = 0;
            end_first = end_second = SIZE;
            change_v = SIZE - 1;
            change_h = 0;
            break;
        case 'd':
            start_first = start_second = 0;
            end_first = SIZE / 2;
            end_second = SIZE;
            break;
    }
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

void mirror_image() {
    for (int i = start_first; i < end_first; i++) {
        for (int j = start_second; j< end_second; j++) {
            image[abs(change_v-i)][abs(change_h-j)] = image[i][j];
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
    mirror_image();
    saveImage();
    if(check_state()){
        start();
    }
}