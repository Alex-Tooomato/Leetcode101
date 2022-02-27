# 第六章 一切皆可搜索

## 深度优先搜索

### 695. 岛屿的最大面积

#### [岛屿的最大面积](https://leetcode-cn.com/problems/max-area-of-island/)

此题的深度是某个点的四周相邻位置。四个方向，就需要分别进行深度搜索。为了防止重复搜索，需要将搜索过的位置标0。可用栈(stack)或递归来完成，两者原理相似。递归便于实现。但栈便于理解，且不容易出现递归栈满的情况。

```c++
#include <vector>
#include <stack>
using namespace std;
class Solution {
public:
    vector<int> direction={-1,0,1,0,-1};//代表四个方向。{-1,0}:x-1,y+0表示左边一格。
    //栈的写法
    int maxAreaOfIsland(vector<vector<int>>& grid) {
    int m=grid.size(),n=m?grid[0].size():0,local_area,area=0,x,y;
    for(int i=0;i<m;++i){
        for(int j=0;j<n;++j){
            if(grid[i][j]){
                local_area=1;
                stack<pair<int,int>> island;
                grid[i][j]=0;
                island.push({i,j});
                while(!island.empty()){
                    auto [r,c]=island.top();
                    island.pop();
                    for(int k=0;k<4;++k){
                        x=r+direction[k];
                        y=c+direction[k+1];
                        if(x>=0&&x<m&&
                            y>=0&&y<n&&grid[x][y]==1){
                            grid[x][y]=0;//防止重复搜索
                            ++local_area;
                            island.push({x,y});
                        }
                    }
                }
                area=max(area,local_area);
            }
        }
    }
        return area;
    }
        //递归写法
    int dfs(vector<vector<int>>& grid,int r,int c) {
      if(grid[r][c]==0)return 0;
      grid[r][c]=0;
      int x,y,area=1;
      for(int i=0;i<4;++i){
          x=r+direction[i];
          y=c+direction[i+1];
          if(x>=0&&x<grid.size()&&y>=0&&y<grid[0].size()&&grid[x][y]==1){
              area+=dfs(grid,x,y);
          }
      }
        return area;
    }
    int maxAreaOfIsland2(vector<vector<int>>& grid){
        if(grid.empty()||grid[0].empty())return 0;
        int max_area=0;
        for(int i=0;i<grid.size();++i){
            for(int j=0;j<grid[0].size();++j){
                if(grid[i][j]==1){
                    max_area=max(max_area,dfs(grid,i,j));
                }
            }
        }
        return max_area;
    }
};

```

