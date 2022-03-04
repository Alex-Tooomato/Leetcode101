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

## 广度优先搜索

### 934. 最短的桥

#### [最短的桥](https://leetcode-cn.com/problems/shortest-bridge/)

深度寻岛，广度建桥

深度需要用栈实现，先入后出，广度需要用队列实现，先入先出

```c++
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
        while(!points.empty()){//没运行到这儿说明一层结束
            ++level;
            int n_points=points.size();
            while(n_points--){//n_points记录了一层中点数的数量
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
```

### 126. 单词接龙Ⅱ

#### [单词接龙 II](https://leetcode-cn.com/problems/word-ladder-ii/)

广度优先构图，深度优先遍历找到所有解。

```c++
#include <iostream>
#include <string>
#include <vector>
#include <set>
#include <unordered_set>
#include <unordered_map>
#include <queue>


using namespace std;

class Solution {
public:
    //官方
    vector<vector<string>> findLadders(string beginWord, string endWord, vector<string> &wordList) {
        vector<vector<string>> res;
        // 因为需要快速判断扩展出的单词是否在 wordList 里，因此需要将 wordList 存入哈希表，这里命名为「字典」
        unordered_set<string> dict = {wordList.begin(), wordList.end()};
        // 修改以后看一下，如果根本就不在 dict 里面，跳过
        if (dict.find(endWord) == dict.end()) {
            return res;
        }
        // 特殊用例处理
        dict.erase(beginWord);

        // 第 1 步：广度优先遍历建图
        // 记录扩展出的单词是在第几次扩展的时候得到的，key：单词，value：在广度优先遍历的第几层
        unordered_map<string, int> steps = {{beginWord, 0}};
        // 记录了单词是从哪些单词扩展而来，key：单词，value：单词列表，这些单词可以变换到 key ，它们是一对多关系
        unordered_map<string, set<string>> from = {{beginWord, {}}};
        int step = 0;
        bool found = false;
        queue<string> q = queue<string>{{beginWord}};
        int wordLen = beginWord.length();
        while (!q.empty()) {
            step++;
            int size = q.size();
            for (int i = 0; i < size; i++) {
                const string currWord = move(q.front());
                string nextWord = currWord;
                q.pop();
                // 将每一位替换成 26 个小写英文字母
                for (int j = 0; j < wordLen; ++j) {
                    const char origin = nextWord[j];
                    for (char c = 'a'; c <= 'z'; ++c) {
                        nextWord[j] = c;
                        if (steps[nextWord] == step) {
                            from[nextWord].insert(currWord);
                        }
                        if (dict.find(nextWord) == dict.end()) {
                            continue;
                        }
                        // 如果从一个单词扩展出来的单词以前遍历过，距离一定更远，为了避免搜索到已经遍历到，且距离更远的单词，需要将它从 dict 中删除
                        dict.erase(nextWord);
                        // 这一层扩展出的单词进入队列
                        q.push(nextWord);
                        // 记录 nextWord 从 currWord 而来
                        from[nextWord].insert(currWord);
                        // 记录 nextWord 的 step
                        steps[nextWord] = step;
                        if (nextWord == endWord) {
                            found = true;
                        }
                    }
                    nextWord[j] = origin;
                }
            }
            if (found) {
                break;
            }
        }
        // 第 2 步：深度优先遍历找到所有解，从 endWord 恢复到 beginWord ，所以每次尝试操作 path 列表的头部
        if (found) {
            vector<string> Path = {endWord};
            dfs(res, endWord, from, Path);
        }
        return res;
    }

    void dfs(vector<vector<string>> &res, const string &Node, unordered_map<string, set<string>> &from,
             vector<string> &path) {
        if (from[Node].empty()) {
            res.push_back({path.rbegin(), path.rend()});
            return;
        }
        for (const string &Parent: from[Node]) {
            path.push_back(Parent);
            dfs(res, Parent, from, path);
            path.pop_back();
        }
    }
    //leetcode101
    vector<vector<string>> findLadders2(string beginWord, string endWord, vector<string> &wordList){
        vector<vector<string>> ans;
        unordered_set<string> dict;
        for(auto & c:wordList){
            dict.insert(c);
        }
        if(dict.find(endWord)==dict.end()){
            return ans;
        }
        dict.erase(beginWord);
        dict.erase(endWord);
        unordered_set<string> q1{beginWord},q2{endWord};
        unordered_map<string,vector<string>> next;
        bool reversed= false,found= false;
        while(!q1.empty()){
            unordered_set<string> q;//存储的是下一级可能包含的word
            for(const auto&w:q1){
                string s=w;
                for(size_t i=0;i<s.size();++i){
                    char ch=s[i];
                    for(char c='a';c<='z';++c){
                        s[i]=c;
                        if(q2.count(s)){
                            reversed?next[s].push_back(w):next[w].push_back(s);//如果是正向，则w后跟着s，反向则s后跟着w（也就是w靠近endWord）,在图中s是w的前方
                            found= true;
                        }
                        if(dict.count(s)){
                            reversed?next[s].push_back(w):next[w].push_back(s);
                            q.insert(s);
                        }
                    }
                    s[i]=ch;//恢复
                }
            }//此时q1(也就是正向的set)遍历完
            if(found){
                break;
            }
            for(const auto&w:q){
                dict.erase(w);
            }
            if(q.size()<=q2.size()){
                q1=q;
            }else{
                reversed=!reversed;
                q1=q2;
                q2=q;
            }//如果q的大小比q2小，也就是下一级合适的点比相反方向小，则继续进行正向的遍历，反之则进行逆向
        }
        if(found){
            vector<string> path={beginWord};
            backtracking(next,path,beginWord,endWord,ans);
        }
        return ans;
    }
    void backtracking(unordered_map<string,vector<string>> &next,vector<string> &path ,const string &beginWord,const string &endWord,vector<vector<string>> &ans){
        if(beginWord==endWord){
            ans.push_back(path);
        }
        for(const auto&s:next[beginWord]){
            path.push_back(s);
            backtracking(next,path,s, endWord,ans);
            path.pop_back();
        }
    }

};


```

### 130. 被围绕的区域

#### [被围绕的区域](https://leetcode-cn.com/problems/surrounded-regions/)

```c++
#include <vector>
using namespace std;
class Solution {
public:
    void dfs(vector<vector<char>>& board,int x,int y){
        if(x<0||x>=board.size()||y<0||y>=board[0].size()||board[x][y]!='O'){
            return;
        }
        board[x][y]='A';
        dfs(board,x-1,y);
        dfs(board,x+1,y);
        dfs(board,x,y-1);
        dfs(board,x,y+1);
    }
    void solve(vector<vector<char>>& board) {
        if(board.empty()||board[0].empty())return;
        int m=board.size(),n=board[0].size();
        for(int i=0;i<m;++i){
            dfs(board,i,0);
            dfs(board,i,n-1);
        }
        for(int j=0;j<n-1;++j){
            dfs(board,0,j);
            dfs(board,m-1,j);
        }
        for(int i=0;i<m;++i){
            for(int j=0;j<n;++j){
                if(board[i][j]=='A'){
                    board[i][j]='O';
                } else if (board[i][j]=='O'){
                    board[i][j]='X';
                }
            }
        }
    }
};
```
