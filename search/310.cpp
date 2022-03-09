//
// Created by pc on 2022/3/9.
//
#include <vector>
#include <unordered_map>
#include <queue>
using namespace std;
class Solution {
public:
    vector<int> findMinHeightTrees(int n, vector<vector<int>>& edges) {
    vector<int> ans;
    if(n==1){
        return {0};
    }
    unordered_map<int,int> degree;
    unordered_map<int,vector<int>> neighbors;
    for(auto & edge:edges){
        ++degree[edge[0]];
        ++degree[edge[1]];
        neighbors[edge[0]].emplace_back(edge[1]);
        neighbors[edge[1]].emplace_back(edge[0]);
    }

    queue<int> q;
    for(auto & point:degree){
        if(point.second==1){
            q.push(point.first);
            --degree[point.first];
        }
    }
    while(!q.empty()){
        ans.clear();
        int n_points=q.size();
        while(n_points--){
            int cur=q.front();
            q.pop();
            ans.emplace_back(cur);
            --degree[cur];
            for(auto & neigh:neighbors[cur]){
                --degree[neigh];
                if(degree[neigh]==1){
                    q.push(neigh);
                }
            }

        }
    }
        return ans;
    }

};