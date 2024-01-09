#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>

struct Node{
    int data;
    struct Node *left;
    struct Node *right;
};

struct Node*createNode(int val){
    struct Node* root=(struct Node*)malloc(sizeof(struct Node));
    root->data=val;
    // printf("%d", root->data);
    root->left=NULL;
    root->right=NULL;
    return root;
}

//Searching if an element is present-Recursive
bool search(struct Node*root, int val){
    if(!root)return false;
    if(root->data==val)return true;
    bool a, b;
    if(val>root->data){
        a=search(root->right, val);
    }
    else{
        b=search(root->left, val);
    }
    if(!a && !b)return false;
    return true;
}


//Searching for an element-Iterative method
bool searchIterative(struct Node*root, int val){
    struct Node* curr=root;
    while(curr){
        if(curr->data==val)return true;
        else if(curr->data>val)curr=curr->left;
        else curr=curr->right;
    }
    return false;
}


//Inserting a value in a BST
struct Node*insert(struct Node*root, int val){
    if(!root){
        struct Node*temp=createNode(val);
        return temp;
    }
    if(val>(root)->data){
        (root)->right=insert(((root)->right), val);
    }
    else if(val<(root)->data){
        (root)->left=insert(((root)->left), val);
    }
    else return NULL;
}

//Helper function
void storeIndored(struct Node*root, int arr[], int *i){
    if(!root)return;
    storeIndored(root->left, arr, i);
    arr[*i]=root->data;
    *i=*i+1;
    storeIndored(root->right, arr, i);
}

int successor(struct Node*root, int val){
    int arr[100]={0};
    int i=0;
    storeIndored(root, arr, &i);
    int size=i-1;
    for(int k=0;k<size-1;k++){
        if(arr[k]==val)return arr[k+1];
    }
    return -1;
}

//Helper function
struct Node*successorDel(struct Node*givenNode){
    if(!givenNode)return NULL;
    struct Node*curr=givenNode->right;
    if(!curr)return NULL;
    while(curr->left)curr=curr->left;
    return curr;
}

struct Node*predeccessor(struct Node*givenNode){
    if(!givenNode)return NULL;
    struct Node*curr=givenNode->left;
    if(!curr)return NULL;
    while(curr->right)curr=curr->right;
    return curr;
}

//Assumption-The function is receiving the value and the value always exists in the tree.
struct Node*deletion(struct Node*root, int val){
    if(!root || (!root->left && !root->right))return NULL;
    if(root->data==val){
        if(root->right){
            struct Node*succ=successorDel(root);
            root->data=succ->data;
            root->right=deletion(root->right, succ->data);
        }
        else{
            struct Node*pree=predeccessor(root);
            root->data=pree->data;
            root->left=deletion(root->left, pree->data);
        }
    }
    else if(val>root->data)root->right=deletion(root->right, val);
    else root->left=deletion(root->left, val);
    return root;
}

void inorder(struct Node*root){
    if(!root)return;
    inorder(root->left);
    printf("%d ", root->data);
    inorder(root->right);
}

int main(){

    //User input not generated since question mentions to create functions.
    struct Node*root=createNode(10);
    root->left=createNode(8);
    root->left->left=createNode(7);
    root->left->right=createNode(9);
    root->right=createNode(12);
    root->right->left=createNode(11);
    root->right->right=createNode(13);
    // printf("%d", root->data);
    // root=insert(root, 1);
    // root=deletion(root, 8);
    int suc=successor(root, 10 );
    printf("%d", suc);

    inorder(root);

    return 0;
}