#include <iostream>
#include <fstream>
#include <cstring>
#include <cmath>
#include "bmplib.cpp"
using namespace std;
int n_shrink;
unsigned char image[SIZE][SIZE];
unsigned char image2[SIZE][SIZE];
void loadImage ();
void saveImage ();
void shrink ();
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
void take_choice(){
    string tmp;
    cout << "Shrink to (1/2), (1/3) or (1/4)? ";
    cin >> tmp;
    if(tmp != "1/2" && tmp != "1/3" && tmp != "1/4"){
        cout << "Please enter correct choice\n";
        take_choice();
    }
    if(tmp == "1/2"){
        n_shrink = 2;
    }else if(tmp == "1/3"){
        n_shrink = 3;
    }else{
        n_shrink = 4;
    }
}

//------------------------------------------------

void shrink() {
    // make all pixels in image2 array are white 255
    for (int i = 0; i < SIZE; ++i) {
        for (int j = 0; j < SIZE; ++j) {
            image2[i][j] = 255;
        }
    }
    for (int i = 0; i < SIZE; ++i) {
        for (int j = 0; j < SIZE; ++j) {
            image2[i/n_shrink][j/n_shrink] = image[i][j];
        }
    }
    /*int row = 0, column = 0;
    for (int i = 0; i < SIZE; i += n_shrink) {
        for (int j = 0; j < SIZE; j += n_shrink) {
           int avrge = 0;
           // take the target pixels to convert to one pixel
            for (int k = i; k < i + n_shrink; ++k) {
                for (int l = j; l < j + n_shrink; ++l) {
                    avrge += image[k][l];
                }
            }
            //------------------------------------------------
            //cout << avrge<<'\n';
            cout << row << ' ' <<column << '\n';
            image2[row][column] = avrge / (n_shrink * n_shrink);
            column ++;
            column %= (SIZE/n_shrink);
        }
        row ++;
    }*/
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
    shrink();
    saveImage();
    if(check_state()){
        start();
    }
}