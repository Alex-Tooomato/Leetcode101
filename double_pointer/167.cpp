//
// Created by skyyw on 2022/1/21.
//
#include <vector>
using namespace std;
class Solution {
public:
    vector<int> twoSum(vector<int>& numbers, int target) {
    int left=0,right=numbers.size()-1,sum;
    while(left<right){
        sum=numbers[left]+numbers[right];
        if(sum==target) break;
        if(sum<target) ++left;
        else --right;
    }
        return vector<int>{left+1,right+1};
    }
};
