//
// Created by pc on 2022/3/11.
//
#include <vector>
#include <limits.h>
#include <iostream>
using namespace std;
class Solution {
public:
    vector<vector<int>> updateMatrix(vector<vector<int>>& mat) {
        if(mat.empty())return {};
        int m=mat.size(),n=mat[0].size();
        vector<vector<int>> dp(m,vector<int>(n,INT_MAX-1));
        for(int i=0;i<m;++i){
            for(int j=0;j<n;++j) {
                if (mat[i][j] == 0) {
                    dp[i][j] = 0;
                } else {
                    if (j > 0) {
                        dp[i][j] = min(dp[i][j], dp[i][j - 1] + 1);
                    }
                    if (i > 0) {
                        dp[i][j] = min(dp[i][j], dp[i - 1][j] + 1);
                    }
                }
            }
        }
        for(int i=m-1;i>=0;--i){
            for(int j=n-1;j>=0;--j){
                if(mat[i][j]!=0){
                    if(j<n-1){
                        dp[i][j] = min(dp[i][j], dp[i][j + 1] + 1);
                    }
                    if(i<m-1){
                        dp[i][j] = min(dp[i][j], dp[i + 1][j] + 1);
                    }
                }
            }
        }
        return dp;
    }
};
int main(){
    Solution s;
    vector<vector<int>> mat ={{0},{1}};
    vector<vector<int>> ans=s.updateMatrix(mat);
    for(auto&p:ans){
        for(auto &m:p){
            cout<<m<<endl;
        }
    }
    return 0;
}