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
    unordered_map<string,int> steps={{beginWord,0}};
    unordered_map<string,string> from={{beginWord,{}}};
    unordered_set<string> dict={wordList.begin(),wordList.end()};

    }

};

