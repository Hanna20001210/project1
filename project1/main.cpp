
#include <iostream>
int **matrix;
int matrix_width, matrix_height,r,n,id,right_limit,up_limit,row;

int blocks[19][4][4]{
    {{0,1,0,0},{1,1,1,0},{0,0,0,0},{0,0,0,0}},//T1
    {{0,1,0,0},{1,1,0,0},{0,1,0,0},{0,0,0,0}},//T2
    {{1,1,1,0},{0,1,0,0},{0,0,0,0},{0,0,0,0}},//T3
    {{1,0,0,0},{1,1,0,0},{1,0,0,0},{0,0,0,0}},//T4
    {{1,1,0,0},{1,0,0,0},{1,0,0,0},{0,0,0,0}},//L1
    {{1,0,0,0},{1,1,1,0},{0,0,0,0},{0,0,0,0}},//L2
    {{0,1,0,0},{0,1,0,0},{1,1,0,0},{0,0,0,0}},//L3
    {{1,1,1,0},{0,0,1,0},{0,0,0,0},{0,0,0,0}},//L4
    {{1,1,0,0},{0,1,0,0},{0,1,0,0},{0,0,0,0}},//J1
    {{1,1,1,0},{1,0,0,0},{0,0,0,0},{0,0,0,0}},//J2
    {{1,0,0,0},{1,0,0,0},{1,1,0,0},{0,0,0,0}},//J3
    {{0,0,1,0},{1,1,1,0},{0,0,0,0},{0,0,0,0}},//J4
    {{1,1,0,0},{0,1,1,0},{0,0,0,0},{0,0,0,0}},//S1
    {{0,1,0,0},{1,1,0,0},{1,0,0,0},{0,0,0,0}},//S2
    {{0,1,1,0},{1,1,0,0},{0,0,0,0},{0,0,0,0}},//Z1
    {{1,0,0,0},{1,1,0,0},{0,1,0,0},{0,0,0,0}},//Z2
    {{1,0,0,0},{1,0,0,0},{1,0,0,0},{1,0,0,0}},//I1
    {{1,1,1,1},{0,0,0,0},{0,0,0,0},{0,0,0,0}},//I2
    {{1,1,0,0},{1,1,0,0},{0,0,0,0},{0,0,0,0}},//O
};

using namespace std;
int main(void) {
    
    cin >> matrix_width >> matrix_height;

    for (int i = 1; i <= matrix_height; i++)
    {
        matrix[i] = new int[matrix_width];
    }
    
    string name;
    cin>>name>>r>>n;
    
    Define_id(name);
    
    for (int i = 1; i <= matrix_height; i++)
    {
        delete[] matrix[i];
    }
    delete[] matrix;
    return 0;
}

bool Left_Boundary(){
    if( r < 1){
        return false;
    }
    for(int j = 0; j <= up_limit; j++){
        if(matrix[row+j][r-1] == 1 && blocks[id][j][0] == 1){
            
        }
    }
}

void Right_Boundary(){
    
}

void Clear(){
    bool clear = true;
    for (int i = 0; i < matrix_height ; i++){
        for (int j = matrix_width - 1; j >= 0; j--){
            if(matrix[i][j] != 0){
                clear = false;
                break;
            }
        }
        if(clear == true){
            for (int m = 0; m < matrix_width; m++){
                matrix[m][i]=0;
            }
        }
    }
}

void Define_id(string a){
    if(a == "T1"){
        id = 0;
        right_limit = 2;
    }
    else if ( a == "T2"){
        id = 1;
        right_limit = 1;
    }
    else if ( a == "T3"){
        id = 2;
        right_limit = 2;
    }
    else if ( a == "T4"){
        id = 3;
        right_limit = 1;
    }
    else if ( a == "L1"){
        id = 4;
        right_limit = 1;
    }
    else if ( a == "L2"){
        id = 5;
        right_limit = 2;
    }
    else if ( a == "L3"){
        id = 6;
        right_limit = 1;
    }
    else if ( a == "L4"){
        id = 7;
        right_limit = 2;
    }
    else if ( a == "J1"){
        id = 8;
        right_limit = 1;
    }
    else if ( a == "J2"){
        id = 9;
        right_limit = 2;
    }
    else if ( a == "J3"){
        id = 10;
        right_limit = 1;
    }
    else if ( a == "J4"){
        id = 11;
        right_limit = 2;
    }
    else if ( a == "S1"){
        id = 12;
        right_limit = 2;
    }
    else if ( a == "S2"){
        id = 13;
        right_limit = 1;
    }
    else if ( a == "Z1"){
        id = 14;
        right_limit = 2;
    }
    else if ( a == "Z2"){
        id = 15;
        right_limit = 1;
    }
    else if ( a == "I1"){
        id = 16;
        right_limit = 0;
    }
    else if ( a == "I2"){
        id = 17;
        right_limit = 3;
    }
    else if ( a == "O"){
        id = 18;
        right_limit = 1;
    }
}
