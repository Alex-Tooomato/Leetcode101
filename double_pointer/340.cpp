//
// Created by skyyw on 2022/1/27.
//
#include <iostream>
#include <unordered_map>
#include <algorithm>
using namespace std;
class Solution {
public:
    int remove_left(unordered_map<char,int>&mp){
        int left_most=INT32_MAX;
        char it0;
        for(const auto & p:mp){
           if(left_most>p.second){
               left_most=p.second;
               it0=p.first;
           }
        }
        mp.erase(it0);
        return left_most+1;
    }
    int lengthOfLongestSubstringKDistinct(string s, int k) {
    int n=s.size();
    if(n*k==0){
        return 0;
    }
    int left=0,right=0;
    int max_len=1;
    unordered_map<char,int> charnum;
    while(right<n){
        charnum[s[right]]=right;
        if(charnum.size()==k+1){
            left=remove_left(charnum);
        }
        max_len=max(max_len,right-left+1);
        right++;
    }
        return max_len;
    }
};