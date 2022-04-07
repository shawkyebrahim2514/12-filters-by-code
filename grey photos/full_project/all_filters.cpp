#include <iostream>
#include <algorithm>
#include "bmplib.cpp"
using namespace std;


string shuffle_order;
bool lighten;
unsigned char image[SIZE][SIZE];
unsigned char image2[SIZE][SIZE];
vector<pair<int,int>>detect_dir{{0,1},{1,0},{-1,0},{0,-1}};
vector<pair<int,int>>all_dir{{1,1},{-1,-1},{1,-1},{-1,1},{0,1},{0,-1},{1,0},{-1,0}};
vector<vector<int>>intervals{{0,0,0,0},{0,SIZE/2,0,SIZE/2},{0,SIZE/2,SIZE/2,SIZE},{SIZE/2,SIZE,0,SIZE/2},{SIZE/2,SIZE,SIZE/2,SIZE}};
// make a vector with the target pixels with rotation number
// degree 90 in index 0, degree 180 in index 1, degree 270 in index 2
// each index has three pairs that decide if the target number will be considered positive or negative or never
// first pair to put (SIZE - 1) number, second pair to put row number, third pair to put column number
// in each pair, the first part is referring to the new image pixel row, the second part is referring to the new image pixel column
vector<vector<pair<int,int>>>rotation_map{ {{1,0},{0,1},{-1,0}}, {{1,1},{-1,0},{0,-1}}, {{0,1},{0,-1},{1,0}} };
int start_first, start_second, end_first, end_second, change_h,change_v, n_rotation, n_enlarge, n_shrink;


//-------------------------------------------------
void make_copy(){
    for (int i = 0; i < SIZE; ++i) {
        for (int j = 0; j < SIZE; ++j) {
            image[i][j] = image2[i][j];
        }
    }
}
//-------------------------------------------------
void loadImage (string paragraph, unsigned char img_arr[SIZE][SIZE]) {
    char imageFileName[100];

    // Get gray scale image file name
    cout << paragraph;
    cin >> imageFileName;

    // Add to it .bmp extension and load image
    strcat (imageFileName, ".bmp");
    if(readGSBMP(imageFileName, img_arr)){
        cout << "Please enter correct image name\n";
        loadImage(paragraph, img_arr);
    }
}
//-------------------------------------------------
void saveImage () {
    char imageFileName[100];

    // Get gray scale image target file name
    cout << "Enter the target image file name: ";
    cin >> imageFileName;

    // Add to it .bmp extension and load image
    strcat (imageFileName, ".bmp");
    writeGSBMP(imageFileName, image2);
}
//-------------------------------------------------
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
                image2[i][j] = 255;
            }else{
                image2[i][j] = 0;
            }
        }
    }
}
//-------------------------------------------------
void invert_img() {
    for (int i = 0; i < SIZE; ++i) {
        for (int j = 0; j < SIZE; ++j) {
            image2[i][j] = 255 - image[i][j];
        }
    }
}
//-------------------------------------------------
void merge_img() {
    for (int i = 0; i < SIZE; ++i) {
        for (int j = 0; j < SIZE; ++j) {
            image2[i][j] = (image[i][j] + image2[i][j])/2;
        }
    }
}
//-------------------------------------------------
void flip_image() {
    for (int i = 0; i < SIZE; i++) {
        for (int j = 0; j< SIZE; j++) {
            image2[abs(change_v-i)][abs(change_h-j)] = image[i][j];
        }
    }
}
//-------------------------------------------------
void rotate_img() {
    for (int i = 0; i < SIZE; ++i) {
        for (int j = 0; j < SIZE; ++j) {
            int tmp_row = (SIZE - 1)*rotation_map[n_rotation][0].first + i*rotation_map[n_rotation][1].first + j*rotation_map[n_rotation][2].first;
            int tmp_column = (SIZE - 1)*rotation_map[n_rotation][0].second + i*rotation_map[n_rotation][1].second + j*rotation_map[n_rotation][2].second;
            image2[i][j] = image[tmp_row][tmp_column];
        }
    }
}
//-------------------------------------------------
void darken_lighten() {
    int amount = 64;
    for (int i = 0; i < SIZE; i++) {
        for (int j = 0; j< SIZE; j++) {
            if(lighten) {
                image2[i][j] = min(255, image[i][j] + amount);
            }else{
                image2[i][j] = max(0, image[i][j] - amount);
            }
        }
    }
}
//-------------------------------------------------
void detect_edges(){
    make_copy();
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
//-------------------------------------------------
void enlarge(){
    int row = 1,column;
    for (int i = intervals[n_enlarge][0]; i < intervals[n_enlarge][1]; ++i) {
        column = 1;
        for (int j = intervals[n_enlarge][2]; j < intervals[n_enlarge][3]; ++j) {
            image2[2*row - 2][2*column - 1] = image[i][j];
            image2[2*row - 1][2*column - 1] = image[i][j];
            image2[2*row - 1][2*column - 2] = image[i][j];
            image2[2*row - 2][2*column - 2] = image[i][j];
            column ++;
        }
        row ++;
    }
}
//-------------------------------------------------
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
}
//-------------------------------------------------
void mirror_image() {
    for (int i = 0; i < SIZE; ++i) {
        for (int j = 0; j < SIZE; ++j) {
            image2[i][j] = image[i][j];
        }
    }
    for (int i = start_first; i < end_first; i++) {
        for (int j = start_second; j< end_second; j++) {
            image2[abs(change_v-i)][abs(change_h-j)] = image[i][j];
        }
    }
}
//-------------------------------------------------
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
        int target = shuffle_order[i] - '0';
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
                image2[row][column] = image[j][k];
                column ++;
            }
            row ++;
        }
    }
}
//-------------------------------------------------
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
            image2[i][j] = avrge/cnt;
        }
    }
}
//-------------------------------------------------
void run_flip(){
    // take user choice h or v
    char choice;
    cout << "Flip (h)orizontally or (v)ertically ? ";
    cin >> choice;
    if(choice != 'h' && choice != 'v'){
        cout << "Please enter correct chocie.\n";
        run_flip();
        return;
    }
    if(choice == 'v'){
        change_h = SIZE - 1;
        change_v = 0;
    }else{
        change_v = SIZE - 1;
        change_h = 0;
    }
    //----------------------------------------------
    flip_image();
}
//-------------------------------------------------
void run_darken_and_lighten(){
    // take user input d or l
    char tmp;
    cout << "Do you want to (d)arken or (l)ighten? ";
    cin >> tmp;
    if(tmp != 'd' && tmp != 'l'){
        cout << "Please enter the correct choice\n";
        run_darken_and_lighten();
        return;
    }
    if(tmp == 'd'){
        lighten = false;
    }else{
        lighten = true;
    }
    //------------------------------
    darken_lighten();
}
//-------------------------------------------------
void run_rotation(){
    // take user input 90 or 180 or 270
    cout << "Rotate (90), (180) or (270) degrees?";
    cin >> n_rotation;
    if(n_rotation%90 != 0 && (n_rotation != 90 && n_rotation != 180 && n_rotation != 270)){
        cout << "Please enter correct choice.\n";
        run_rotation();
        return;
    }
    n_rotation /= 90;
    n_rotation --;
    //--------------------------------------
    rotate_img();
}
//-------------------------------------------------
void run_enlarge(){
    // take user input 1 or 2 or 3 or 4
    cout << "Which quarter to enlarge 1, 2, 3 or 4?";
    cin >> n_enlarge;
    if(n_enlarge < 1 || n_enlarge > 4){
        cout << "Please choose correct choice\n";
        run_enlarge();
        return;
    }
    //------------------------------------
    enlarge();
}
//-------------------------------------------------
void run_shrink(){
    // take user input 1/2 or 1/3 or 1/4
    string tmp;
    cout << "Shrink to (1/2), (1/3) or (1/4)? ";
    cin >> tmp;
    if(tmp != "1/2" && tmp != "1/3" && tmp != "1/4"){
        cout << "Please enter correct choice\n";
        run_shrink();
    }
    if(tmp == "1/2"){
        n_shrink = 2;
    }else if(tmp == "1/3"){
        n_shrink = 3;
    }else{
        n_shrink = 4;
    }
    //-------------------------------------
    shrink();
}
//-------------------------------------------------
void run_mirror(){
    // take user input r or l or u or d
    char choice;
    cout << "Mirror (l)eft, (r)ight, (u)pper, (d)own side? ";
    cin >> choice;
    if(choice != 'l' && choice != 'r' && choice != 'u' && choice != 'd'){
        cout << "Please enter correct chocie.\n";
        run_mirror();
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
        case 'd':
            start_first = SIZE / 2;
            start_second = 0;
            end_first = end_second = SIZE;
            change_v = SIZE - 1;
            change_h = 0;
            break;
        case 'u':
            start_first = start_second = 0;
            end_first = SIZE / 2;
            end_second = SIZE;
            change_v = SIZE - 1;
            change_h = 0;
            break;
    }
    //-----------------------------------------
    mirror_image();
}
//-------------------------------------------------
void run_shuffle(){
    // take user input (new order of quarters)
    bool check = true;
    cout << "New shuffle_order of quarters ?";
    shuffle_order = "";
    while (shuffle_order.empty()){
        getline(cin , shuffle_order);
    }
    shuffle_order.erase(remove(shuffle_order.begin(),shuffle_order.end(),' '),shuffle_order.end());
    for (int i = 0; i < 4; ++i) {
        if(shuffle_order[i] < '1' || shuffle_order[i] > '4'){
            check = false;
        }
    }
    if(shuffle_order.size() != 4 || !check) {
        cout << "Please enter correct choice.\n";
        run_shuffle();
        return;
    }
    shuffle_image();
    //-------------------------------------
}
//-------------------------------------------------
void run_blur(){
    for (int i = 1; i <= 3; ++i) {
        blur();
        make_copy();
    }
}
//-------------------------------------------------