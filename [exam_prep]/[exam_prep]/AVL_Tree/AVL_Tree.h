#include "minmax.h"
#include "../zNodeInfo/z.NodeInfo.h"

/*		-------------- AVL Tree --------------*/

typedef struct AVL_Tree
{
	NodeInfo* info;
	struct AVL_Tree* leftChild;
	struct AVL_Tree* rightChild;
	short bFactor;	// balance factor for a node -> 0 by default
}AVL_Tree, AVL_Node;

/*AVL tree specific methods*/
AVL_Node* createNode(NodeInfo* info);
short height(AVL_Tree*);

void insertAVL_Tree(AVL_Tree**, NodeInfo*);

AVL_Tree* leftRotation(AVL_Tree*);
AVL_Tree* rightRotation(AVL_Tree*);

AVL_Tree* leftRotate(AVL_Tree*);
AVL_Tree* rightRotate(AVL_Tree*);

AVL_Tree* rebalance(AVL_Tree*);

AVL_Tree* deleteNode(AVL_Tree*, int);
AVL_Tree* minValueNode(AVL_Tree*);

void printLeaves(AVL_Tree*);

void printTreeByLevel(AVL_Tree*);
void printLevel(AVL_Tree*, int);

void inorder_LPR(AVL_Tree*);
void inorder_PLR(AVL_Tree*);
void inorder_LRP(AVL_Tree*);


//info
/*
	- AVL Tree
	- if we want a balanced binary tree, we have to start with balanced and keep it that way
	- because the rotations only apply to was before an insertion/deletion
		-> when we insert we need to check the balance (equilibrium factor ?) and rebalance if needed
		( balance factor -> increases when we lean on one side -> we search for nodes with a balance factor
		outside a certain set: {-1, 0, 1})
		-> -1 for left side; 1 for right side
		-> when we do a rotation and the signs of the pivot and the descendant are different -> DOUBLE ROTATION
		-> first rotation is on the descendent then on the pivot (the incorrect node)
			-> positive balance factor out of the set -> ROTATION TO THE LEFT
			-> negative balance factor out of the set -> ROTATION TO THE RIGHT
	- BALANCE FACTOR CALCULATION: height[right_subtree] - height[left_subtree]
	Link to table: https://github.com/andreea-burada/sdd_2022/blob/main/seminar/seminar_13/AVL_rotations.png
						pivot ->
	desc/pivot		-	  |	    +
   _______________________|____________
  d		-		RR(pivot) | RR(desc)
  e						  | LR(pivot)
  s
  c		+		LR(desc)	LR(pivot)
  |				RR(pivot)
 \ /
*/

// implementation
AVL_Node* createNode(NodeInfo* info)
{
	AVL_Node* toReturn = (AVL_Node*)malloc(sizeof(AVL_Node));
	toReturn->info = info;
	toReturn->leftChild = NULL;
	toReturn->rightChild = NULL;
	toReturn->bFactor = 0;

	return toReturn;
}
short height(AVL_Tree* root)
{
	if (root)
		return 1 + max(height(root->leftChild), height(root->rightChild));
	else
		return 0;
}


void insertAVL_Tree(AVL_Tree** root, NodeInfo* info)
{
	// BinaryTree* aux = *root;

	if (*root == NULL) {		// the end of the recursivity
		AVL_Tree* newNode = createNode(info);
		*root = newNode;
	}
	else
	{
		if ((*root)->info->code > info->code)
			// insert on the left side of the root
			insertAVL_Tree(&((*root)->leftChild), info);
		else {
			if ((*root)->info->code < info->code)
				// insert to the right
				insertAVL_Tree(&((*root)->rightChild), info);
			else {
				(*root)->info = info;
			}
		}
	}
	// rebalancing the BST
	*root = rebalance(*root);

}



AVL_Tree* leftRotation(AVL_Tree* pivot)
{
	AVL_Tree* desc = pivot->rightChild;
	pivot->rightChild = desc->leftChild;
	desc->leftChild = pivot;

	return desc;
}
AVL_Tree* rightRotation(AVL_Tree* pivot)
{
	AVL_Tree* desc = pivot->leftChild;
	pivot->leftChild = desc->rightChild;
	desc->rightChild = pivot;

	return desc;
}

AVL_Tree* rebalance(AVL_Tree* root)
{
	AVL_Tree* desc = NULL;
	// recalculating the balance factor
	root->bFactor = height(root->rightChild) - height(root->leftChild);
	if (root->bFactor == -2)
	{
		desc = root->leftChild;
		if (desc->bFactor == -1)
		{
			// single rotation
			// RIGHT ROTATION on pivot
			root = rightRotation(root);
		}
		else
		{
			// double rotation
			// LEFT ROTATION on desc -> RIGHT ROTATION on pivot
			root->leftChild = leftRotation(desc);
			root = rightRotation(root);
		}
	}
	else if (root->bFactor == 2)
	{
		desc = root->rightChild;
		if (desc->bFactor == -1)
			root->rightChild = rightRotation(desc);
		root = leftRotation(root);
	}

	return root;
}



AVL_Tree* deleteNode(AVL_Tree* root, int key)
{

	// STEP 1: PERFORM STANDARD BST DELETE
	if (root == NULL)
		return root;

	// If the key to be deleted is smaller
	// than the root's key, then it lies
	// in left subtree
	if (key < root->info->code)
		root->leftChild = deleteNode(root->leftChild, key);

	// If the key to be deleted is greater
	// than the root's key, then it lies
	// in right subtree
	else if (key > root->info->code)
		root->rightChild = deleteNode(root->rightChild, key);

	// if key is same as root's key, then
	// This is the node to be deleted
	else
	{
		// node with only one child or no child
		if ((root->leftChild == NULL) ||
			(root->rightChild == NULL))
		{
			AVL_Node* temp = root->	leftChild ?
				root->leftChild :
				root->rightChild;

			// No child case
			if (temp == NULL)
			{
				temp = root;
				root = NULL;
			}
			else // One child case
				*root = *temp; // Copy the contents of
							   // the non-empty child
			free(temp);
		}
		else
		{
			// node with two children: Get the inorder
			// successor (smallest in the right subtree)
			AVL_Node* temp = minValueNode(root->rightChild);

			// Copy the inorder successor's
			// data to this node
			root->info->code = temp->info->code;

			// Delete the inorder successor
			root->rightChild = deleteNode(root->rightChild,
				temp->info->code);
		}
	}

	// If the tree had only one node
	// then return
	if (root == NULL)
		return root;

	// STEP 2: UPDATE HEIGHT OF THE CURRENT NODE
	root->bFactor = height(root->rightChild) - height(root->leftChild);

	// STEP 3: GET THE BALANCE FACTOR OF
	// THIS NODE (to check whether this
	// node became unbalanced)
	int balance = root->bFactor;

	// If this node becomes unbalanced,
	// then there are 4 cases

	// Left Left Case
	if (balance > 1 &&
		root->leftChild->bFactor >= 0)
		return rightRotate(root);

	// Left Right Case
	if (balance > 1 &&
		root->leftChild->bFactor < 0)
	{
		root->leftChild = leftRotate(root->leftChild);
		return rightRotate(root);
	}

	// Right Right Case
	if (balance < -1 &&
		root->rightChild->bFactor <= 0)
		return leftRotate(root);

	// Right Left Case
	if (balance < -1 &&
		root->rightChild->bFactor > 0)
	{
		root->rightChild = rightRotate(root->rightChild);
		return leftRotate(root);
	}

	return root;
}
// A utility function to right
// rotate subtree rooted with y
AVL_Tree* rightRotate(AVL_Tree* y)
{
	AVL_Tree* x = y->leftChild;
	AVL_Tree* T2 = x->rightChild;

	// Perform rotation
	x->rightChild = y;
	y->leftChild = T2;

	// Update heights
	y->bFactor = height(y->rightChild) - height(y->leftChild);
	x->bFactor = height(x->rightChild) - height(x->leftChild);

	// Return new root
	return x;
}

// A utility function to left
// rotate subtree rooted with x
AVL_Tree* leftRotate(AVL_Tree* x)
{
	AVL_Tree* y = x->rightChild;
	AVL_Tree* T2 = y->leftChild;

	// Perform rotation
	y->leftChild = x;
	x->rightChild = T2;

	// Update heights
	y->bFactor = height(y->rightChild) - height(y->leftChild);
	x->bFactor = height(x->rightChild) - height(x->leftChild);

	// Return new root
	return y;
}
AVL_Tree* minValueNode(AVL_Tree* node)
{
	AVL_Tree* current = node;

	/* loop down to find the leftmost leaf */
	while (current->leftChild != NULL)
		current = current->leftChild;

	return current;
}


void printLeaves(AVL_Tree* root)
{
	if (root)
	{
		if (root->leftChild == NULL && root->rightChild == NULL)
			printInfo(root->info);
		printLeaves(root->leftChild);
		printLeaves(root->rightChild);
	}
}

// print tree level by level - O(n*h); h - height
void printTreeByLevel(AVL_Tree* root)
{
	int treeHeight = height(root);
	for (int i = 1; i <= treeHeight; i++)
	{
		if (i == 1)
			printf("Root\n");
		else
			printf("Level %d\n", i);
		printLevel(root, i);
		printf("\n");
	}
}
void printLevel(AVL_Tree* root, int lvl)
{
	if (lvl != 1)
	{
		if (root->leftChild)
			printLevel(root->leftChild, lvl - 1);
		if (root->rightChild)
			printLevel(root->rightChild, lvl - 1);
	}
	else {
		printInfo(root->info);
	}
}



void inorder_LPR(AVL_Tree* root) {

	if (root)
	{
		inorder_LPR(root->leftChild);
		printInfo(root->info);
		inorder_LPR(root->rightChild);
	}
}
// printing the root first then in ascending order
void inorder_PLR(AVL_Tree* root) {

	if (root)
	{
		printInfo(root->info);
		inorder_PLR(root->leftChild);
		inorder_PLR(root->rightChild);
	}
}
// printing in descending order
void inorder_LRP(AVL_Tree* root) {

	if (root)
	{
		inorder_LRP(root->leftChild);
		inorder_LRP(root->rightChild);
		printInfo(root->info);
	}
}