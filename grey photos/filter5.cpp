#include <iostream>
#include <fstream>
#include <cstring>
#include <cmath>
#include <vector>
#include "bmplib.cpp"
using namespace std;
int n_rotation;
unsigned char image[SIZE][SIZE];
unsigned char image2[SIZE][SIZE];
// make a vector with the target pixels with rotation number
// degree 90 in index 0, degree 180 in index 1, degree 270 in index 2
// each index has three pairs that decide if the target number will be considered positive or negative or never
// first pair to put (SIZE - 1) number, second pair to put row number, third pair to put column number
// in each pair, the first part is referring to the new image pixel row, the second part is referring to the new image pixel column
vector<vector<pair<int,int>>>rotation_map{ {{1,0},{0,1},{-1,0}}, {{1,1},{-1,0},{0,-1}}, {{0,1},{0,-1},{1,0}} };
void loadImage ();
void saveImage ();
void rotate_img ();
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
    cout << "Rotate (90), (180) or (270) degrees?";
    cin >> n_rotation;
    if(n_rotation%90 != 0 && (n_rotation != 90 && n_rotation != 180 && n_rotation != 270)){
        cout << "Please enter correct choice.\n";
        take_choice();
        return;
    }
    n_rotation /= 90;
    n_rotation --;
}

//------------------------------------------------

void rotate_img() {
    for (int i = 0; i < SIZE; ++i) {
        for (int j = 0; j < SIZE; ++j) {
            int tmp_row = (SIZE - 1)*rotation_map[n_rotation][0].first + i*rotation_map[n_rotation][1].first + j*rotation_map[n_rotation][2].first;
            int tmp_column = (SIZE - 1)*rotation_map[n_rotation][0].second + i*rotation_map[n_rotation][1].second + j*rotation_map[n_rotation][2].second;
            image2[i][j] = image[tmp_row][tmp_column];
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
    rotate_img();
    saveImage();
    if(check_state()){
        start();
    }
}