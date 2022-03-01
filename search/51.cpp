//
// Created by pc on 2022/3/1.
//
#include <string>
#include <vector>
using namespace std;
class Solution {
public:
    vector<vector<string>> solveNQueens(int n) {
        vector<vector<string>>ans;
        if(n==0){
        return ans;
    }
        vector<string>board(n,string(n,'.'));
        vector<bool>column(n, false);
        vector<bool>ldiag(2*n-1, false);//左斜右斜分别有2*n-1种，左斜（i-j）是定值，大小（-n+1,n-1）,全加个n-1就变成(0,2n-2)，就可用数组实现,[i-row+n-1]
        vector<bool>rdiag(2*n-1, false);//右斜(i+j)是定值，大小从(0,2n-2)
        backstracking(ans,board,column,ldiag,rdiag,0,n);
        return ans;
    }
    void backstracking(vector<vector<string>>&ans,vector<string>&board,vector<bool>&column,vector<bool>&ldiag,vector<bool>&rdiag,int row,int n){
        if(row==n){
            ans.push_back(board);
            return;
        }
        for(int i=0;i<n;++i){
            if(column[i]||ldiag[n-i+row-1]||rdiag[row+i]){
                continue;
            }
            board[row][i]='Q';
            column[i]=ldiag[n-i+row-1]=rdiag[row+i]=true;//修改当前节点状态
            backstracking(ans,board,column,ldiag,rdiag,row+1,n);//递归子节点
            board[row][i]='.';
            column[i]=ldiag[n-i+row-1]=rdiag[row+i]= false;//回归当前节点状态
        }

    }
};