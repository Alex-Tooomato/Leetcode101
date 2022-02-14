//
// Created by skyyw on 2022/1/24.
//
#include <unordered_map>
//#include <iostream>
#include <string>
#include <vector>
using namespace std;
class Solution {
public:
    string minWindow(string s, string t) {
    vector<bool> flag(128,false);
    vector<int> chars(128,0);
    for(int i=0;i<t.size();i++){
    flag[t[i]]= true;
    ++chars[t[i]];
    }
    int l=0,cnt=0,min_l=0,min_size=s.size()+1;
    for(int r=0;r<s.size();r++){
        if(flag[s[r]]){
            if(--chars[s[r]]>=0){
                ++cnt;
            }
        }
        while(cnt==t.size()){
            if(r-l+1<min_size){
                min_l=l;
                min_size=r-l+1;
            }
            if(flag[s[l]]&&++chars[s[l]]>0){
                --cnt;
            }
            ++l;
        }
    }
        return min_size>s.size()?"":s.substr(min_l,min_size);
    }

    string minWindow2(string s, string t) {
        unordered_map<char,int>temp;
        for(const auto& x:t){
            ++temp[x];
        }
        int l=0,r=0,cnt=0;
        int min_l=0,min_size=s.size()+1;
        while(r<s.size()){
            if(temp.find(s[r])!=temp.end()){
                ++cnt;
                --temp[s[r]];
            }
            while(cnt==t.size()){
                if(r-l+1<min_size){
                    min_l=l;
                    min_size=r-l+1;
                }
                if((temp.find(s[l])!=temp.end())&&temp[s[l]]>=0){
                    --cnt;
                    ++temp[s[l]];
                }
                ++l;
            }
            ++r;
        }
        return min_size>s.size()?"":s.substr(min_l,min_size);
    }
    //用两个unordered_map，一个用来存储t中的个数，另一个用来进行循环计数
    unordered_map <char, int> ori, cnt;
    bool check(){
        for(const auto &p:ori){
            if(cnt[p.first]<p.second)
                return false;
        }
        return true;
    }
    string minWindow3(string s, string t) {

        for(const auto& x:t){
            ++ori[x];
        }
        int l=0,r=0;
        int min_l=0,min_size=s.size()+1;
        while(r<s.size()){
            if(ori.find(s[r])!=ori.end()){
                ++cnt[s[r]];
            }
            while(check()&&l<=r){
                if(r-l+1<min_size){
                    min_l=l;
                    min_size=r-l+1;
                }
                if(ori.find(s[l])!=ori.end()){
                    --cnt[s[l]];
                }
                ++l;
            }
            ++r;
        }
        return min_size>s.size()?string() :s.substr(min_l,min_size);
    }
};

//int main(){
//unordered_map<char,int> mybook={{'a',1},{'C',2}};
//cout<<mybook['C']<<endl;
//++mybook['D'];
//mybook['E'];
//cout<<mybook['E']<<endl;
//int i=1;
//int b=--i>0?1:0;
//cout<<b<<endl;
//    return 0;
//}