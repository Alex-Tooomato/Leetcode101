//
// Created by pc on 2022/2/18.
//
#include <vector>
using namespace std;
class Solution {
public:
    int singleNonDuplicate(vector<int>& nums) {
        int low=0,high=nums.size()-1;
        while(low<high){
            int mid=(low+high)/2;
            if(nums[mid]==nums[mid^1]){
                low=mid+1;
            } else{
                high=mid;
            }
        }
        return nums[low];
    }
};