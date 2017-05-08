#ifndef TREENODE_H
#define TREENODE_H

#include <iostream>
#include <vector>
#include <string>
#include <queue>
#include <limits>
#include <list>
#include <algorithm>
#include <iomanip>
#include <cmath>
#include "mydb.h"
// // // // // // // // // // // // // // // // // // // // // // 

using namespace std;

const int kNULL = 0xa3a3a3a3;

struct TreeNode {
	int val;
	TreeNode* left;
	TreeNode* right;
	TreeNode(int x);
};

// Print a Queue
template<class T>
void print(queue<T> q);

// Print a Tree
void print(TreeNode* root);



/* 
Builds a tree -- heap style -- where constant kNULL represent no child.
Approach: Keep a queue of the leaf nodes. 
Syntax: 
buildTree( {1, 0, 3, kNULL, 4, 3, kNULL, 7 } )

*/
TreeNode* buildTree(vector<int>& a, bool debug = false);

// Build a binary search tree
TreeNode* buildBST(vector<int> a, bool balance = false);



//Print nodes at each level
void listerize(TreeNode* root);


#endif










































