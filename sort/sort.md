# 第5章 千奇百怪的排序算法

## 1. 常用排序算法

### 快速排序（Quick Sort）

左闭有闭的二分写法

将大于某个分界值(一般取第一个数)的放在右边，小于的放在左边，然后递归

```c++
void quick_sort(vector<int> &nums,int l,int r){
    if(l>=r){
        return;
    }
    int first=l,last=r,key=nums[first];
    while(first<last){
        while(first<last&&nums[last]>=key){
            --last;
        }
        nums[first]=nums[last];
        while(first<last&&nums[first]<=key){
            ++first;
        }
        nums[last]=nums[first];
    }
    nums[first]=key;
    quick_sort(nums,l,first-1);
    quick_sort(nums,first+1,r);
}
```

### 归并排序（Merge Sort）

```c++
void merge_sort(vector<int> &nums,int l,int r,vector<int> &temp){
    if(l>=r){//分到还剩2个就不能继续分了
        return;
    }
    //先分开
    int m=l+(r-l)/2;
    merge_sort(nums,l,m,temp);
    merge_sort(nums,m+1,r,temp);
    //合并
    int i=l,j=m+1,k=l;
    while (i <= m && j <= r)        //数组data[start,mid]与数组(mid,end]均没有全部归入数组result中去
    {
        if (nums[i] <= nums[j])         //如果data[i]小于等于data[j]
            temp[k++] = nums[i++];    //则将data[i]的值赋给result[k]，之后i,k各加一，表示后移一位
        else
            temp[k++] = nums[j++];    //否则，将data[j]的值赋给result[k]，j,k各加一
    }
    while (i <= m)                    //表示数组data(mid,end]已经全部归入result数组中去了，而数组data[start,mid]还有剩余
        temp[k++] = nums[i++];        //将数组data[start,mid]剩下的值，逐一归入数组result
    while (j <= r)                    //表示数组data[start,mid]已经全部归入到result数组中去了，而数组(mid,high]还有剩余
        temp[k++] = nums[j++];//将数组a[mid,high]剩下的值，逐一归入数组result

        for(i=l;i<(r+1);++i){
        nums[i]=temp[i];
    }
}
void merge_sort2(vector<int> &nums,int l,int r,vector<int> &temp){
    if(l+1>=r){
        return;
    }
    int m=l+(r-l)/2;
    merge_sort2(nums,1,m,temp);
    merge_sort2(nums,m,r,temp);
    int p=l,q=m,i=l;
    while(p<m||q<r){
        if(q>=r||(p<m&&nums[p]<=nums[q])){
            temp[i++]=nums[p++];
        }else{
            temp[i++]=nums[q++];
        }
    }
    for(i=l;i<r;++i){
        nums[i]=temp[i];
    }
}
```

### 插入排序（Insertion Sort）

```c++
void insert_sort(vector<int> &nums,int n){
    for(int i=0;i<n;++i){
        for(int j=i;j>0&&nums[j]>nums[j-1];--j){
            swap(nums[j],nums[j-1]);
        }
    }
}
```

### 冒泡排序（Bubble Sort）

```c++
void selection_sort(vector<int> &nums,int n){
    int mid;
    for(int i=0;i<n-1;++i){
        mid=i;
        for(int j=i+1;j<n;++j){
            if(nums[j]<nums[mid]){
                mid=j;
            }
        }
        swap(nums[mid],nums[i]);
    }
}
```

## 2. 快速选择

#### [数组中的第K个最大元素](https://leetcode-cn.com/problems/kth-largest-element-in-an-array/)

寻找排完序的倒数第k个元素

```c++
#include <vector>
using namespace std;
class Solution {
public:
        //桶排序
    vector<int> topKFrequent(vector<int>& nums, int k){
        unordered_map<int,int>counts;
        int max_count=0;
        for(auto & num:nums){
            max_count=max(max_count,++counts[num]);
        }
        vector<vector<int>>buckets(max_count+1);
        for(auto& p:counts){
            buckets[p.second].push_back(p.first);
        }
        vector<int> ans;
        for(int i=max_count;i>=0&&ans.size()<k;--i){
            for(auto & n:buckets[i]){
                ans.push_back(n);
                if(ans.size()==k){
                    break;
                }
            }
        }
        return ans;
    }
    //快速选择
    void qsort(vector<pair<int, int>>& v, int start, int end, vector<int>& ret, int k) {
        int picked = rand() % (end - start + 1) + start;
        swap(v[picked], v[start]);

        int pivot = v[start].second;
        int index = start;
        for (int i = start + 1; i <= end; i++) {
            if (v[i].second >= pivot) {
                swap(v[index + 1], v[i]);
                index++;
            }
        }
        swap(v[start], v[index]);

        if (k <= index - start) {
            qsort(v, start, index - 1, ret, k);
        } else {
            for (int i = start; i <= index; i++) {
                ret.push_back(v[i].first);
            }
            if (k > index - start + 1) {
                qsort(v, index + 1, end, ret, k - (index - start + 1));
            }
        }
    }

    vector<int> topKFrequent1(vector<int>& nums, int k){
        unordered_map<int,int> occurences;
        for(auto&v:nums) {
            ++occurences[v];
        }
        vector<pair<int,int>> values;
        for(auto&kv:occurences){
            values.push_back(kv);
        }
        vector<int>ret;
        qsort(values,0,values.size()-1,ret,k);
        return ret;
    }
    //最小堆
    static bool cmp(pair<int,int>&x,pair<int,int>&y){
        return x.second>y.second;
    }
    vector<int> topKFrequent2(vector<int>& nums, int k) {
        unordered_map<int,int> occurences;
        for(auto&v:nums) {
            ++occurences[v];
        }
        priority_queue<pair<int,int>,vector<pair<int,int>>, decltype(&cmp)> q(cmp);//第三个		参数传入的是Compare的类型，decltype(&cmp)代表的是cmp的类型，是一个函数指针类型，
        // 如果使用不带参数的构造函数，则用来比较的实际函数将不明，会是一个野指针，能通过编译，但运行看天意。
        for(auto&[num,count]:occurences){
            if(q.size()==k){
                if(count>q.top().second){
                    q.pop();
                    q.emplace(num,count);
                }
            }else{
                q.emplace(num,count);
            }
        }
        vector<int> ret;
        while(!q.empty()){
            ret.emplace_back(q.top().first);
            q.pop();
        }
        return ret;
    }
};
```

## 3. 练习

### 451. 根据字符出现频率排序（中等）

#### [根据字符出现频率排序](https://leetcode-cn.com/problems/sort-characters-by-frequency/)

```c++
#include <iostream>
#include <unordered_map>
#include <vector>
using namespace std;

class Solution {
public:
    string frequencySort(string s) {
        unordered_map<char,int> counts;
        int max_count=0;
        for(auto & num:s){
            max_count=max(max_count,++counts[num]);
        }
        vector<vector<int>> buckets(max_count+1);
        for(auto & p:counts){
            buckets[p.second].push_back(p.first);
        }
        string ans;
        for(int i=max_count;i>0;--i){
                for(auto & num:buckets[i]){
                    for(int j=i;j>0;--j){
                        ans.push_back(num);
                    }
            }
        }
        return ans;
    }
};
```

## 75. 颜色分类（中等）

#### [颜色分类](https://leetcode-cn.com/problems/sort-colors/)

```c++
#include <vector>
using namespace std;
class Solution {
public:
    //单指针
    void sortColors(vector<int>& nums) {
        int n=nums.size();
        int ptr=0;
        for(int i=0;i<n;++i){
            if(nums[i]==0){
                swap(nums[ptr],nums[i]);
                ++ptr;
            }
        }
        for(int i=ptr;i<n;++i){
            if(nums[i]==1){
                swap(nums[ptr],nums[i]);
                ++ptr;
            }
        }

    }
    //双指针
    void sortColors2(vector<int>& nums) {
        int n=nums.size();
        int p0=0;
        int p1=0;
        for (int i=0;i<n;++i){
            if(nums[i]==1){
                swap(nums[p1],nums[i]);
                ++p1;
            }else  if(nums[i]==0){
                swap(nums[p0],nums[i]);
                if(p0<p1){
                    swap(nums[i],nums[p1]);
                }
                ++p0;
                ++p1;
            }
        }
    }
};
```
