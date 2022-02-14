//
// Created by skyyw on 2022/1/20.
//
#include <vector>
#include <algorithm>
using namespace std;
class Solution {
public:
    vector<vector<int>> reconstructQueue(vector<vector<int>>& people) {
        sort(people.begin(),people.end(),[](const vector<int>&a,const vector<int>b){
            return a[0]<b[0]||(a[0]==b[0]&&a[1]>b[1]);
        });
        int n=people.size();
        vector<vector<int>> ans(n);
        for(const vector<int>&person:people){
            int count=person[1]+1;
            for(int i=0;i<n;i++){
                if(ans[i].empty()){
                    --count;
                    if(!count){
                        ans[i]=person;
                        break;
                    }
                }
            }
        }
        return ans;
    }
    vector<vector<int>> reconstructQueue2(vector<vector<int>>& people){
        sort(people.begin(),people.end(),[](const vector<int>&u,const vector<int>&v){
            return u[0]>v[0]||(u[0]==v[0]&&u[1]<v[1]);
        });
        vector<vector<int>> ans;
        for(const vector<int>&person:people){
            ans.insert(ans.begin()+person[1],person);
        }
        return ans;
    }
};