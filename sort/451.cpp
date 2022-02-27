//
// Created by pc on 2022/2/25.
//
#include <iostream>
#include <unordered_map>
#include <vector>
using namespace std;

class Solution {
public:
    string frequencySort(string s) {
        unordered_map<char,int> counts;
        int max_count=0;
        for(auto & num:s){
            max_count=max(max_count,++counts[num]);
        }
        vector<vector<int>> buckets(max_count+1);
        for(auto & p:counts){
            buckets[p.second].push_back(p.first);
        }
        string ans;
        for(int i=max_count;i>0;--i){
                for(auto & num:buckets[i]){
                    for(int j=i;j>0;--j){
                        ans.push_back(num);
                    }
            }
        }
        return ans;
    }
};
