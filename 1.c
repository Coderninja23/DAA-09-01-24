#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>

struct Node
{
    int data;
    struct Node *left;
    struct Node *right;
};

struct Node *createNode(int val)
{
    struct Node *root = (struct Node *)malloc(sizeof(struct Node));
    root->data = val;
    // printf("%d", root->data);
    root->left = NULL;
    root->right = NULL;
    return root;
}

void preorder(struct Node *root)
{
    if (!root)
        return;
    preorder(root->left);
    printf("%d ", root->data);
    preorder(root->right);
}

void inorder(struct Node *root)
{
    if (!root)
        return;
    inorder(root->left);
    printf("%d ", root->data);
    inorder(root->right);
}

void postorder(struct Node *root)
{
    if (!root)
        return;
    preorder(root->left);
    preorder(root->right);
    printf("%d ", root->data);
}

void inorderIterative(struct Node *root)
{
    struct Node *curr = root;
    while (curr)
    {
        if (!curr->left)
        {
            printf("%d ", curr->data);
            curr = curr->right;
        }
        else
        {
            struct Node *prev = curr->left;
            while (prev->right && prev->right != curr)
                prev = prev->right;
            if (!prev->right)
            {
                prev->right = curr;
                curr = curr->left;
            }
            else if (prev->right == curr)
            {
                printf("%d ", curr->data);
                prev->right = NULL;
                curr = curr->right;
            }
        }
    }
}

void preorderIterative(struct Node *root)
{
    struct Node *curr = root;
    while (curr)
    {
        if (!curr->left)
        {
            printf("%d ", curr->data);
            curr = curr->right;
        }
        else
        {
            struct Node *prev = curr->left;
            while (prev->right && prev->right != curr)
                prev = prev->right;
            if (!prev->right)
            {
                printf("%d ", curr->data);

                prev->right = curr;
                curr = curr->left;
            }
            else if (prev->right == curr)
            {
                prev->right = NULL;
                curr = curr->right;
            }
        }
    }
}

int main()
{
    //User input not generated since question mentions to create functions.
    struct Node *root = createNode(10);
    root->left = createNode(8);
    root->left->left = createNode(7);
    root->left->right = createNode(9);
    root->right = createNode(12);
    root->right->left = createNode(11);
    root->right->right = createNode(13);
    preorderIterative(root);
    return 0;
}