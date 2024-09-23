
using namespace std;

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
    bool isValidBST(TreeNode* root) {
        return isValidBSTLimits(root, nullptr, nullptr);
    }
    bool isValidBSTLimits(TreeNode* root, int *max, int *min)
    {
        if ((max && root->val >= *max) || (min && root->val <= *min))
            return false;
        if (root->left && ! isValidBSTLimits(root->left, &root->val, min))
            return false;
        if (root->right && ! isValidBSTLimits(root->right, max, &root->val))
            return false;
        return true;
    }
};