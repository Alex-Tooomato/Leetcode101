//
// Created by pc on 2022/3/6.
//
#include <string>
#include <vector>
using namespace std;
// Definition for a binary tree node.
 struct TreeNode {
      int val;
      TreeNode *left;
      TreeNode *right;
      TreeNode() : val(0), left(nullptr), right(nullptr) {}
      TreeNode(int x) : val(x), left(nullptr), right(nullptr) {}
      TreeNode(int x, TreeNode *left, TreeNode *right) : val(x), left(left), right(right) {}
  };

class Solution {
public:
    vector<string> binaryTreePaths(TreeNode* root) {
    vector<string> ans;
        backtracking(root,ans,"");
        return ans;
    }
    void backtracking(TreeNode * root,vector<string> &ans,string s){
        if(root!= nullptr){
            s+= to_string(root->val);
            if(root->left== nullptr&&root->right== nullptr){
                ans.push_back(s);
            } else{
                s+="->";
                backtracking(root->left,ans,s);
                backtracking(root->right,ans,s);//用栈实现了回溯
            }

        }

    }
};