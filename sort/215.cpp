//
// Created by pc on 2022/2/22.
//

#include <vector>
using namespace std;
class Solution {
public:
    int findKthLargest(vector<int>& nums, int k) {
    int l=0,r=nums.size()-1,target=nums.size()-k;
    while(l<r){
        int mid=quickSelection(nums,l,r);
        if(mid==target){
            return nums[target];
        }
        if(mid<target){
            l=mid+1;
        } else{
            r=mid-1;
        }
    }
        return nums[l];
    }
    int quickSelection(vector<int> &nums,int l,int r){
        int i=l+1,j=r;
        while(true){
            while(i<r&&nums[i]<=nums[l]){
                ++i;
            }
            while(l<j&&nums[j]>=nums[l]){//退出循环时nums[j]<nums[l]
                --j;
            }
            if(i>=j){
                break;
            }
            swap(nums[i],nums[j]);
        }
        swap(nums[l],nums[j]);
        return j;
    }
};