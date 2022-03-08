//
// Created by pc on 2022/3/7.
//
#include <vector>
#include <string.h>
using namespace std;
class Solution {
private:
    bool line[9][9];
    bool colum[9][9];
    bool block[3][3][9];
    vector<pair<int,int>> spaces;
    bool valid = false;

public:
    void solveSudoku(vector<vector<char>>& board) {
        memset(line, false,sizeof (line));
        memset(colum, false,sizeof(colum));
        memset(block, false, sizeof(block));
        for(int i=0;i<9;++i){
            for(int j=0;j<9;++j){
                if(board[i][j]=='.'){
                    spaces.emplace_back(i,j);
                }else{
                    int num=board[i][j]-'0'-1;
                    line[i][num]= true;
                    colum[j][num]= true;
                    block[i/3][j/3][num]=true;
                }
            }
        }
        backtracking(board,0);
    }
    void backtracking(vector<vector<char>>& board,int pos){
        if(pos== spaces.size()){
            valid= true;
            return;
        }
        auto [i,j]=spaces[pos];
        for(int k=0;k<9&&!valid;++k){
            if(!line[i][k]&&!colum[j][k]&&!block[i/3][j/3][k]){
                line[i][k]=colum[j][k]=block[i/3][j/3][k]= true;
                board[i][j]= k+'0'+1;
                backtracking(board,pos+1);
                line[i][k]=colum[j][k]=block[i/3][j/3][k]= false;
            }
        }
    }
};