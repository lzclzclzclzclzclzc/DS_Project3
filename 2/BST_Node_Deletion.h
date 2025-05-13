#ifndef BSTNODEDELETION_H
#define BSTNODEDELETION_H
#include "Node.h"
#include <iostream>
#include <vector>
#include <chrono>
extern int comparison_count;

// 插入函数（构建 BST）
TreeNode* insert(TreeNode* root, int val, bool use_parent = false) {
    if (!root) return new TreeNode(val);
    if (val < root->val) {
        root->left = insert(root->left, val, use_parent);
        if (use_parent) root->left->parent = root;
    } else {
        root->right = insert(root->right, val, use_parent);
        if (use_parent) root->right->parent = root;
    }
    return root;
}

// 1. 标准递归删除
TreeNode* deleteRecursive(TreeNode* root, int key) {
    if (!root) return nullptr;
    comparison_count++;
    if (key < root->val) root->left = deleteRecursive(root->left, key);
    else if (key > root->val) root->right = deleteRecursive(root->right, key);
    else {
        if (!root->left) return root->right;
        if (!root->right) return root->left;
        TreeNode* minNode = root->right;
        while (minNode->left) {
            minNode = minNode->left;
            comparison_count++;
        }
        root->val = minNode->val;
        root->right = deleteRecursive(root->right, minNode->val);
    }
    return root;
}

// 2. 非递归删除
TreeNode* deleteIterative(TreeNode* root, int key) {
    TreeNode* parent = nullptr, *cur = root;
    while (cur && cur->val != key) {
        comparison_count++;
        parent = cur;
        cur = (key < cur->val) ? cur->left : cur->right;
    }
    if (!cur) return root;

    TreeNode* replacement = nullptr;
    if (!cur->left || !cur->right) {
        replacement = cur->left ? cur->left : cur->right;
    } else {
        TreeNode* succParent = cur, *succ = cur->right;
        while (succ->left) {
            comparison_count++;
            succParent = succ;
            succ = succ->left;
        }
        cur->val = succ->val;
        cur = succ;
        parent = succParent;
        replacement = cur->right;
    }

    if (!parent) return replacement;
    if (parent->left == cur) parent->left = replacement;
    else parent->right = replacement;

    return root;
}

// 3. Hibbard 删除（左子树最大）
TreeNode* deleteHibbard(TreeNode* root, int key) {
    if (!root) return nullptr;
    comparison_count++;
    if (key < root->val) root->left = deleteHibbard(root->left, key);
    else if (key > root->val) root->right = deleteHibbard(root->right, key);
    else {
        if (!root->left) return root->right;
        if (!root->right) return root->left;
        TreeNode* maxNode = root->left;
        while (maxNode->right) {
            maxNode = maxNode->right;
            comparison_count++;
        }
        root->val = maxNode->val;
        root->left = deleteHibbard(root->left, maxNode->val);
    }
    return root;
}

// 4. 父指针优化删除
TreeNode* deleteWithParent(TreeNode* root, TreeNode* node) {
    if (!node) return root;
    comparison_count++;
    if (!node->left || !node->right) {
        TreeNode* child = node->left ? node->left : node->right;
        if (node->parent) {
            if (node->parent->left == node)
                node->parent->left = child;
            else
                node->parent->right = child;
        } else {
            root = child;
        }
        if (child) child->parent = node->parent;
    } else {
        TreeNode* succ = node->right;
        while (succ->left) {
            succ = succ->left;
            comparison_count++;
        }
        node->val = succ->val;
        root = deleteWithParent(root, succ);
    }
    return root;
}

TreeNode* find(TreeNode* root, int val) {
    while (root && root->val != val) {
        comparison_count++;
        root = (val < root->val) ? root->left : root->right;
    }
    return root;
}

#endif