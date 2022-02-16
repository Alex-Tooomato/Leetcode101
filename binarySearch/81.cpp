//
// Created by pc on 2022/2/16.
//
#include <vector>
using namespace std;
class Solution {
public:
    bool search(vector<int>& nums, int target) {
int l=0,r=nums.size()-1,mid;
while(l<=r){
    mid=(l+r)/2;
    if(nums[mid]==target){
        return true;
    }
    if(nums[mid]==nums[l]){
        ++l;
    } else if(nums[mid]<=nums[r]){
        if(target>nums[mid]&&target<=nums[r]){
            l=mid+1;
        } else{
            r=mid-1;
        }
    }else{
        if(target>=nums[l]&&target<nums[mid]){
            r=mid-1;
        } else{
            l=mid+1;
        }
    }
}
        return false;
    }
};
