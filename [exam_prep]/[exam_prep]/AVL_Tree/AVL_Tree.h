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

AVL_Tree* rebalance(AVL_Tree*);

// to add - delete by key

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