#include <iostream>
#include <fstream>
#include <cstring>
#include <algorithm>
#include <cmath>
#include <vector>
#include "bmplib.cpp"
using namespace std;
string order;
unsigned char image[SIZE][SIZE];
unsigned char newimage[SIZE][SIZE];
// we will take the original intervals from image, the first is the first_start, the second is the first_end, the third is the second_start, the fourth is the second_end
vector<vector<int>>intervals{{0,0,0,0},{0,SIZE/2,0,SIZE/2},{0,SIZE/2,SIZE/2,SIZE},{SIZE/2,SIZE,0,SIZE/2},{SIZE/2,SIZE,SIZE/2,SIZE}};
int change_h,change_v;
void loadImage ();
void saveImage ();
void shuffle_image ();
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
    bool check = true;
    cout << "New order of quarters ?";
    order = "";
    while (order.empty()){
        getline(cin , order);
    }
    order.erase(remove(order.begin(),order.end(),' '),order.end());
    for (int i = 0; i < 4; ++i) {
        if(order[i] < '1' || order[i] > '4'){
            check = false;
        }
    }
    if(order.size() != 4 || !check) {
        cout << "Please enter correct choice.\n";
        take_choice();
    }
    cout << "YES";
}
//------------------------------------------------
void saveImage () {
    char imageFileName[100];

    // Get gray scale image target file name
    cout << "Enter the target image file name: ";
    cin >> imageFileName;

    // Add to it .bmp extension and load image
    strcat (imageFileName, ".bmp");
    writeGSBMP(imageFileName, newimage);
}
//------------------------------------------------

void shuffle_image() {
    int row, column;
    for (int i = 0; i < 4; ++i) {
        // return the initial row number
        if (i<2){
            // if the quarter that we now draw in is in the upper half
            row = 0;
        }
        else{
            // if the quarter that we now draw in is in the lower half
            row = SIZE / 2;
        }
        // target is the quarter that we want to draw
        int target = order[i] - '0';
        // loop over each row of the target quarter
        for (int j = intervals[target][0]; j < intervals[target][1]; ++j) {
            // return the initial column number
            if(i == 0 || i == 2){
                // if the quarter that we now draw in is in the left half
                column = 0;
            }
            else{
                // if the quarter that we now draw in is in the right half
                column = SIZE / 2;
            }
            // loop over each column of the target quarter
            for (int k = intervals[target][2]; k < intervals[target][3]; ++k) {
                newimage[row][column] = image[j][k];
                column ++;
            }
            row ++;
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
    shuffle_image();
    saveImage();
    if(check_state()){
        start();
    }
}