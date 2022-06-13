
#include "../zNodeInfo/z.NodeInfo.h"

/*		-------------- Binary Search Tree --------------*/

typedef struct BST
{
	struct BST* leftChild;
	NodeInfo* info;
	struct BST* rightChild;
}BinarySearchTree, BinaryNode;

/*binary search tree specific methods*/
BinaryNode* createNode(NodeInfo*);

void printInfo(NodeInfo*);

void insertBST(BinarySearchTree**, NodeInfo*);

void deleteBST(BinarySearchTree**, int);
void logicalDeletion(BinarySearchTree**, BinarySearchTree**);

void inorder_LPR(BinarySearchTree*);
void inorder_PLR(BinarySearchTree*);
void inorder_LRP(BinarySearchTree*);

// implementation
BinarySearchTree* createNode(NodeInfo* info)
{
	BinarySearchTree* node = (BinarySearchTree*)malloc(sizeof(BinarySearchTree));
	node->info = info;
	node->leftChild = node->rightChild = NULL;
	return node;
}



void insertBST(BinarySearchTree** root, NodeInfo* info)
{
	if (*root == NULL)
	{
		*root = createNode(info);
	}
	else
	{
		if ((*root)->info->code > info->code)
			insertBST(&(*root)->leftChild, info);
		else if ((*root)->info->code < info->code)
			insertBST(&(*root)->rightChild, info);
		else
			(*root)->info = info;
	}
}



void deleteBST(BinarySearchTree** root, int key)
{
	if (*root != NULL)
	{
		if ((*root)->info->code > key)
			deleteBST(&(*root)->leftChild, key);
		else if ((*root)->info->code < key)
			deleteBST(&(*root)->rightChild, key);
		else
		{
			if ((*root)->leftChild == NULL && (*root)->rightChild == NULL)
			{
				free((*root)->info->name);
				free((*root)->info->dept);
				free((*root)->info);
				free((*root));
				*root = NULL;
			}
			else if ((*root)->leftChild == NULL || (*root)->rightChild == NULL)
			{
				BinarySearchTree* desc = NULL;
				if ((*root)->leftChild)
					desc = (*root)->leftChild;
				else
					desc = (*root)->rightChild;
				free((*root)->info->name);
				free((*root)->info->dept);
				free((*root)->info);
				free((*root));
				*root = desc;
			}
			else
				logicalDeletion(root, &(*root)->leftChild);
		}
	}
}
void logicalDeletion(BinarySearchTree** root, BinarySearchTree** leftSubTree)
{
	if ((*leftSubTree)->rightChild)
		logicalDeletion(root, &(*leftSubTree)->rightChild);
	else
	{
		NodeInfo* tmp = (*root)->info;
		(*root)->info = (*leftSubTree)->info;
		BinarySearchTree* aux = (*leftSubTree);
		(*leftSubTree) = (*leftSubTree)->leftChild;
		free(tmp->name);
		free(tmp->dept);
		free(tmp);
		free(aux);
	}
}



void inorder_LPR(BinarySearchTree* root) {
	
	if (root)
	{
		inorder_LPR(root->leftChild);
		printInfo(root->info);
		inorder_LPR(root->rightChild);
	}
}
// printing the root first then in ascending order
void inorder_PLR(BinarySearchTree* root) {
	
	if (root)
	{
		printInfo(root->info);
		inorder_PLR(root->leftChild);
		inorder_PLR(root->rightChild);
	}
}
// printing in descending order
void inorder_LRP(BinarySearchTree* root) {
	
	if (root)
	{
		inorder_LRP(root->leftChild);
		inorder_LRP(root->rightChild);
		printInfo(root->info);
	}
}