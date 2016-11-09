#include <stdlib.h>
#include <glib.h>
#include <stdio.h>

typedef struct bin_tree {
	int data;
	struct bin_tree * right, * left;
} node;

node* newBinaryTree()
{
	return NULL;
}

node* insertNode(node* tree, int val)
{
	node *temp = NULL;

	if (!(tree)) {
		temp = malloc(sizeof(node));
		temp->left = temp->right = NULL;
		temp->data = val;
		tree = temp;
		return tree;
	}

	if (val < tree->data)
		tree->left = insertNode(tree->left, val);
	else if (val > tree->data)
		tree->right = insertNode(tree->right, val);

	return tree;
}

void do_preorder(node* tree, GList** in)
{
	if (tree) {
		int* val = malloc(sizeof(int));
		*val = tree->data;
		*in = g_list_append(*in, val);
		do_preorder(tree->left, in);
		do_preorder(tree->right, in);
	}
}

void preorder(node* tree, GList** in)
{
	*in = NULL;
	do_preorder(tree, in);
}

void do_inorder(node* tree, GList** in)
{
	if (tree) {
		do_inorder(tree->left, in);
		int* val = malloc(sizeof(int));
		*val = tree->data;
		*in = g_list_append(*in, val);
		do_inorder(tree->right, in);
	}
}

void inorder(node* tree, GList** in)
{
	*in = NULL;
	do_inorder(tree, in);
}

void do_postorder(node* tree, GList** in)
{
	if (tree) {
		do_postorder(tree->left, in);
		do_postorder(tree->right, in);
		int* val = malloc(sizeof(int));
		*val = tree->data;
		*in = g_list_append(*in, val);
	}
}

void postorder(node* tree, GList** in)
{
	*in = NULL;
	do_postorder(tree, in);
}

void freeTree(node* tree)
{
	if (tree) {
		freeTree(tree->left);
		freeTree(tree->right);
		free(tree);
	}
}

node* search(node* tree, int val)
{
	if (!(tree))
		return NULL;

	if (val < tree->data)
		search((tree->left), val);
	else if (val > tree->data)
		search(tree->right, val);
	return tree;
}

node* minValueNode(node* Node)
{
	node* current = Node;

	/* loop down to find the leftmost leaf */
	while (current->left != NULL)
		current = current->left;

	return current;
}

node* deleteNode(node* root, int data)
{
	if (root == NULL) return root;

	if (data < root->data)
		root->left = deleteNode(root->left, data);

	else if (data > root->data)
		root->right = deleteNode(root->right, data);

	else{
		if (root->left == NULL) {
			node *temp = root->right;
			free(root);
			return temp;
		}else if (root->right == NULL) {
			node *temp = root->left;
			free(root);
			return temp;
		}

		node* temp = minValueNode(root->right);

		root->data = temp->data;

		root->right = deleteNode(root->right, temp->data);
	}
	return root;
}

void displayList(GList* list)
{
	GList* iter = list;

	while (iter) {
		printf("%d ", *(int*)(iter->data));
		iter = iter->next;
	}

	printf("\n");
}

int depth(node* root)
{
	if (root == NULL)
		return 0;
	else {
		int lDepth = depth(root->left);
		int rDepth = depth(root->right);

		if (lDepth > rDepth)
			return lDepth + 1;
		else return rDepth + 1;
	}
}

node* findLeastCommonAncestor(node* root, int n1, int n2)
{
	// Base case
	if (root == NULL)
		return NULL;

	// If either n1 or n2 matches with root's data, report
	// the presence by returning root (Note that if a data is
	// ancestor of other, then the ancestor data becomes LCA
	if (root->data == n1 || root->data == n2)
		return root;

	// Look for keys in left and right subtrees
	node *left_lca  = findLeastCommonAncestor(root->left, n1, n2);
	node *right_lca = findLeastCommonAncestor(root->right, n1, n2);

	// If both of the above calls return Non-NULL, then one data
	// is present in once subtree and other is present in other,
	// So this node is the LCA
	if (left_lca && right_lca) return root;

	// Otherwise check if left subtree or right subtree is LCA
	return (left_lca != NULL) ? left_lca : right_lca;
}

/* Returns true if the given tree is a BST and its
   values are >= min and <= max. */
int isBSTUtil(node* root, int min, int max)
{
	/* an empty tree is BST */
	if (root == NULL)
		return 1;

	/* false if this node violates the min/max constraint */
	if (root->data < min || root->data > max)
		return 0;

	/* otherwise check the subtrees recursively,
	   tightening the min or max constraint */
	return
		isBSTUtil(root->left, min, root->data - 1) &&   // Allow only distinct values
		isBSTUtil(root->right, root->data + 1, max);    // Allow only distinct values
}

int isBST(node* root)
{
	return isBSTUtil(root, INT_MIN, INT_MAX);
}

int totalNodes(node* root)
{
	GList* in = NULL;
	inorder(root, &in);
	return g_list_length(in);
}

int main()
{
	node *root;

	//int i;

	root = newBinaryTree();
	/* Inserting nodes into tree */
	root = insertNode(root, 50);
	root = insertNode(root, 30);
	root = insertNode(root, 20);
	root = insertNode(root, 40);
	root = insertNode(root, 70);
	root = insertNode(root, 60);
	root = insertNode(root, 80);

	/* Printing nodes of tree */
	// printf("Pre Order Display\n");
	// print_preorder(root);

	GList* in = NULL;
	printf("\nIn Order Display\n");
	inorder(root, &in);
	displayList(in);

	root = deleteNode(root, 40);

	printf("\nIn Order Display\n");
	inorder(root, &in);
	displayList(in);

	printf("\nDepth = %d\n", depth(root));

	node* lca = findLeastCommonAncestor(root, 20, 80);
	if (lca == NULL)
		printf("\nLCA of [17] and [2] = NONE\n");
	else
		printf("\nLCA of [17] and [2] = %d\n", lca->data);

	printf("\nTree is %s BST\n", (isBST(root)) ? "a" : "NOT a");

	printf("\nTotal Nodes = %d\n", totalNodes(root));

	freeTree(root);
}
