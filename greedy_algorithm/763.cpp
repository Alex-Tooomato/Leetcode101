//
// Created by skyyw on 2022/1/19.
//
#include <vector>
#include <string>
using namespace std;
class Solution {
public:
    vector<int> partitionLabels(string s) {
        if(s.size()==0){
            return vector<int>(0);
        }
    int last[26];
    int n=s.size();
    for(int i=0;i<n;i++){
        last[s[i]-'a']=i;
    }
    vector<int> ans;
    int start=0,end=0;
    for(int i=0;i<n;i++){
        end=max(end,last[s[i]-'a']);
        if(i==end){
            ans.push_back(end-start+1);
            start=end+1;
        }
    }
        return ans;
    }
};
