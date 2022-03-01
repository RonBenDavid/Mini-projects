/*
Assigned by:
Ron ben david
*/
#define _CRT_SECURE_NO_DEPRECATE
#include<stdlib.h>
#include<stdio.h>
#include<stdbool.h>
#define COUNT 10

typedef int tree_type;

typedef struct tree {
	tree_type data;
	struct tree* right, * left, * parent;
	int height;
}tree;

/*create a new node*/
tree* create_node(tree* parent, tree_type data)
{
	tree* node = (tree*)malloc(sizeof(tree));
	if (!node)
	{
		printf("Not enough system memory is available for allocation!\n");
		exit(1);
	}
	node->data = data;
	node->parent = parent;
	node->left = node->right = NULL;
	node->height = 1;
	return node;
}

/*insert a new node into the BST using iterative method*/
void insert_iterative(tree** root, tree_type data)
{
	if (!(*root))
	{
		*root = create_node(NULL, data);
	}
	else
	{
		tree* cursor = *root;

		while (1)
		{
			if (data < cursor->data)
			{
				if (cursor->left)
					cursor = cursor->left;
				else
				{
					cursor->left = create_node(cursor, data);
					return;
				}
			}
			else if (data > cursor->data)
			{
				if (cursor->right)
					cursor = cursor->right;
				else
				{
					cursor->right = create_node(cursor, data);
					return;
				}
			}
			else //(data == cursor->data)
			{
				return;
			}
		}
	}
}

void print_preorder(tree* root)
{
	if (root)
	{
		printf("%d ", root->data);
		print_preorder(root->left);
		print_preorder(root->right);
	}

}

void print_inorder(tree* root)
{
	if (root)
	{
		print_inorder(root->left);
		printf("%d ", root->data);
		print_inorder(root->right);
	}
}

void print_postorder(tree* root)
{
	if (root)
	{
		print_postorder(root->left);
		print_postorder(root->right);
		printf("%d ", root->data);
	}
}

void deltree(tree** root)
{
	if (*root)
	{
		deltree(&((*root)->left));
		deltree(&((*root)->right));
		free(*root);
		*root = NULL;
	}
}

tree* search(tree* root, tree_type data)
{
	if (!root)
		return NULL;

	if (data < root->data)
	{
		search(root->left, data);
	}
	else if (data > root->data)
	{
		search(root->right, data);
	}
	else if (data == root->data)
	{
		return root;
	}
}

tree* min_value(tree* node, int* height)
{
	*height = 0;

	/* loop down to find the leftmost leaf */
	while (node->left != NULL)
	{
		node = node->left;
		(*height)++;
	}

	return node;
}

tree* max_value(tree* node, int* height)
{
	*height = 0;

	/* loop down to find the rightmost leaf */
	while (node->right != NULL)
	{
		node = node->right;
		(*height)++;
	}

	return node;
}

/*delete a node in the BST*/
tree* delete_node(tree* root, tree_type data)
{
	if (!root)
		return NULL;

	if (data < root->data)
		root->left = delete_node(root->left, data);
	else if (data > root->data)
		root->right = delete_node(root->right, data);
	else
	{
		tree* cursor = NULL;

		if ((root->left) && (root->right)) //2 children
		{
			int left, right;
			tree* parent = NULL;
			tree* cursorLeft = min_value(root->right, &left);
			tree* cursorRight = max_value(root->left, &right);

			cursor = (left > right) ? cursorLeft : cursorRight;
			parent = cursor->parent;
			root->data = cursor->data;

			if (parent->left == cursor)
				parent->left = delete_node(parent->left, cursor->data);
			else
				parent->right = delete_node(parent->right, cursor->data);
		}
		else
		{
			if (root->left)	//only left child
			{
				cursor = root->left;
				cursor->parent = root->parent;
			}
			else if (root->right) //only right child
			{
				cursor = root->right;
				cursor->parent = root->parent;
			}
			free(root);
			root = cursor;
		}
	}
	return root;
}

int maxDepth(tree* root)
{
	if (root == NULL)
		return 0;
	else
	{
		/* compute the depth of each subtree */
		int lDepth = maxDepth(root->left);
		int rDepth = maxDepth(root->right);

		/* use the larger one */
		if (lDepth > rDepth)
			return(lDepth + 1);
		else return(rDepth + 1);
	}
}
static int count = 0;
int maxnodes(tree* root)
{
		if (root != NULL)
		{
			maxnodes(root->left);
			count++;
			maxnodes(root->right);
		}
		return count;

}
int countright(tree* root) {
	if (root == NULL) return 0;
	int num_l = 0, num_r = 0;
	if (root->left != NULL)
		num_l = countright(root->left);
	if (root->right != NULL)
		num_r = countright(root->right) + 1;
	return num_l + num_r;
}
unsigned int getLeafCount(tree* root)
{
	if (root == NULL)
		return 0;
	if (root->left == NULL && root->right == NULL)
		return 1;
	else
		return getLeafCount(root->left) +
		getLeafCount(root->right);
}
struct tree* lca(struct tree* root, int node_1, int node_2)
{
	if (root != NULL)
	{
		if (root->data > node_1 && root->data > node_2)
		{
			return lca(root->left, node_1, node_2);
		}
		if (root->data < node_1 && root->data < node_2)
		{
			return lca(root->right, node_1, node_2);
		}
		return root;
	}
}
void print_tree(tree* root, int space)
{
	int i;

	// Base case
	if (!root)
		return;

	// Process right child first
	print_tree(root->right, space + COUNT);

	// Print current node after space
	// count
	printf("\n");
	for (i = 0; i < space; i++)
		printf(" ");
	printf("%d\n", root->data);

	// Process left child
	print_tree(root->left, space + COUNT);
}

// Function to print binary tree in 2D
// It does reverse inorder
bool AVL(tree* root) {
	int lh;
	int rh;
	if (root == NULL)
		return 1;
	lh = maxDepth(root->left); // left height
	rh = maxDepth(root->right); // right height
	if (abs(lh - rh) <= 1 && AVL(root->left) && AVL(root->right)) return 1;
	return 0;
}
int avl_balance_factor(tree* node) {
	int bf = 0;

	if (node->left) bf += maxDepth(node->left);
	if (node->right) bf -= maxDepth(node->right);

	return bf;
}
int height(tree* N)
{
	if (N == NULL)
		return 0;
	return N->height;
}
int getBalance(tree* root)
{
	if (root == NULL)
		return 0;
	return height(root->left) - height(root->right);
}
tree* avl_rotate_leftleft(tree* node) {
	tree* a = node;
	tree* b = a->left;

	a->left = b->right;
	b->right = a;

	return(b);
}

/* Left Right Rotate */
tree* avl_rotate_leftright(tree* node) {
	tree* a = node;
	tree* b = a->left;
	tree* c = b->right;

	a->left = c->right;
	b->right = c->left;
	c->left = b;
	c->right = a;

	return(c);
}

/* Right Left Rotate */
tree* avl_rotate_rightleft(tree* node) {
	tree* a = node;
	tree* b = a->right;
	tree* c = b->left;

	a->right = c->left;
	b->left = c->right;
	c->right = b;
	c->left = a;

	return(c);
}

/* Right Right Rotate */
tree* avl_rotate_rightright(tree* node) {
	tree* a = node;
	tree* b = a->right;

	a->right = b->left;
	b->left = a;

	return(b);
}
tree* BalanceAVL(tree* node) {
	tree* newroot = NULL;

	/* Balance our children, if they exist. */
	if (node->left)
		node->left = BalanceAVL(node->left);
	if (node->right)
		node->right = BalanceAVL(node->right);

	int bf = avl_balance_factor(node);

	if (bf >= 2) {
		/* Left Heavy */

		if (avl_balance_factor(node->left) <= -1)
			newroot = avl_rotate_leftright(node);
		else
			newroot = avl_rotate_leftleft(node);

	}
	else if (bf <= -2) {
		/* Right Heavy */

		if (avl_balance_factor(node->right) >= 1)
			newroot = avl_rotate_rightleft(node);
		else
			newroot = avl_rotate_rightright(node);

	}
	else {
		/* This node is balanced -- no change. */

		newroot = node;
	}

	return(newroot);
}
void main()
{
	int num;
	tree* temp = NULL;
	tree* root = NULL;
	bool itsavl;

	insert_iterative(&root, 5);
	insert_iterative(&root, 3);
	insert_iterative(&root, 7);
	insert_iterative(&root, 15);
	insert_iterative(&root, 6);
	insert_iterative(&root, 12);
	insert_iterative(&root, 17);
	insert_iterative(&root, 2);
	insert_iterative(&root, 0);
	struct tree* t = lca(root, 2, 6);
	printf("LCA of %d and %d is %d \n", 2, 6, t->data);
	itsavl = AVL(root);
	print_tree(root, 0);
	if (AVL(root))
		printf("The Tree is AVL Tree\n");
	else
	{
		printf("The Tree is not AVL\n");
		do
		{
			BalanceAVL(root);
			printf("\n\nThe tree now is AVL!\n\n");
			print_tree(root, 0);
		} while (!AVL(root));
	}
	deltree(&root);
}
