//
// Created by pc on 2022/3/4.
//
#include <vector>
using namespace std;
class Solution {
public:
    void dfs(vector<vector<char>>& board,int x,int y){
        if(x<0||x>=board.size()||y<0||y>=board[0].size()||board[x][y]!='O'){
            return;
        }
        board[x][y]='A';
        dfs(board,x-1,y);
        dfs(board,x+1,y);
        dfs(board,x,y-1);
        dfs(board,x,y+1);
    }
    void solve(vector<vector<char>>& board) {
        if(board.empty()||board[0].empty())return;
        int m=board.size(),n=board[0].size();
        for(int i=0;i<m;++i){
            dfs(board,i,0);
            dfs(board,i,n-1);
        }
        for(int j=0;j<n-1;++j){
            dfs(board,0,j);
            dfs(board,m-1,j);
        }
        for(int i=0;i<m;++i){
            for(int j=0;j<n;++j){
                if(board[i][j]=='A'){
                    board[i][j]='O';
                } else if (board[i][j]=='O'){
                    board[i][j]='X';
                }
            }
        }
    }
};
