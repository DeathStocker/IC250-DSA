#include <stdlib.h>
#include <glib.h>
#include <stdio.h>
#include <ctype.h>

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

int isBSTUtil(node* root, int min, int max)
{
	if (root == NULL)
		return 1;

	if (root->data < min || root->data > max)
		return 0;

	return
		isBSTUtil(root->left, min, root->data - 1) &&
		isBSTUtil(root->right, root->data + 1, max);
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

GList* findInList(GList* list, int val)
{
	GList* iter = list;

	while (iter) {
		if (*(int*)(iter->data) == val)
			break;
		iter = iter->next;
	}
	return iter;
}

GList* inSuccessor(node* root, int data)
{
	GList* in = NULL;

	inorder(root, &in);

	GList* Node = findInList(in, data);

	if (Node == NULL)
		return NULL;
	return Node->next;
}

GList* inPredecessor(node* root, int data)
{
	GList* in = NULL;

	inorder(root, &in);

	GList* Node = findInList(in, data);

	if (Node == NULL)
		return NULL;
	return Node->prev;
}

int Abs(int val)
{
	return (val < 0) ? -val : val;
}

int closestNode(node* root, int val)
{
	GList* in = NULL;

	inorder(root, &in);

	GList* iter = in;

	int min = INT_MAX;
	int closest = INT_MIN;
	while (iter) {
		int diff = Abs(val - *(int*)(iter->data));
		if (diff < min) {
			min = diff;
			closest = *(int*)(iter->data);
		}
		iter = iter->next;
	}

	return closest;
}

node* lca(node* root, int n1, int n2)
{
	if (root == NULL) return NULL;

	if (root->data > n1 && root->data > n2)
		return lca(root->left, n1, n2);

	if (root->data < n1 && root->data < n2)
		return lca(root->right, n1, n2);

	return root;
}

node* findLCA(node* root, int n1, int n2)
{
	GList* in = NULL;

	inorder(root, &in);
	if (findInList(in, n1) == NULL || findInList(in, n2) == NULL)
		return NULL;
	node* LCA = lca(root, n1, n2);

	return LCA;
}

int searchInInorder(int* arr, int x, int n)
{
	int i;

	for (i = 0; i < n; i++)
		if (arr[i] == x)
			return i;
	return -1;
}

void preToPostOrder(GList** list, int* in, int* pre, int n)
{
	// The first element in pre[] is always root, search it
	int root = searchInInorder(in, pre[0], n);

	// If left subtree is not empty, print left subtree
	if (root != 0)
		preToPostOrder(list, in, pre + 1, root);

	// If right subtree is not empty, print right subtree
	if (root != n - 1)
		preToPostOrder(list, in + root + 1, pre + root + 1, n - root - 1);

	int* val = malloc(sizeof(int));
	*val = pre[0];
	*list = g_list_append(*list, val);
}

int* listToArray(GList* list, int len)
{
	int* arr = malloc(len * sizeof(int));

	int i;

	for (i = 0; i < len; i++, list = list->next)
		arr[i] = *(int*)(list->data);

	return arr;
}

int cmpFunc(const void* a, const void* b)
{
	return *(int*)(a) - *(int*)(b);
}

void preToPost(node* root, GList** list)
{
	(void)root;

	int length = g_list_length(*list);
	int* pre = listToArray(*list, length);

	*list = g_list_sort(*list, cmpFunc);
	int* in = listToArray(*list, length);

	GList* post = NULL;

	preToPostOrder(&post, in, pre, length);

	*list = post;
}

int main()
{
	node *root;

	root = newBinaryTree();
	/* Inserting nodes into tree */
	root = insertNode(root, 30);
	root = insertNode(root, 20);
	root = insertNode(root, 50);
	root = insertNode(root, 40);
	root = insertNode(root, 70);
	root = insertNode(root, 60);
	root = insertNode(root, 80);
	root = insertNode(root, 10);
	root = insertNode(root, 90);

	GList* in = NULL;
	printf("\nIn Order Display\n");
	inorder(root, &in);
	displayList(in);

	root = deleteNode(root, 40);

	printf("\nPre Order Display\n");
	preorder(root, &in);
	displayList(in);

	printf("\nPost Order Display\n");
	postorder(root, &in);
	displayList(in);

	printf("\nDepth = %d\n", depth(root));

	node* lca = findLCA(root, 60, 10);
	if (lca == NULL)
		printf("\nLCA of [60] and [10] = NONE\n");
	else
		printf("\nLCA of [60] and [10] = %d\n", lca->data);

	printf("\nTree is %s BST\n", (isBST(root)) ? "a" : "NOT a");

	printf("\nTotal Nodes = %d\n", totalNodes(root));

	GList* insucc = inSuccessor(root, 50);
	printf("Inorder Successor of %d = ", 50);
	(insucc == NULL) ? printf("NONE.\n") : printf("%d\n", *(int*)(insucc->data));

	GList* inpre = inPredecessor(root, 50);
	printf("Inorder Successor of %d = ", 50);
	(insucc == NULL) ? printf("NONE.\n") : printf("%d\n", *(int*)(inpre->data));

	printf("Closest to [%d] = %d\n", 18, closestNode(root, 18));

	printf("\n=======================\n\nPre Order Display\n");
	preorder(root, &in);
	displayList(in);

	printf("\nPost Order from Pre Order = \n");
	preToPost(root, &in);
	displayList(in);

	freeTree(root);
}
