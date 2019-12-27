
#include<iostream>
#include<stdbool.h>
using namespace std;

static int count=1;

void print(int ** b,int n){

    for(int i=0;i<n;i++){
        for(int j=0;j<n;j++){
            cout << b[i][j] << " ";
        }
        cout << "\n";
    }
    cout << "\n";
}

bool check(int ** b,int row,int col,int n){
    
    //traverse through whole row to see if any queen is there in it
    for(int i=0;i<col;i++){
        if(b[row][i]){
            return false;
        }
    }

    //for upper diagonal elements
    for(int i=row,j=col ; i >= 0 && j >= 0 ; i--,j-- ){
        if(b[i][j]){
            return false;
        }
    }
    //for lower diagonal elements
    for(int i=row,j=col ; i < n && j >= 0 ; i++,j--){
        if(b[i][j]){
            return false;
        }
    }

    return true;
}

bool chessBoard(int ** b,int q,int n){
    if(q == n){
        cout << "Solution " << count++ << " :\n";
        print(b,n);
         return true;
    }
    bool res = false; 
    for(int i=0 ;i < n; i++){
        if(check(b,i,q,n)){
            b[i][q] = 1;
            // if(chessBoard(b,q+1,n)){
            //     return true;
            // }
            res = chessBoard(b, q + 1,n) || res; 
            b[i][q] = 0;
        }
    }
    return res;
}

int main(){
    int n;
    cout << "Enter the chessboard size :";
    cin >> n;
    // an array of size n will contain address of each column
    int ** board = new int*[n];
    //creating each column
    for(int i = 0; i < n; i++){
        board[i] = new int[n]{};
    }
    //for first queen start from col 0
    if(!chessBoard(board,0,n)){
        cout << "No Solution exists";
    }

}
