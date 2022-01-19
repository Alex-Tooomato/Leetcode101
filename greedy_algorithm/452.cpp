//
<<<<<<< HEAD
// Created by pc on 2022/1/10.
//

=======
// Created by skyyw on 2022/1/19.
//
>>>>>>> main
#include <vector>
#include <algorithm>
using namespace std;
class Solution {
public:
    int findMinArrowShots(vector<vector<int>>& points) {
<<<<<<< HEAD
        if(points.empty()){
            return 0;
        }
        sort(points.begin(),points.end(),[](vector<int>a,vector<int>b){return a[1]<b[1];});
        int total =1,prev=points[0][1];
        for(const vector<int>& balloon: points){
            if(balloon[0]>prev){
                total++;
                prev=balloon[1];
=======
        if(points.empty())
            return 0;
        sort(points.begin(), points.end(),[](vector<int>a,vector<int>b) {return a[1]<b[1];});
        int total=1,prev=points[0][1];
        for(const vector<int>& ballon :points){//按引用以减少按值复制的时空消耗
            if(ballon[0]>prev){
                total++;
                prev=ballon[1];
>>>>>>> main
            }
        }
        return total;
    }
<<<<<<< HEAD
};
=======
};
>>>>>>> main
