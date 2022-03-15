//
// Created by pc on 2022/3/12.
//
#include <iostream>
#include <unordered_set>
#include <vector>
using namespace std;
class Solution {
public:
    bool wordBreak(string s, vector<string>& wordDict) {
     unordered_set<string> dict;
     for(auto & word:wordDict){
         dict.insert(word);
     }
     int n=s.size();
     vector<bool> dp(n+1);
     dp[0]= true;
     for(int i=1;i<=n;++i){
         for(int j=0;j<i;++j){
             if(dp[j]&&dict.find(s.substr(j,i-j))!=dict.end()){
                 dp[i]= true;
             }
         }
     }
        return dp[n];
    }
};