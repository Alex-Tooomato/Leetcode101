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

### 257. 二叉树的所有路径

#### [二叉树的所有路径](https://leetcode-cn.com/problems/binary-tree-paths/)

```c++
#include <string>
#include <vector>
using namespace std;
// Definition for a binary tree node.
 struct TreeNode {
      int val;
      TreeNode *left;
      TreeNode *right;
      TreeNode() : val(0), left(nullptr), right(nullptr) {}
      TreeNode(int x) : val(x), left(nullptr), right(nullptr) {}
      TreeNode(int x, TreeNode *left, TreeNode *right) : val(x), left(left), right(right) {}
  };

class Solution {
public:
    vector<string> binaryTreePaths(TreeNode* root) {
    vector<string> ans;
        backtracking(root,ans,"");
        return ans;
    }
    void backtracking(TreeNode * root,vector<string> &ans,string s){
        if(root!= nullptr){
            s+= to_string(root->val);
            if(root->left== nullptr&&root->right== nullptr){
                ans.push_back(s);
            } else{
                s+="->";
                backtracking(root->left,ans,s);
                backtracking(root->right,ans,s);//用栈实现了回溯
                //由于string每次传入不一定是一个字符，所以不方便用pop_back来实现回溯。
            }
        }

    }
};
//硬要用的话可以
        if(root!= nullptr){
            s+= to_string(root->val);
            if(root->left== nullptr&&root->right== nullptr){
                ans.push_back(s);
            } else{
                s+="->";
                backtracking(root->left,ans,s);
                backtracking(root->right,ans,s);
                s.pop_back();
                s.pop_back();
            }
            for(int i=0;i<to_string(root->val).size();++i){
                s.pop_back();
            }
        }
```

### 47. 全排列Ⅱ

#### [全排列 II](https://leetcode-cn.com/problems/permutations-ii/)

```c++
#include <vector>
#include <algorithm>
using namespace std;
class Solution {
    vector<bool> vis;
public:
    vector<vector<int>> permuteUnique(vector<int>& nums) {
        vector<vector<int>> ans;
        vector<int> perm;
        vis.resize(nums.size());
        sort(nums.begin(),nums.end());
        backtracking(ans,nums,0,perm);
        return ans;
    }
    void backtracking(vector<vector<int>> &ans,vector<int>&nums,int idx,vector<int> &perm){
        if(idx==nums.size()){
            ans.emplace_back(perm);
            return;
        }
        for(int i=0;i<nums.size();++i){
            if(vis[i]||(i>0&&nums[i]==nums[i-1]&&!vis[i-1])){
                continue;
            }
            perm.emplace_back(nums[i]);
            vis[i]= true;
            backtracking(ans,nums,idx+1,perm);
            vis[i]= false;
            perm.pop_back();
        }
    }
};
```

### 40. 组合总和III

#### [组合总和 II](https://leetcode-cn.com/problems/combination-sum-ii/)

```c++
#include <vector>
#include <algorithm>
#include <iostream>
using namespace std;
class Solution {
public:
    //同上一题的去重方法
    void backtracking(vector<int>& candidates,int target,int i,int n,int sum,vector<bool> vis,vector<int> res,vector<vector<int>> &ans){
        if(i==n){return;}
        for(int j=i;j<n;++j){
            if(vis[j]||(j>0&&candidates[j]==candidates[j-1]&&!vis[j-1])){
                continue;
            }
            sum+=candidates[j];
            res.emplace_back(candidates[j]);
            vis[j]=true;
            if(sum==target){
                ans.emplace_back(res);
                return;
            }else if(sum>target){
                return;
            }else{
                backtracking(candidates,target,j+1,n,sum,vis,res,ans);
            }
            sum-=candidates[j];
            vis[j]=false;
            res.pop_back();
        }
        return;
    }
    vector<vector<int>> combinationSum2(vector<int>& candidates, int target) {
        vector<vector<int>> ans;
        vector<int> res;
        int sum;
        vector<bool> vis;
        vis.resize(candidates.size(), false);
        int n=candidates.size();
        sort(candidates.begin(),candidates.end());
        backtracking(candidates,target,0,n,sum,vis,res,ans);
        return ans;
    }
    //官方解答，用freq记录相同数出现的次数，将相同的数一起处理，处理相同的数出现不同次数的情况
    private:
    vector<pair<int, int>> freq;
    vector<vector<int>> ans;
    vector<int> sequence;

public:
    void dfs(int pos, int rest) {
        if (rest == 0) {
            ans.push_back(sequence);
            return;
        }
        if (pos == freq.size() || rest < freq[pos].first) {
            return;
        }

        dfs(pos + 1, rest);

        int most = min(rest / freq[pos].first, freq[pos].second);
        for (int i = 1; i <= most; ++i) {
            sequence.push_back(freq[pos].first);
            dfs(pos + 1, rest - i * freq[pos].first);
        }
        for (int i = 1; i <= most; ++i) {
            sequence.pop_back();
        }
    }

    vector<vector<int>> combinationSum2_2(vector<int>& candidates, int target) {
        sort(candidates.begin(), candidates.end());
        for (int num: candidates) {
            if (freq.empty() || num != freq.back().first) {
                freq.emplace_back(num, 1);
            } else {
                ++freq.back().second;
            }
        }
        dfs(0, target);
        return ans;
    }

};
```

### 37. 解数独(困难)

#### [解数独](https://leetcode-cn.com/problems/sudoku-solver/)

#### 方法一：递归

```c++
#include <vector>
#include <string.h>
using namespace std;
class Solution {
private:
    bool line[9][9];
    bool colum[9][9];
    bool block[3][3][9];
    vector<pair<int,int>> spaces;
    bool valid = false;

public:
    void solveSudoku(vector<vector<char>>& board) {
        memset(line, false,sizeof (line));
        memset(colum, false,sizeof(colum));
        memset(block, false, sizeof(block));
        for(int i=0;i<9;++i){
            for(int j=0;j<9;++j){
                if(board[i][j]=='.'){
                    spaces.emplace_back(i,j);
                }else{
                    int num=board[i][j]-'0'-1;
                    line[i][num]= true;
                    colum[j][num]= true;
                    block[i/3][j/3][num]=true;
                }
            }
        }
        backtracking(board,0);
    }
    void backtracking(vector<vector<char>>& board,int pos){
        if(pos== spaces.size()){
            valid= true;
            return;
        }
        auto [i,j]=spaces[pos];
        for(int k=0;k<9&&!valid;++k){
            if(!line[i][k]&&!colum[j][k]&&!block[i/3][j/3][k]){
                line[i][k]=colum[j][k]=block[i/3][j/3][k]= true;
                board[i][j]= k+'0'+1;
                backtracking(board,pos+1);
                line[i][k]=colum[j][k]=block[i/3][j/3][k]= false;
            }
        }
    }
};
```

#### 方法二：位运算优化

使用位运算符将数组压缩成一个数。

具体地，数$b$的二进制表示的第$i$位（从低到高，最低位为第0位）为1,当且仅当数字$i+1$已经出现过。例如当$b$的二进制表示为$(011000100)_2$时，就表示数字$3,7,8$已经出现过。

位运算有一些基础的使用技巧。下面列举了所有在代码中使用到的技巧：

- 对于第 $i$ 行第 $j$列的位置，$line[i]\ column[j] \ block[i/3][j/3]$中第$k$位为$1$，表示该位置不能填入数字$k+1$（因为已经出现过），其中$|$表示按位或运算。如果我们对这个值进行∼按位取反，那么第$k$位为$1$就表示该位置可以填入数字$k+1$，我们就可以通过寻找$1$来进行枚举。由于在进行按位取反运算后，这个数的高位也全部变成了$1$，而这是我们不应当枚举到的，因此我们需要将这个数和$(111111111)_2=(1FF)_{16}$进行按位与运算$\&$，将所有无关的位置为；
- 我们可以使用按位异或运算$\wedge$，将第$i$位从$0$变为$1$，或从$1$变为$0$。具体地，与数$1<<i$进行按位异或运算即可，其中$<<$表示左移运算；
- 我们可以用$b\&(-b)$ 得到$b$二进制表示中最低位的$1$，这是因为$(-b)$在计算机中以补码的形式存储，它等于$∼b+1$。$b$如果和$∼b$进行按位与运算，那么会得到$0$，但是当$∼b$增加$1$之后，最低位的连续的$1$都变为$0$，而最低位的$0$变为$1$，对应到$b$中即为最低位的$1$，因此当$b$和$∼b+1$进行按位与运算时，只有最低位的$1$会被保留；
- 当我们得到这个最低位的$1$时，我们可以通过一些语言自带的函数得到这个最低位的$1$究竟是第几位(即$i$值)，具体可以参考下面的代码；
- 我们可以用$b$和最低位的$1$进行按位异或运算，就可以将其从$b$中去除，这样就可以枚举下一个$1$。同样地，我们也可以用$b$和$b-1$进行按位与运算达到相同的效果。

```c++
class Solution {
private:
    int line[9];
    int column[9];
    int block[3][3];
    bool valid;
    vector<pair<int, int>> spaces;

public:
    void flip(int i, int j, int digit) {
        line[i] ^= (1 << digit);//digit+1被使用过，因此将1左移digit位并与原数异或
        column[j] ^= (1 << digit);
        block[i / 3][j / 3] ^= (1 << digit);
    }

    void dfs(vector<vector<char>>& board, int pos) {
        if (pos == spaces.size()) {
            valid = true;
            return;
        }

        auto [i, j] = spaces[pos];
        int mask = ~(line[i] | column[j] | block[i / 3][j / 3]) & 0x1ff;//mask的bit位表示可填入的数
        for (; mask && !valid; mask &= (mask - 1)) {
            int digitMask = mask & (-mask);//取得位数最小的1的位置，如011010位数最小的1为000010
            int digit = __builtin_ctz(digitMask);//返回digitMask二进制下末尾 0 的个数
            flip(i, j, digit);
            board[i][j] = digit + '0' + 1;
            dfs(board, pos + 1);
            flip(i, j, digit);
        }
    }

    void solveSudoku(vector<vector<char>>& board) {
        memset(line, 0, sizeof(line));
        memset(column, 0, sizeof(column));
        memset(block, 0, sizeof(block));
        valid = false;

        for (int i = 0; i < 9; ++i) {
            for (int j = 0; j < 9; ++j) {
                if (board[i][j] == '.') {
                    spaces.emplace_back(i, j);
                }
                else {
                    int digit = board[i][j] - '0' - 1;
                    flip(i, j, digit);
                }
            }
        }

        dfs(board, 0);
    }
};

```

### 301. 删除无效的括号

#### [删除无效的括号](https://leetcode-cn.com/problems/remove-invalid-parentheses/)

广度优先

```c++
#include <string>
#include <unordered_set>
#include <vector>
using namespace std;
class Solution {
public:
    bool isValid(string s){
        int count=0;
        for(char & c:s){
            if(c=='('){
                ++count;
            } else if(c==')'){
                --count;
                if(count<0){
                    return false;
                }
            }
        }
        return count == 0;
    }
    vector<string> removeInvalidParentheses(string s) {
    vector<string> ans;
    unordered_set<string> curr_set;

    curr_set.insert(s);

    while(true){
        for(auto& p:curr_set){
            if(isValid(p)){
                ans.emplace_back(p);
            }
        }
        if(ans.size()>0){
            return ans;
        }
        unordered_set<string> next_set;
        for(auto& str:curr_set){
            for(int i=0;i<str.size();++i){
                if(i>0&&str[i]==str[i-1]){
                    continue;
                }
                if(str[i]=='('||str[i]==')'){
                    next_set.insert(str.substr(0,i)+str.substr(i+1,str.size()));
                }
            }
        }
        curr_set=next_set;
    }

    }
};
```

