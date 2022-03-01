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

### 547. 省份数量

#### [省份数量](https://leetcode-cn.com/problems/number-of-provinces/)

```c++
#include <vector>
using namespace std;
class Solution {
public:

    int findCircleNum(vector<vector<int>>& isConnected) {
        if(isConnected.empty()||isConnected[0].empty())return 0;
        int n=isConnected.size();
        vector<bool> visited(n, false);
        int count=0;
        for(int i=0;i<isConnected.size();++i){//遍历的对象从表内的点变成了边上的点
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
```

### 417. 太平洋大西洋水流问题

#### [太平洋大西洋水流问题](https://leetcode-cn.com/problems/pacific-atlantic-water-flow/)

```c++
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
```

## 回溯法

### 46. 全排列

#### [全排列](https://leetcode-cn.com/problems/permutations/)

```c++
#include <vector>
using namespace std;
class Solution {
public:
    vector<vector<int>> permute(vector<int>& nums) {
        if(nums.empty()) return {};
        vector<vector<int>> ans;
        backtracking(nums,ans,0);
        return ans;
    }
    void backtracking(vector<int>&nums,vector<vector<int>> &ans,int level){
        if(level==nums.size()-1){
            ans.push_back(nums);
            return;
        }
        for(int i=level;i<nums.size();++i){
            swap(nums[i],nums[level]);//修改当前节点状态
            backtracking(nums,ans,level+1);//递归子节点
            swap(nums[i],nums[level]);//回改当前节点状态
        }
    }
};
```

### 77. 组合

#### [组合](https://leetcode-cn.com/problems/combinations/)

```c++
#include <vector>
using namespace std;
class Solution {
public:
    vector<vector<int>> combine(int n, int k) {
    vector<vector<int>> result;
    vector<int> ans(k,0);
    int count=0;
        backtracking(result,ans,count,1,n,k);
        return result;
    }
    void backtracking(vector<vector<int>> &result,vector<int>&ans,int &count,int pos,int n,int k){
        if(count==k){
            result.push_back(ans);
            return;
        }
        for(int i=pos;i<=n;++i){
            ans[count++]=i;修改当前节点状态
            backtracking(result,ans,count,i+1,n,k);
            --count;//回归当前结点状态
        }
    }
};
```

### 79. 单词搜索

#### [单词搜索](https://leetcode-cn.com/problems/word-search/)

```c++
#include <vector>
using namespace std;
class Solution {
public:
    bool exist(vector<vector<char>>& board, string word) {
        if(board.empty())return false;
        int m=board.size(),n=board[0].size();
        vector<vector<bool>> used(m,vector<bool>(n, false));
        bool find= false;
        for(int i=0;i<m;++i){
            for(int j=0;j<n;++j){
                backtracking(board,used,word,0,i,j,find);
            }
        }
        return find;
    }
    void backtracking(const vector<vector<char>>& board,vector<vector<bool>> & used,const string &word,int pos,int r,int c,bool & find){
    if(r<0||r>=board.size()||c<0||c>=board[0].size()){
        return;
    }
    if(used[r][c]||find||board[r][c]!=word[pos]){
        return;
    }
    if(pos==word.size()-1){
        find= true;
        return;
    }
    used[r][c]=true;
    backtracking(board,used,word,pos+1,r+1,c,find);
    backtracking(board,used,word,pos+1,r,c+1,find);
    backtracking(board,used,word,pos+1,r,c-1,find);
    backtracking(board,used,word,pos+1,r-1,c,find);
    used[r][c]=false;
    }
};
```

### 51. N皇后（困难）

#### [N 皇后](https://leetcode-cn.com/problems/n-queens/)

```c++
#include <string>
#include <vector>
using namespace std;
class Solution {
public:
    vector<vector<string>> solveNQueens(int n) {
        vector<vector<string>>ans;
        if(n==0){
        return ans;
    }
        vector<string>board(n,string(n,'.'));
        vector<bool>column(n, false);
        vector<bool>ldiag(2*n-1, false);//左斜右斜分别有2*n-1种，左斜（i-j）是定值，大小（-				n+1,n-1）,全加个n-1就变成(0,2n-2)，就可用数组实现,[i-row+n-1]
        vector<bool>rdiag(2*n-1, false);//右斜(i+j)是定值，大小从(0,2n-2)
        backstracking(ans,board,column,ldiag,rdiag,0,n);
        return ans;
    }
    void backstracking(vector<vector<string>>&ans,vector<string>&board,vector<bool>&column,vector<bool>&ldiag,vector<bool>&rdiag,int row,int n){
        if(row==n){
            ans.push_back(board);
            return;
        }
        for(int i=0;i<n;++i){
            if(column[i]||ldiag[n-i+row-1]||rdiag[row+i]){
                continue;
            }
            board[row][i]='Q';
            column[i]=ldiag[n-i+row-1]=rdiag[row+i]=true;//修改当前节点状态
            backstracking(ans,board,column,ldiag,rdiag,row+1,n);//递归子节点
            board[row][i]='.';
            column[i]=ldiag[n-i+row-1]=rdiag[row+i]= false;//回归当前节点状态
        }

    }
};
```

