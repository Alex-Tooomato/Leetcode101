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

```

```

