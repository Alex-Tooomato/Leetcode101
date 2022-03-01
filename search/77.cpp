//
// Created by pc on 2022/3/1.
//
#include <vector>
using namespace std;
class Solution {
public:
    vector<vector<int>> combine(int n, int k) {
    vector<vector<int>> result;
    vector<int> ans(k,0);
    int count=0;
        backtracking(result,ans,count,1,n,k);
        return result;
    }
    void backtracking(vector<vector<int>> &result,vector<int>&ans,int &count,int pos,int n,int k){
        if(count==k){
            result.push_back(ans);
            return;
        }
        for(int i=pos;i<=n;++i){
            ans[count++]=i;
            backtracking(result,ans,count,i+1,n,k);
            --count;
        }
    }
};