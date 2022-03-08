//
// Created by pc on 2022/3/8.
//
#include <string>
#include <unordered_set>
#include <vector>
using namespace std;
class Solution {
public:
    bool isValid(string s){
        int count=0;
        for(char & c:s){
            if(c=='('){
                ++count;
            } else if(c==')'){
                --count;
                if(count<0){
                    return false;
                }
            }
        }
        return count == 0;
    }
    vector<string> removeInvalidParentheses(string s) {
    vector<string> ans;
    unordered_set<string> curr_set;

    curr_set.insert(s);

    while(true){
        for(auto& p:curr_set){
            if(isValid(p)){
                ans.emplace_back(p);
            }
        }
        if(ans.size()>0){
            return ans;
        }
        unordered_set<string> next_set;
        for(auto& str:curr_set){
            for(int i=0;i<str.size();++i){
                if(i>0&&str[i]==str[i-1]){
                    continue;
                }
                if(str[i]=='('||str[i]==')'){
                    next_set.insert(str.substr(0,i)+str.substr(i+1,str.size()));
                }
            }
        }
        curr_set=next_set;
    }

    }
};