
#include "TreeNode.h"

using namespace std;


TreeNode::TreeNode(int x): val(x), left(NULL), right(NULL) {}

// Print a Queue (for debugging purposes).
template<class T>
void print(queue<T> q) {
	while (!q.empty()) {
		if (q.front())
			cout << q.front()->val << endl;
		else 
			cout << "NULL" << endl;
		q.pop();
	}
}

// Print a Tree
void print(TreeNode* root) {
	if (!root) return;
	print(root->left);		
	cout << root->val << " " ;
	print(root->right);
}



// 	Check two trees for equality
bool isEqual( TreeNode* a, TreeNode* b ) {
	if (!a != !b) return false; // one is null and the other is not
	if (!a && !b) return true; // both are null
	if (a->val != b->val) return false;
	return isEqual(a->left, b->left) && isEqual( a->right, b->right );
}


/* 
Build a tree -- heap style -- but NULL represent no child.

Approach: Keep a queue of the leaf nodes that we can attach
new child nodes to.

Syntax: 
buildTree( {1, 0, 3, NULL, 4, 3, NULL, 7 } )
Issues: 
1.) How to identify NULL in vector<int>?
*/
TreeNode* buildTree(vector<int>& a, bool debug) {

	// ensure a[0] is a legitimate root node
	if (a.size() == 0 || a[0] == kNULL) return NULL;

	TreeNode* root = new TreeNode( a[0] );
	TreeNode* x;
	bool childSet = false;
	queue<TreeNode*> q;

	q.push( root );

	if (debug) { printf("********\n"); print(q); }

	for (int i = 1; i < a.size(); i++) {
		
		// if a[i] is a legimate node, we creat it, otherwise a[i] is NULL
		TreeNode* temp = (a[i] == kNULL ? NULL: new TreeNode( a[i] ) );

		// Next, we need to find the legitimate nodes 
		// in the queue that we can add children to.
		
		while (!q.empty() && q.front() == NULL) {
			if (debug)
				cout << "Encountered kNULL" << endl;
			q.pop();
		}

		// Returning here occurs when the topology of the 
		// binary tree that is implicity specified in the input
		// contradicts itself by having more non-kNULL elements
		// to add, but all leaf nodes have been attached to kNULL.
		if (q.empty()) { 
			cout << "Topology of tree is inconsistent." << endl;
			return root;
		}

		x = q.front();

		// add children
		if (!childSet) {
			if (debug) cout << "Attaching " << (temp == NULL?-2:temp->val) << " to " <<  x->val << endl;
			x->left = temp;			
			q.push(x->left);
			childSet = true;
		} else if (childSet) {
			if (debug) cout << "Attaching " << (temp == NULL?-2:temp->val) << " to " <<  x->val << endl;
			x->right = temp;				
			q.pop();
			q.push(x->right);
			childSet = false;
		}
		
		if (debug) { printf("********\n"); print(q); }
	}

	if (debug) printf("********\n");

	return root;
}



// Print nodes at each level
void listerize(TreeNode* root) {
	list< list<TreeNode*> > levels;
	list<TreeNode*> l;
	l.push_back( root );
	levels.push_back( l );

	int iter = 0;
	while(iter++ < 4) {
		list<TreeNode*> x = levels.back();
		list<TreeNode*> n;
		for (TreeNode* t : x) {			
			if (t) {
				n.push_back(t->left);
				n.push_back(t->right);
			} else {
				n.push_back(NULL);
				n.push_back(NULL);
			}
		}

		// Check if list<TreeNode*> n has any elements
		// that actually point to a TreeNode object, and
		// if so, keep going.
		if ( !all_of(n.begin(), n.end(), [](TreeNode* t){ return t == NULL;} ) )
			levels.push_back(n);
		else
			break;
	}

	int level = 0;
	for (auto l:levels) {
		if (level > 20) break;

		for (auto t:l) {
			if (t)
				cout << setw( pow(2,levels.size() - level -1 ) ) << t -> val << setw( pow(2,levels.size() - level -1 ) ) << " ";
			else 
				cout << setw( pow(2,levels.size() - level -1 ) ) << "." << setw( pow(2,levels.size() - level -1 ) ) << " ";

		}
		cout << endl;
		level++;
	}
	
}


// Recursive function to build BST
void insertNode(TreeNode* root, int x) {
	if (x < root->val)
		if (root->left) insertNode(root->left, x);
		else root->left = new TreeNode(x);

	else 
		if (root->right) insertNode(root->right, x);
		else root->right = new TreeNode(x);
}


// For pre-processing input to buildBST so that we can have a balanced tree
void sortedToBalanced( vector<int>& a, vector<int>& b, int i, int j) {

	if (i >= j) return;	
	int m = (i + j) / 2;
	b.push_back(a[m]);
	sortedToBalanced(a, b, i, m);
	sortedToBalanced(a, b, m+1, j);

}

/* Build a binary search tree from an array a. */
TreeNode* buildBST(vector<int> a, bool balance) {

	if (balance) {
		vector<int> b;
		sortedToBalanced(a, b, 0, a.size());
		a = b;
	}

	if (a.size() == 0) return NULL;
	TreeNode* root = new TreeNode(a[0]);
	for (int i = 1; i < a.size(); i++) {
		insertNode(root, a[i]);
	}
	return root;
}






































