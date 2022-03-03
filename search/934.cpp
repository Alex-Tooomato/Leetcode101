//
// Created by pc on 2022/3/3.
//
#include <vector>
#include <queue>
using namespace std;
class Solution {
public:
    vector<int> directions{-1,0,1,0,-1};
    int shortestBridge(vector<vector<int>>& grid) {
        if(grid.size()==0)return 0;
        queue<pair<int,int>> points;
        int m=grid.size(),n=grid[0].size();
        bool flipped=false;
        for(int i=0;i<m;++i){
            if(flipped)break;
            for(int j=0;j<n;++j){
                if(grid[i][j]==1){
                    dfs(grid,points,m,n,i,j);
                    flipped= true;
                    break;
                }
            }
        }
        int x,y;
        int level=0;
        while(!points.empty()){
            ++level;
            int n_points=points.size();
            while(n_points--){
                auto [r,c]=points.front();
                points.pop();
                for(int k=0;k<4;++k){
                    x=r+directions[k],y=c+directions[k+1];
                    if(x>=0&&x<m&&y>=0&&y<n){
                        if(grid[r][c]==1){
                            return level;
                        }
                        if(grid[x][y]==2){
                            continue;
                        }
                        points.push({r,c});
                        grid[x][y]=2;
                    }
                }
            }
        }
    }
    void dfs(vector<vector<int>> &grid,queue<pair<int,int>> &points,int m,int n,int i,int j){
        if(i<0||i>=m||j<0||j>=n||grid[i][j]==2){
            return;
        }
        if(grid[i][j]==0){
            points.push({i,j});
            return;
        }
        grid[i][j]=2;
        dfs(grid,points,m,n,i-1,j);
        dfs(grid,points,m,n,i+1,j);
        dfs(grid,points,m,n,i,j-1);
        dfs(grid,points,m,n,i,j+1);
    }
};
