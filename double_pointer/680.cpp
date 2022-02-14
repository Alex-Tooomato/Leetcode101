//
// Created by skyyw on 2022/1/25.
//

#include <string>
using namespace std;
class Solution {
public:
    bool check_left_Palindrome(string s,int left,int right){
        for(int i=left,j=right;i<j;++i,--j){
            if(s[i]!=s[j]){
                return false;
            }
        }
        return true;
    }
    bool validPalindrome(string s) {
    int left=0,right=s.size()-1;
    while(left<right){
        if(s[left]==s[right]){
            ++left;
            --right;
        }else  {
            return check_left_Palindrome(s,left,right-1)|| check_left_Palindrome(s,left+1,right);
        }
    }
        return true;
    }
};