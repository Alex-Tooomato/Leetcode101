//
// Created by pc on 2022/3/7.
//
#include <vector>
#include <algorithm>
#include <iostream>
using namespace std;
class Solution {
public:
    void dfs(vector<int>& candidates,int target,int i,int n,int sum,vector<bool>  vis,vector<int> res,vector<vector<int>> &ans){
        if(i==n){return;}
        for(int j=i;j<n;++j){
            if(vis[j]||(j>0&&candidates[j]==candidates[j-1]&&!vis[j-1])){
                continue;
            }
            sum+=candidates[j];
            res.emplace_back(candidates[j]);
            vis[j]=true;
            if(sum==target){
                ans.emplace_back(res);
                return;
            }else if(sum>target){
                return;
            }else{
                dfs(candidates,target,j+1,n,sum,vis,res,ans);
            }
            sum-=candidates[j];
            vis[j]=false;
            res.pop_back();
        }
        return;
    }
    vector<vector<int>> combinationSum2(vector<int>& candidates, int target) {
        vector<vector<int>> ans;
        vector<int> res;
        int sum;
        vector<bool> vis;
        vis.resize(candidates.size(), false);
        int n=candidates.size();
        sort(candidates.begin(),candidates.end());
        dfs(candidates,target,0,n,sum,vis,res,ans);
        return ans;
    }
};
int main(){
    Solution s;
    vector<int> candidates={10,1,2,7,6,1,5};
    int target=8;
    vector<vector<int>> ans;
    ans=s.combinationSum2(candidates,target);
    for(int i=0;i<ans.size();++i){
        for(int j=0;j<ans[i].size();++j){
            cout<<ans[i][j]<<" ";
        }
        cout<<endl;
    }
    return 0;
}