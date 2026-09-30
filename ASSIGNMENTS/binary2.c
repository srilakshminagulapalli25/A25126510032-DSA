#include <stdio.h>
#include <stdlib.h>
struct Node
{
    int data;
    struct Node *left;
    struct Node *right;
};
struct Node* createNode(int value)
{
    struct Node *newNode;
    newNode = (struct Node*)malloc(sizeof(struct Node));
    newNode->data = value;
    newNode->left = NULL;
    newNode->right = NULL;
    return newNode;
}
struct Node* insert(struct Node *root, int value)
{
    if (root == NULL)
        return createNode(value);
    if (value < root->data)
        root->left = insert(root->left, value);
    else if (value > root->data)
        root->right = insert(root->right, value);
    return root;
}
void inorder(struct Node *root)
{
    if (root != NULL)
    {
        inorder(root->left);
        printf("%d ", root->data);
        inorder(root->right);
    }
}
void preorder(struct Node *root)
{
    if (root != NULL)
    {
        printf("%d ", root->data);
        preorder(root->left);
        preorder(root->right);
    }
}
void postorder(struct Node *root)
{
    if (root != NULL)
    {
        postorder(root->left);
        postorder(root->right);
        printf("%d ", root->data);
    }
}
struct Node* search(struct Node *root, int value)
{
    if (root == NULL || root->data == value)
        return root;
    if (value < root->data)
        return search(root->left, value);
    else
        return search(root->right, value);
}
struct Node* findMin(struct Node *root)
{
    while (root->left != NULL)
        root = root->left;
    return root;
}
struct Node* deleteNode(struct Node *root, int value)
{
    struct Node *temp;
    if (root == NULL)
        return root;
    if (value < root->data)
    {
        root->left = deleteNode(root->left, value);
    }
    else if (value > root->data)
    {
        root->right = deleteNode(root->right, value);
    }
    else
    {
        if (root->left == NULL && root->right == NULL)
        {
            free(root);
            return NULL;
        }
        else if (root->left == NULL)
        {
            temp = root->right;
            free(root);
            return temp;
        }
        else if (root->right == NULL)
        {
            temp = root->left;
            free(root);
            return temp;
        }
        else
        {
            temp = findMin(root->right);
            root->data = temp->data;
            root->right = deleteNode(root->right, temp->data);
        }
    }

    return root;
}
int main()
{
    struct Node *root = NULL;
    int n, value, searchValue, deleteValue;
    int i;
    printf("Enter number of values: ");
    scanf("%d", &n);
    printf("Enter %d unique values:\n", n);
    for (i = 0; i < n; i++)
    {
        scanf("%d", &value);
        root = insert(root, value);
    }
    printf("\nInorder Traversal: ");
    inorder(root);
    printf("\nPreorder Traversal: ");
    preorder(root);
    printf("\nPostorder Traversal: ");
    postorder(root);
    printf("\n\nEnter value to search: ");
    scanf("%d", &searchValue);
    if (search(root, searchValue) != NULL)
        printf("%d exists in the BST.\n", searchValue);
    else
        printf("%d does not exist in the BST.\n", searchValue);
    printf("\nEnter value to delete: ");
    scanf("%d", &deleteValue);
    if (search(root, deleteValue) != NULL)
    {
        root = deleteNode(root, deleteValue);
        printf("%d deleted successfully.\n", deleteValue);
        printf("\nInorder after deletion: ");
        inorder(root);
        printf("\nPreorder after deletion: ");
        preorder(root);
        printf("\nPostorder after deletion: ");
        postorder(root);
    }
    else
    {
        printf("%d does not exist in the BST.\n", deleteValue);
    }
    return 0;
}