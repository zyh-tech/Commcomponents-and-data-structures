
#include<bits/stdc++.h>
using namespace std;
//染色法迭代遍历
//一种方法解决三种遍历

struct TreeNode{
    int val;
    TreeNode* left;
    TreeNode* right;
    TreeNode(int _val):val(_val),left(nullptr),right(nullptr){}
};

vector<int> orderTraversal(TreeNode* root){
    vector<int> res;
    stack<pair<TreeNode*,int>> st;
    st.push({root,0});

    while(!st.empty()){
        auto [node,color] = st.top();
        st.pop();
        if(node == nullptr) continue;
        if(color == 0){
            //压栈顺序和遍历顺序相反，子结点颜色是0，自身是1
            st.push({node->right,0});
            st.push({node,1});
            st.push({node->left,0});
        }else{
            res.emplace_back(node->val);
        }
    }
    return res;
}