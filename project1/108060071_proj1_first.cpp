#include <iostream>
#include <string>
#include <sstream>
#include <fstream>

int matrix[16][41]; //因為row,col都從1開始而非0，所以matrix初始範圍長寬各加一
int matrix_width, matrix_height,r,n,id,right_limit,up_limit,row,top_row,hit_time;

int blocks[19][4][4]={ //19種方塊的形狀
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
void Clear(); //消行
void Define_id(std::string); //判斷輸入方塊id
void hit_bottom(); //判斷是否落底
void fall(); //下落一行
void block_to_matrix(); //將方塊填入matrix
void shift(); //左右平移
void all_move_down(int); //消行後往下掉落
/*bool Left_Boundary(void);
bool Right_Boundary(void);*/

using namespace std;
int main(int argc, char* argv[]){
    ifstream file(argv[1], ios::in);
    file >>  matrix_height >> matrix_width;
    for (int i = 1; i <= matrix_height; i++){
        for (int j = 1; j <= matrix_width; j++){
            matrix[i][j]=0;
        }
    }
    
    string s1, s2, s3, str;
    getline(file, str);
    top_row = 1;
    
    while( getline(file, s1, ' ')){
        if(s1 == "End"){
            break;
        }
        else{
            getline(file, s2, ' ');
            getline(file, s3);
            r=stoi(s2);
            n=stoi(s3);
            
            row = top_row+1;
            hit_time=0;
            Define_id(s1);
            hit_bottom();
        }
    }
    fstream file_out;
    file_out.open("108060071_proj1.final", ios::out);
    if(file.fail()){
        cout<<"Cannot open the file"<<endl;
    }
    else{
        for (int i = matrix_height; i >= 1; i--){
            for (int j = 1; j < matrix_width; j++)
            {
                file_out << matrix[i][j]<<" ";
            }
            file_out<<matrix[i][matrix_width]<<endl;
        }
    }
    return 0;
}

void hit_bottom(){
    bool hit =false;
    if( row == 1 ){ //是否已到底
        hit =true;
    }
    else{ //判斷每行第一個1在matrix裡的row-1是不是也是1
        for (int j = 0 ;j <= right_limit; j++){
            for (int i = 0 ;i <= up_limit; i++){
                if ( blocks[id][i][j] == 1 ){
                    if( matrix[row+i-1][r+j] == 1 ){
                        hit =true;
                        break;
                    }
                }
            }
            if(hit){break;}
        }
    }
    if(hit){
        if (hit_time == 0){//第一次落地
            hit_time += 1;
            shift();
        }
        else{//第二次落地
            block_to_matrix();
        }
    }
    else{
        fall();
    }
}

void fall(){
    row -= 1;
    hit_bottom();
}

void shift(){
    if(n != 0){
        r += n;
        hit_bottom();
    }
    else{
        block_to_matrix();
    }
}

void block_to_matrix(){
    for (int i = 0 ;i <= up_limit; i++){
        for (int j = 0 ;j <= right_limit; j++){
            if ( blocks[id][i][j] == 1 ){
                matrix[row+i][r+j]=1;
                //cout<<row+i<<" "<<r+j<<endl;
            }
        }
    }
    if( row + up_limit > top_row){
        top_row = row + up_limit;
    }
    Clear();
}

void Clear(){
    bool clear = true;
    for (int i = 1; i <= top_row ; i++){
        for (int j = 1 ; j <= matrix_width; j++){
            if(matrix[i][j] != 1){//有一個不是1就false
                clear = false;
                break;
            }
        }
        if( clear == true){//整列變0
            for (int m = 1; m <= matrix_width; m++){
                matrix[i][m]=0;
            }
            all_move_down(i);
            //break;
        }
        else{
            clear = true;
        }
    }
}

void all_move_down(int start){
    for (int i = start + 1; i <= top_row ; i++){
        for (int j = 1 ; j <= matrix_width; j++){
            matrix[i-1][j] = matrix[i][j];
            if( i == top_row ){
                matrix[i][j] = 0;
            }
        }
    }
    top_row -=1 ;
    Clear();
}

void Define_id(string a){
    if(a == "T1"){
        id = 0;
        right_limit = 2;
        up_limit = 1;
    }
    else if ( a == "T2"){
        id = 1;
        right_limit = 1;
        up_limit = 2;
    }
    else if ( a == "T3"){
        id = 2;
        right_limit = 2;
        up_limit = 1;
    }
    else if ( a == "T4"){
        id = 3;
        right_limit = 1;
        up_limit = 2;
    }
    else if ( a == "L1"){
        id = 4;
        right_limit = 1;
        up_limit = 2;
    }
    else if ( a == "L2"){
        id = 5;
        right_limit = 2;
        up_limit = 1;
    }
    else if ( a == "L3"){
        id = 6;
        right_limit = 1;
        up_limit = 2;
    }
    else if ( a == "L4"){
        id = 7;
        right_limit = 2;
        up_limit = 1;
    }
    else if ( a == "J1"){
        id = 8;
        right_limit = 1;
        up_limit = 2;
    }
    else if ( a == "J2"){
        id = 9;
        right_limit = 2;
        up_limit = 1;
    }
    else if ( a == "J3"){
        id = 10;
        right_limit = 1;
        up_limit = 2;
    }
    else if ( a == "J4"){
        id = 11;
        right_limit = 2;
        up_limit = 1;
    }
    else if ( a == "S1"){
        id = 12;
        right_limit = 2;
        up_limit = 1;
    }
    else if ( a == "S2"){
        id = 13;
        right_limit = 1;
        up_limit = 2;
    }
    else if ( a == "Z1"){
        id = 14;
        right_limit = 2;
        up_limit = 1;
    }
    else if ( a == "Z2"){
        id = 15;
        right_limit = 1;
        up_limit = 2;
    }
    else if ( a == "I1"){
        id = 16;
        right_limit = 0;
        up_limit = 3;
    }
    else if ( a == "I2"){
        id = 17;
        right_limit = 3;
        up_limit = 0;
    }
    else if ( a == "O"){
        id = 18;
        right_limit = 1;
        up_limit = 1;
    }
};


/*bool Left_Boundary(){
    if( r < 1){
        return false;
    }
    for(int i = 0; i <= up_limit; i++){
        if(matrix[row+i][r-1] == 1 && blocks[id][i][0] == 1){
            return false;
        }
    }
    return true;
}

bool Right_Boundary(){
    if( r > matrix_width){
        return false;
    }
    for(int i = 0; i <= up_limit; i++){
        if(matrix[row+i][r+right_limit+1] == 1 && blocks[id][i][r+right_limit] == 1){
            return false;
        }
    }
    return true;
}*/
