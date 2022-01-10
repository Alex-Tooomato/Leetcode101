//
// Created by pc on 2022/1/10.
//

#include <vector>
#include <algorithm>
using namespace std;
class Solution {
public:
    int findMinArrowShots(vector<vector<int>>& points) {
        if(points.empty()){
            return 0;
        }
        sort(points.begin(),points.end(),[](vector<int>a,vector<int>b){return a[1]<b[1];});
        int total =1,prev=points[0][1];
        for(const vector<int>& balloon: points){
            if(balloon[0]>prev){
                total++;
                prev=balloon[1];
            }
        }
        return total;
    }
};