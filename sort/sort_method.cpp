//
// Created by pc on 2022/2/19.
//
#include <vector>
#include <iostream>
using namespace std;
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
void merge_sort2(vector<int> &nums,int l,int r,vector<int> &temp){
    if(l>=r){//分到还剩2个就不能继续分了
        return;
    }
    //先分开
    int m=l+(r-l)/2;
    merge_sort2(nums,l,m,temp);
    merge_sort2(nums,m,r,temp);
    //合并
    int i=l,j=m,k=l;
    while(i<m||j<r){
        if(j>=r||(i<m&&nums[i]<=nums[j])){
            temp[k++]=nums[i++];
        }else{
            temp[k++]=nums[j++];
        }
    }
    for(k=l;k<r;++k){
        nums[k]=temp[k];
    }
}
void merge(vector<int>&data, int start, int mid, int end, vector<int>&result)
{
    int i, j, k;
    i = start;
    j = mid + 1;                        //避免重复比较data[mid]
    k = 0;
    while (i <= mid && j <= end)        //数组data[start,mid]与数组(mid,end]均没有全部归入数组result中去
    {
        if (data[i] <= data[j])         //如果data[i]小于等于data[j]
            result[k++] = data[i++];    //则将data[i]的值赋给result[k]，之后i,k各加一，表示后移一位
        else
            result[k++] = data[j++];    //否则，将data[j]的值赋给result[k]，j,k各加一
    }
    while (i <= mid)                    //表示数组data(mid,end]已经全部归入result数组中去了，而数组data[start,mid]还有剩余
        result[k++] = data[i++];        //将数组data[start,mid]剩下的值，逐一归入数组result
    while (j <= end)                    //表示数组data[start,mid]已经全部归入到result数组中去了，而数组(mid,high]还有剩余
        result[k++] = data[j++];        //将数组a[mid,high]剩下的值，逐一归入数组result

    for (i = 0; i < k; i++)             //将归并后的数组的值逐一赋给数组data[start,end]
        data[start + i] = result[i];    //注意，应从data[start+i]开始赋值
}
void merge_sort(vector<int>&data, int start, int end, vector<int>&result)
{
    if (start < end)
    {
        int mid = start + (end-start) / 2;//避免溢出int
        merge_sort(data, start, mid, result);                    //对左边进行排序
        merge_sort(data, mid + 1, end, result);                  //对右边进行排序
        merge(data, start, mid, end, result);                    //把排序好的数据合并
    }
}

int main()
{
    vector<int> data={1,7,6,4,9,14,19,100,55,10,11};
//    quick_sort(data,0,10);
//    for(auto i:data){
//        cout<<i<<" ";
//    }
    vector<int>temp(11);
    merge_sort(data,0,10,temp);
    for(auto i:data){
        cout<<i<<" ";
    }
    return 0;
}
