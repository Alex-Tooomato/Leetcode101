//
// Created by pc on 2022/3/6.
//
#include <vector>
#include <algorithm>
using namespace std;
class Solution {
    vector<bool> vis;
public:
    vector<vector<int>> permuteUnique(vector<int>& nums) {
        vector<vector<int>> ans;
        vector<int> perm;
        vis.resize(nums.size());
        sort(nums.begin(),nums.end());
        backtracking(ans,nums,0,perm);
        return ans;
    }
    void backtracking(vector<vector<int>> &ans,vector<int>&nums,int idx,vector<int> &perm){
        if(idx==nums.size()){
            ans.emplace_back(perm);
            return;
        }
        for(int i=0;i<nums.size();++i){
            if(vis[i]||(i>0&&nums[i]==nums[i-1]&&!vis[i-1])){
                continue;
            }
            perm.emplace_back(nums[i]);
            vis[i]= true;
            backtracking(ans,nums,idx+1,perm);
            vis[i]= false;
            perm.pop_back();
        }
    }
};