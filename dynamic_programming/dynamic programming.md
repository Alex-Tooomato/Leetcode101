# 深入浅出动态规划

## 基本动态规划：一维

### 70. 爬楼梯

#### [爬楼梯](https://leetcode-cn.com/problems/climbing-stairs/)

```c++
//状态转移方程
class Solution {
public:
    int climbStairs(int n) {
    if(n<=2){
        return n;
    }
    vector<int> dp(n+1,1);
    
    for(int i=2;i<n+1;++i){
        dp[i]=dp[i-1]+dp[i-2];
    }
        return dp[n];
    }
};
//节省空间
class Solution {
public:
    int climbStairs(int n) {
        if (n <= 2) {
            return n;
        }
        int pre1=1,pre2=2;
        int cur;
        for(int i=2;i<n;++i){
            cur=pre1+pre2;
            pre1=pre2;
            pre2=cur;
        }
        return cur;
    }
};
```

### 198. 打家劫舍

#### [打家劫舍](https://leetcode-cn.com/problems/house-robber/)

```c++
//状态转移方程
class Solution {
public:
    int rob(vector<int>& nums) {
        if(nums.empty()) return 0;
        int n=nums.size();
    vector<int> dp(n+1,0);
            dp[1]=nums[0];
    for(int i=2;i<n+1;++i){
        dp[i]=max(dp[i-2]+nums[i-1],dp[i-1]);
    }
        return dp[n];
    }
};
//节省空间
class Solution {
public:
    int rob(vector<int>& nums) {
        if(nums.empty()) return 0;
        int n=nums.size();
        if(n==1) return nums[0];
        int pre0=0,pre1=nums[0];
        int cur;
    for(int i=2;i<n+1;++i){
       cur=max(pre1,pre0+nums[i-1]);
       pre0=pre1;
       pre1=cur;  
    }
        return cur;
    }
};
```

### 413. 等差数列划分

#### [等差数列划分](https://leetcode-cn.com/problems/arithmetic-slices/)

```c++
class Solution {
public:
    int numberOfArithmeticSlices(vector<int>& nums) {
    int n=nums.size();
    if(n<3) return 0;
    vector<int> dp(n,0);
    for(int i=2;i<n;++i){
        if(nums[i]-nums[i-1]==nums[i-1]-nums[i-2]){
            dp[i]=dp[i-1]+1;//dp[i]:以nums[i]结尾的等差数列的数量
        }
    }
    return accumulate(dp.begin(),dp.end(),0);
    }
};
```

## 基本动态规划：二维

### 64. 最小路径和

#### [最小路径和](https://leetcode-cn.com/problems/minimum-path-sum/)

```c++
#include <vector>
using namespace std;
class Solution {
public:
    int minPathSum(vector<vector<int>>& grid) {
    int m=grid.size(),n=grid[0].size();
    vector<int> dp(n,0);
    for(int i=0;i<m;++i){
        for(int j=0;j<n;++j){
            if(i==0&&j==0){
                dp[j]=grid[i][j];
            } else if(i==0){
                dp[j]=dp[j-1]+grid[i][j];
            } else if(j==0){
                dp[j]=dp[j]+grid[i][j];
            } else{
                dp[j]=min(dp[j],dp[j-1])+grid[i][j];
            }
        }
    }
        return dp[n-1];
    }
};
```

### 542. 01矩阵

#### [01 矩阵](https://leetcode-cn.com/problems/01-matrix/)

用两次动态搜索（一次从左上到右下，一次从右下到左上），实现四个方向的搜索

```c++
#include <vector>
#include <limits.h>
#include <iostream>
using namespace std;
class Solution {
public:
    vector<vector<int>> updateMatrix(vector<vector<int>>& mat) {
        if(mat.empty())return {};
        int m=mat.size(),n=mat[0].size();
        vector<vector<int>> dp(m,vector<int>(n,INT_MAX-1));
        for(int i=0;i<m;++i){
            for(int j=0;j<n;++j) {
                if (mat[i][j] == 0) {
                    dp[i][j] = 0;
                } else {
                    if (j > 0) {
                        dp[i][j] = min(dp[i][j], dp[i][j - 1] + 1);
                    }
                    if (i > 0) {
                        dp[i][j] = min(dp[i][j], dp[i - 1][j] + 1);
                    }
                }
            }
        }
        for(int i=m-1;i>=0;--i){
            for(int j=n-1;j>=0;--j){
                if(mat[i][j]!=0){
                    if(j<n-1){
                        dp[i][j] = min(dp[i][j], dp[i][j + 1] + 1);
                    }
                    if(i<m-1){
                        dp[i][j] = min(dp[i][j], dp[i + 1][j] + 1);
                    }
                }
            }
        }
        return dp;
    }
};
```

### 221. 最大正方形

#### [最大正方形](https://leetcode-cn.com/problems/maximal-square/)

```c++
#include <vector>
using namespace std;
class Solution {
public:
    int maximalSquare(vector<vector<char>>& matrix) {
        if(matrix.empty()||matrix[0].empty()) return 0;
        int m=matrix.size(),n= matrix[0].size();
        int max_side=0;
        vector<vector<int>> dp(m,vector<int>(n,0));
        for(int i=0;i<m;++i){
            for(int j=0;j<n;++j){
               if(matrix[i][j]=='1'){
                   if(i==0||j==0){
                       dp[i][j]=1;
                   }else{
                       dp[i][j] = min(min(dp[i - 1][j], dp[i][j - 1]), dp[i - 1][j - 1]) + 1;
                   }
                   max_side=max(max_side,dp[i][j]);
               }
            }
        }
        return max_side* max_side;
    }
};
```

## 分割类型题

### 279. 完全平方数

#### [完全平方数](https://leetcode-cn.com/problems/perfect-squares/)

```c++
#include <vector>
#include <limits.h>
using namespace std;
class Solution {
public:
    int numSquares(int n) {
    vector<int> dp(n+1,INT_MAX);
    dp[0]=0;
    for(int i=1; i<=n ; ++i) {
        for(int j=1;j*j<=i;++j){
            dp[i]=min(dp[i],dp[i-j*j]+1);
        }
    }
        return dp[n];
    }
};
```

### 91. 解码方法

#### [解码方法](https://leetcode-cn.com/problems/decode-ways/)

```c++
#include <iostream>
#include <vector>
using namespace std;
class Solution {
public:
    int numDecodings(string s) {
        int n=s.size();
        if(n==0)return 0;
        int prev=s[0]-'0';
        if(prev==0)return 0;
        if(n==1)return 1;
        vector<int> dp(n+1,1);
        for(int i=2;i<=n;++i){
            int cur=s[i-1]-'0';
            if((prev==0||prev>2)&&cur==0){//出现30或者00这种情况，无法解码
                return 0;
            }
            if((prev==1)||(prev==2&&cur<7)){
                if(cur){//当前字母可以和前面的字母组合，且不为0
                    dp[i]=dp[i-2]+dp[i-1];
                }else{//如果是10或20，此时只能视作一个字母且不能和10/20 前的字母组合
                    dp[i]=dp[i-2];
                }
            }else{//不能和前一个字母组合
                dp[i]=dp[i-1];
            }
            prev=cur;
        }
        return dp[n];
    }
};

//官方
class Solution {
public:
    int numDecodings(string s) {
        int n = s.size();
        vector<int> f(n + 1);
        f[0] = 1;
        for (int i = 1; i <= n; ++i) {
            if (s[i - 1] != '0') {
                f[i] += f[i - 1];//单字符处理
            }
            if (i > 1 && s[i - 2] != '0' && ((s[i - 2] - '0') * 10 + (s[i - 1] - '0') <= 26)) {
                f[i] += f[i - 2];//双字符处理
            }//若无法处理则当前为0,且	之后都为0,因为f[i] += f[i - 2]需要保证s[i-2]!=0
        }
        return f[n];
    }
};

```

### 139. 单词拆分

#### [单词拆分](https://leetcode-cn.com/problems/word-break/)

```c++
#include <iostream>
#include <vector>
using namespace std;
class Solution {
public:
    bool wordBreak(string s, vector<string>& wordDict) {
        int n=s.length();
    vector<bool> dp(n+1, false);
    dp[0]= true;
    for(int i=1;i<=n;++i){
        for(const string& word:wordDict){
            int len=word.length();
            if(i>=len&&s.substr(i-len,len)==word){
                dp[i]=dp[i]||dp[i-len];
            }
        }
    }
        return dp[n];
    }
};

```

