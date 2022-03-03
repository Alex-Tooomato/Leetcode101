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

};

