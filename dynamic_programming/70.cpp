//
// Created by pc on 2022/3/10.
//
using namespace std;
class Solution {
public:
    int climbStairs(int n) {
        if (n <= 2) {
            return n;
        }
        int pre1=1,pre2=2;
        int cur;
        for(int i=2;i<n;++i){
            cur=pre1+pre2;
            pre1=pre2;
            pre2=cur;
        }
        return cur;
    }
};