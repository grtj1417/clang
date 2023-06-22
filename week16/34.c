#include <stdio.h>
#include <stdlib.h>
#include <string.h>

typedef struct Node {
    char data;
    struct Node *left, *right;
} TreeNode;

typedef TreeNode *BinaryTree;

void printTree(BinaryTree bTree);
void printLevelOrder(BinaryTree root);
void printCurrentLevel(BinaryTree root, int level);
int calculateHeight(BinaryTree node);

void printLevelOrder(BinaryTree root)
{
    int height = calculateHeight(root);
    for (int level = 1; level <= height; level++)
        printCurrentLevel(root, level);
}

void printCurrentLevel(BinaryTree root, int level)
{
    if (root == NULL)
        return;
    if (level == 1) {
        printf("%c", root->data);
    } else if (level > 1) {
        printCurrentLevel(root->left, level - 1);
        printCurrentLevel(root->right, level - 1);
    }
}

int calculateHeight(BinaryTree node)
{
    if (node == NULL)
        return 0;
    else {
        int lHeight = calculateHeight(node->left);
        int rHeight = calculateHeight(node->right);
        if (lHeight > rHeight)
            return (lHeight + 1);
        else
            return (rHeight + 1);
    }
}

TreeNode *buildTreeFromPreIn(char *preOrder, char *inOrder, int treeSize)
{
    if (treeSize == 0)
        return NULL;

    TreeNode *root = (TreeNode *)malloc(sizeof(TreeNode));
    root->data = preOrder[0];
    root->left = NULL;
    root->right = NULL;

    if (treeSize == 1)
        return root;

    int i;
    for (i = 0; i < treeSize; i++) {
        if (inOrder[i] == root->data)
            break;
    }

    int leftSize = i;
    root->left = buildTreeFromPreIn(&preOrder[1], inOrder, leftSize);
    int rightSize = treeSize - leftSize - 1;
    root->right = buildTreeFromPreIn(&preOrder[1 + leftSize], &inOrder[i + 1], rightSize);
    return root;
}

TreeNode *buildTreeFromPostIn(char *postOrder, char *inOrder, int treeSize)
{
    if (treeSize == 0)
        return NULL;

    TreeNode *root = (TreeNode *)malloc(sizeof(TreeNode));
    root->data = postOrder[treeSize - 1];
    root->left = NULL;
    root->right = NULL;

    if (treeSize == 1)
        return root;

    int i;
    for (i = 0; i < treeSize; i++) {
        if (inOrder[i] == root->data)
            break;
    }

    int leftSize = i;
    root->left = buildTreeFromPostIn(postOrder, inOrder, leftSize);
    int rightSize = treeSize - leftSize - 1;
    root->right = buildTreeFromPostIn(&postOrder[leftSize], &inOrder[i + 1], rightSize);

    return root;
}

void constructBinaryTree()
{
    int nodeNum;
    char order_1, order_2;
    char node_1[20], node_2[20];
    scanf("%c\n", &order_1);
    scanf("%s\n", node_1);
    scanf("%c\n", &order_2);
    scanf("%s", node_2);

    nodeNum = strlen(node_1);
    BinaryTree root;

    if (order_1 == 'P' && order_2 == 'I') {
        TreeNode *rootNode = buildTreeFromPreIn(node_1, node_2, nodeNum);
        root = rootNode;
    } else if (order_1 == 'I' && order_2 == 'P') {
        TreeNode *rootNode = buildTreeFromPreIn(node_2, node_1, nodeNum);
        root = rootNode;
    } else if (order_1 == 'O' && order_2 == 'I') {
        TreeNode *rootNode = buildTreeFromPostIn(node_1, node_2, nodeNum);
        root = rootNode;
    } else if (order_1 == 'I' && order_2 == 'O') {
        TreeNode *rootNode = buildTreeFromPostIn(node_2, node_1, nodeNum);
        root = rootNode;
    }

    printLevelOrder(root);
}

int main()
{
    constructBinaryTree();
    return 0;
}
