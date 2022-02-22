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
    int findKthLargest(vector<int>& nums, int k) {
    int l=0,r=nums.size()-1,target=nums.size()-k;
    while(l<r){
        int mid=quickSelection(nums,l,r);
        if(mid==target){
            return nums[target];
        }
        if(mid<target){
            l=mid+1;
        } else{
            r=mid-1;
        }
    }
        return nums[l];
    }
    int quickSelection(vector<int> &nums,int l,int r){//返回的位置左边比该位置的值小，右边比该位置的值大，因此此位置为排完序后所在的位置。
        int i=l+1,j=r;
        while(true){
            while(i<r&&nums[i]<=nums[l]){
                ++i;
            }
            while(l<j&&nums[j]>=nums[l]){//退出循环时nums[j]<nums[l]
                --j;
            }
            if(i>=j){
                break;
            }
            swap(nums[i],nums[j]);
        }
        swap(nums[l],nums[j]);
        return j;
    }
};
```
