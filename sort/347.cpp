//
// Created by pc on 2022/2/22.
//
#include <vector>
#include <unordered_map>
#include <queue>
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
        priority_queue<pair<int,int>,vector<pair<int,int>>, decltype(&cmp)> q(cmp);//第三个参数传入的是Compare的类型，decltype(&cmp)代表的是cmp的类型，是一个函数指针类型，
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