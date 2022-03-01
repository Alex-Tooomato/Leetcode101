//
// Created by pc on 2022/2/28.
//
#include <vector>
using namespace std;
class Solution {
public:

    int findCircleNum(vector<vector<int>>& isConnected) {
        if(isConnected.empty()||isConnected[0].empty())return 0;
        int n=isConnected.size();
        vector<bool> visited(n, false);
        int count=0;
        for(int i=0;i<isConnected.size();++i){
                if(!visited[i]){
                    dfs(isConnected,i,visited);
                    ++count;
                }
        }
        return count;
    }
    void dfs(vector<vector<int>>& isConnected,int i,vector<bool>& visited){
        visited[i]= true;
        for(int k=0;k<isConnected.size();++k){
            if(isConnected[i][k]==1&&!visited[k]){
                dfs(isConnected,k,visited);
            }
        }
    }
};