//
// Created by pc on 2022/3/1.
//
#include <vector>
using namespace std;
class Solution {
public:
    vector<vector<int>> permute(vector<int>& nums) {
        if(nums.empty()) return {};
        vector<vector<int>> ans;
        backtracking(nums,ans,0);
        return ans;
    }
    void backtracking(vector<int>&nums,vector<vector<int>> &ans,int level){
        if(level==nums.size()-1){
            ans.push_back(nums);
            return;
        }
        for(int i=level;i<nums.size();++i){
            swap(nums[i],nums[level]);
            backtracking(nums,ans,level+1);
            swap(nums[i],nums[level]);
        }
    }
};