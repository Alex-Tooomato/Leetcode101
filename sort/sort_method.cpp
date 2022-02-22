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

void insertion_sort(vector<int> &nums,int n){
    for(int i=0;i<n;++i){
        for(int j=i;j>0&&nums[j]<nums[j-1];--j){
            swap(nums[j],nums[j-1]);
        }
    }
}
void bubble_sort(vector<int> &nums,int n){
    bool swapped;
    for(int i=1;i<n;++i){
        swapped= false;
        for(int j=1;j<n-i+1;++j){
            if(nums[j]<nums[j-1]){
                swap(nums[j],nums[j-1]);
                swapped= true;
            }
        }
        if(!swapped){
            break;//如果某一轮没发生过交换，则说明顺序已经排好了
        }
    }
}
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
int main()
{
    vector<int> data={1,7,6,4,9,14,19,100,55,10,11};
//    quick_sort(data,0,10);
//    for(auto i:data){
//        cout<<i<<" ";
//    }
    vector<int>temp(11);
    for(auto i:data){
        cout<<i<<" ";
    }
    cout<<endl;
    selection_sort(data,data.size());
    for(auto i:data){
        cout<<i<<" ";
    }
    return 0;
}
