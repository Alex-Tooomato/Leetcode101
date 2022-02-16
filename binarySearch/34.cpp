//
// Created by pc on 2022/2/16.
//
#include <vector>
using namespace std;
class Solution {
public:
    int lower_location(vector<int>& nums, int target){
        int l=0,r=nums.size(),mid;
        while(l<r){
            mid=(l+r)/2;
            if(nums[mid]>=target){
                r=mid;
            } else{
                l=mid+1;
            }
        }
        return l;
    }
    int upper_location(vector<int>& nums, int target){
        int l=0,r=nums.size(),mid;
        while(l<r){
            mid=(l+r)/2;
            if(nums[mid]>target){
                r=mid;
            } else{
                l=mid+1;
            }
        }
        return l;
    }
    vector<int> searchRange(vector<int>& nums, int target) {
        if(nums.empty())return vector<int>{-1,-1};
        int lower=lower_location(nums,target);
        int upper= upper_location(nums,target)-1;
        if(lower==nums.size()||nums[lower]!=target){
            return vector<int>{-1,-1};
        }
        return vector<int>{lower,upper};
    }
};
