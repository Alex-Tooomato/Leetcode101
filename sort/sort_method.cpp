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
void merge_sort(vector<int> &nums,int l,int r,vector<int> &temp){
    if(l+1>=r){//分到还剩2个就不能继续分了
        return;
    }
    //先分开
    int m=l+(r-l)/2;
    merge_sort(nums,l,m,temp);
    merge_sort(nums,m,r,temp);
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

int main()
{
    vector<int> data={1,7,6,4,9,14,19,100,55,10,11};
//    quick_sort(data,0,10);
//    for(auto i:data){
//        cout<<i<<" ";
//    }
    vector<int>temp(11);
    merge_sort(data,0,11,temp);
    for(auto i:data){
        cout<<i<<" ";
    }
    return 0;
}
