// Node.h
#ifndef __NODE_H__
#define __NODE_H__

#include <iostream>
#include <vector>


struct TreeNode {
    int val;
    TreeNode *left, *right, *parent; 
    TreeNode(int v) : val(v), left(nullptr), right(nullptr), parent(nullptr) {}
};


#endif