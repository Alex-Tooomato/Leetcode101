//
// Created by pc on 2022/3/1.
//
#include <vector>
#include <string>
using namespace std;
class Solution {
public:
    bool exist(vector<vector<char>>& board, string word) {
        if(board.empty())return false;
        int m=board.size(),n=board[0].size();
        vector<vector<bool>> used(m,vector<bool>(n, false));
        bool find= false;
        for(int i=0;i<m;++i){
            for(int j=0;j<n;++j){
                backtracking(board,used,word,0,i,j,find);
            }
        }
        return find;
    }
    void backtracking(const vector<vector<char>>& board,vector<vector<bool>> & used,const string &word,int pos,int r,int c,bool & find){
    if(r<0||r>=board.size()||c<0||c>=board[0].size()){
        return;
    }
    if(used[r][c]||find||board[r][c]!=word[pos]){
        return;
    }
    if(pos==word.size()-1){
        find= true;
        return;
    }
    used[r][c]=true;
    backtracking(board,used,word,pos+1,r+1,c,find);
    backtracking(board,used,word,pos+1,r,c+1,find);
    backtracking(board,used,word,pos+1,r,c-1,find);
    backtracking(board,used,word,pos+1,r-1,c,find);
    used[r][c]=false;
    }
};
