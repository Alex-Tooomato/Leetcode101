//
// Created by pc on 2022/3/1.
//
#include <vector>
using namespace std;
class Solution {
public:
    vector<int> directions={-1,0,1,0,-1};
    vector<vector<int>> pacificAtlantic(vector<vector<int>>& heights) {
        if(heights.empty()||heights[0].empty())return {};
        vector<vector<int>> result;
        int m=heights.size(),n=heights[0].size();
        vector<vector<bool>> can_reach_p(m,vector<bool>(n,false));
        vector<vector<bool>> can_reach_a(m,vector<bool>(n,false));
        for(int i=0;i<m;++i){
            dfs(heights,can_reach_p,i,0);
            dfs(heights,can_reach_a,i,n-1);
        }
        for(int j=0;j<n;++j){
            dfs(heights,can_reach_p,0,j);
            dfs(heights,can_reach_a,m-1,j);
        }
        for(int i=0;i<m;++i){
            for(int j=0;j<n;++j){
                if(can_reach_a[i][j]&&can_reach_p[i][j]){
                    result.push_back(vector<int>{i,j});
                }
            }
        }
        return result;
    }
    void dfs(const vector<vector<int>>& heights,vector<vector<bool>> &can_reach,int r,int c){
        if(can_reach[r][c]){
                return;
        }
        can_reach[r][c]=true;
        int x,y;
        for(int k=0;k<4;++k){
            x=r+directions[k];
            y=c+directions[k+1];
            if(x>=0&&x<heights.size()&&y>=0&&y<heights[0].size()&&heights[x][y]>=heights[r][c]){
                dfs(heights,can_reach,x,y);
            }
        }
    }
};