//
// Created by pc on 2022/3/3.
//

#include <iostream>
#include <string>
#include <vector>
#include <set>
#include <unordered_set>
#include <unordered_map>
#include <queue>


using namespace std;

class Solution {
public:
    //官方
    vector<vector<string>> findLadders(string beginWord, string endWord, vector<string> &wordList) {
        vector<vector<string>> res;
        unordered_set<string> dict={wordList.begin(),wordList.end()};
        if(dict.find(endWord)==dict.end()){return res;}
        dict.erase(beginWord);
        unordered_map<string,int> steps={{beginWord,0}};
        unordered_map<string,set<string>> from={{beginWord,{}}};
        int step=0;
        bool found= false;
        queue<string> q;
        q.push(beginWord);
        int wordLen=beginWord.length();
        while(!q.empty()){
            ++step;
            int size=q.size();
            while(size--){
                const string currword=move(q.front());
                string nextword=currword;
                q.pop();
                for(int j=0;j<wordLen;++j){
                    const char origin =nextword[j];
                    for(char c='a';c<='z';++c){
                        nextword[j]=c;
                        if(steps[nextword]==step){
                            from[nextword].insert(currword);
                        }
                        if(dict.find(nextword)==dict.end()){
                            continue;
                        }
                        dict.erase(nextword);
                        q.push(nextword);
                        from[nextword].insert(currword);
                        steps[nextword]=step;
                        if(nextword==endWord){
                            found= true;
                        }
                    }
                    nextword[j]=origin;
                }
            }
            if(found){
                break;//此时保证层数最少
            }
        }
        if(found){
            vector<string> path={endWord};
            dfs(res,endWord,from,path);
        }
        return res;
    }
    void dfs(vector<vector<string>> &res, const string endWord,unordered_map<string,set<string>>&from,vector<string>& path) {
        if(from[endWord].empty()){
            res.push_back({path.rbegin(),path.rend()});
            return;
        }
        for(auto & Parent:from[endWord]){
            path.push_back(Parent);
            dfs(res,Parent,from,path);
            path.pop_back();
        }
    }
    //leetcode101
    vector<vector<string>> findLadders2(string beginWord, string endWord, vector<string> &wordList){
        vector<vector<string>> ans;
        unordered_set<string> dict;
        for(auto & c:wordList){
            dict.insert(c);
        }
        if(dict.find(endWord)==dict.end()){
            return ans;
        }
        dict.erase(beginWord);
        dict.erase(endWord);
        unordered_set<string> q1{beginWord},q2{endWord};
        unordered_map<string,vector<string>> next;
        bool reversed= false,found= false;
        while(!q1.empty()){
            unordered_set<string> q;//存储的是下一级可能包含的word
            for(const auto&w:q1){
                string s=w;
                for(size_t i=0;i<s.size();++i){
                    char ch=s[i];
                    for(char c='a';c<='z';++c){
                        s[i]=c;
                        if(q2.count(s)){
                            reversed?next[s].push_back(w):next[w].push_back(s);//如果是正向，则w后跟着s，反向则s后跟着w（也就是w靠近endWord）,在图中s是w的前方
                            found= true;
                        }
                        if(dict.count(s)){
                            reversed?next[s].push_back(w):next[w].push_back(s);
                            q.insert(s);
                        }
                    }
                    s[i]=ch;//恢复
                }
            }//此时q1(也就是正向的set)遍历完
            if(found){
                break;
            }
            for(const auto&w:q){
                dict.erase(w);
            }
            if(q.size()<=q2.size()){
                q1=q;
            }else{
                reversed=!reversed;
                q1=q2;
                q2=q;
            }//如果q的大小比q2小，也就是下一级合适的点比相反方向小，则继续进行正向的遍历，反之则进行逆向
        }
        if(found){
            vector<string> path={beginWord};
            backtracking(next,path,beginWord,endWord,ans);
        }
        return ans;
    }
    void backtracking(unordered_map<string,vector<string>> &next,vector<string> &path ,const string &beginWord,const string &endWord,vector<vector<string>> &ans){
        if(beginWord==endWord){
            ans.push_back(path);
        }
        for(const auto&s:next[beginWord]){
            path.push_back(s);
            backtracking(next,path,s, endWord,ans);
            path.pop_back();
        }
    }

};

