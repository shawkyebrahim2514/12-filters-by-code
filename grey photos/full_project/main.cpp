#include <iostream>
#include "all_filters.cpp"
using namespace std;
bool is_valid_choice(char tmp){
    if((tmp >= '0' && tmp <= '9') || (tmp >= 'a' && tmp <= 'c') || tmp == 's') {
        return true;
    }
    return false;
}

bool run_filters(char tmp){
    switch (tmp) {
        case '0':
            return false;
        case '1':
            black_and_white();
            break;
        case '2':
            invert_img();
            break;
        case '3':
            loadImage("Please enter name of image file to merge with: ",image2);
            merge_img();
            break;
        case '4':
            run_flip();
            break;
        case '5':
            run_darken_and_lighten();
            break;
        case '6':
            run_rotation();
            break;
        case '7':
            black_and_white();
            detect_edges();
            break;
        case '8':
            run_enlarge();
            break;
        case '9':
            run_shrink();
            break;
        case 'a':
            run_mirror();
            break;
        case 'b':
            run_shuffle();
            break;
        case 'c':
            run_blur();
            break;
        case 's':
            saveImage();
            break;
    }
    return true;
}

void start(){
    char tmp;
    cout << "Please select a filter to apply or 0 to exit:\n";
    cout << "1- Black & White Filter\n";
    cout << "2- Invert Filter\n";
    cout << "3- Merge Filter\n";
    cout << "4- Flip Image\n";
    cout << "5- Darken and Lighten Image\n";
    cout << "6- Rotate Image\n";
    cout << "7- Detect Image Edges\n";
    cout << "8- Enlarge Image\n";
    cout << "9- Shrink Image\n";
    cout << "a- Mirror 1/2 Image\n";
    cout << "b- Shuffle Image\n";
    cout << "c- Blur Image\n";
    cout << "s- Save the image to a file\n";
    cout << "0- Exit\n";
    cin >> tmp;
    if(!is_valid_choice(tmp)){
        cout << "Enter correct choice\n";
        start();
    }
    if(run_filters(tmp)){
        make_copy();
        start();
    }
}
int main(){
    loadImage("Please enter file name of the image to process: ", image);
    start();
}