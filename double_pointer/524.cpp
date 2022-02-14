//
// Created by skyyw on 2022/1/25.
//
#include <iostream>
#include <vector>
using namespace std;
class Solution {
public:
    string findLongestWord(string s, vector<string>& dictionary) {
        string res="";
        int len=0;
    for(const string&p:dictionary){
        int i=0,j=0;
        while(i<p.size()&&j<s.size()){
            if(p[i]==s[j]){
                if(i==p.size()-1){
                    if(p.size()>len||(p.size()==len&&p<res)){
                        res=p;
                        len=p.size();
                    }
                    break;
                }
                ++j;
                ++i;
            } else{
                ++j;
            }
        }
    }
        return res;
    }
};