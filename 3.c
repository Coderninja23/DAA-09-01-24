#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>

struct Node
{
    int val;
    struct Node *next;
};

struct Node *createNode(int val)
{
    struct Node *temp = (struct Node *)malloc(sizeof(struct Node));
    temp->val = val;
    temp->next = NULL;
    return temp;
}

void insert(struct Node **head, int pos, int val)
{
    if (!head)
    {
        struct Node *temp = createNode(val);
        (*head) = temp;
        return;
    }
    if (pos == 1)
    {
        struct Node *temp = createNode(val);
        temp->next = *head;
        *head = temp;
        return;
    }
    else
    {
        struct Node *temp = *head;
        for (int i = 1; i < pos - 1; i++)
        {
            if (!temp)
                return;
            temp = temp->next;
        }
        struct Node *newNode = createNode(val);
        newNode->next = temp->next;
        temp->next = newNode;
    }
}

void deleteAtBeginning(struct Node**head){
    if(!(*head))return;
    struct Node*temp=(*head)->next;
}

void deletion(struct Node **head, int val)
{
    if (!(*head))
        return;
    struct Node *temp = *head;
    if (temp->val == val)
    {
        struct Node *temp = temp->next;
        temp->next = NULL;
        free(temp);
        *head = temp;
    }
    while (temp && temp->next && temp->next->val != val)
        temp = temp->next;
    if (!temp || !temp->next)
        return;
    struct Node *dele = temp->next;
    temp->next = temp->next->next;
    free(dele);
}

void insertAsSorted(struct Node **head, int val)
{
    if (!head)
    {
        struct Node *temp = createNode(val);
        (*head) = temp;
        return;
    }
    struct Node *temp = *head;
    while (temp && temp->next && temp->next->val < val)
        temp = temp->next;
    if (!temp)
        return;
    struct Node *newNode = createNode(val);
    newNode->next = temp->next;
    temp->next = newNode;
}

void FrontBackSplit(struct Node *head, int n, struct Node **head1, struct Node **head2)
{
    int n1 = n / 2 + n % 2;
    int n2 = n / 2;
    *head1 = createNode(head->val);
    struct Node *temp1 = (*head1);

    struct Node *it = head->next;
    for (int i = 1; i < n1; i++)
    {
        struct Node *temp = createNode(it->val);
        temp1->next = temp;
        temp1 = temp1->next;
        it = it->next;
    }
    *head2 = createNode(it->val);
    struct Node *temp2 = *head2;
    it = it->next;
    for (int i = 1; i < n2; i++)
    {
        struct Node *temp = createNode(it->val);
        temp2 = temp;
        temp2 = temp2->next;
    }
}

void sort(int arr[], int n)
{
    for (int i = 0; i < n; i++)
    {
        for (int j = 1; j < n - i; j++)
        {
            if (arr[j] < arr[j - 1])
            {
                int temp = arr[j - 1];
                arr[j - 1] = arr[j];
                arr[j] = temp;
            }
        }
    }
}

void Merge(int arr[], int l, int mid, int h)
{
    int i = l, j = mid + 1, k = l;
    int b[100];
    while (i <= mid && j <= h)
    {
        if (arr[i] < arr[j])
        {
            b[k++] = arr[i++];
        }
        else
        {
            b[k++] = arr[j++];
        }
    }
    while (i <= mid)
        b[k++] = arr[i++];
    while (j <= h)
        b[k++] = arr[j++];
    for (int i = l; i <= h; i++)
    {
        arr[i] = b[i];
    }
}

void mergeSort(int arr[], int l, int h)
{
    if (l >= h)
        return;

    int mid = l + (h - l) / 2;
    mergeSort(arr, l, mid);
    mergeSort(arr, mid + 1, h);
    Merge(arr, l, mid, h);
    // cout<<l<<endl;
}

void storeIndored(struct Node *head, int arr[], int *i)
{
    if (!head)
        return;
    struct Node *temp = head;
    while (temp)
    {
        arr[*i] = temp->val;
        *i = *i + 1;
        temp = temp->next;
    }
}

void sortLinkedList(struct Node *head, int n)
{
    int arr[n];
    int i = 0;
    storeIndored(head, arr, &i);
    mergeSort(arr, 0, n);
    struct Node *temp = head;
    for (int i = 0; i < n; i++)
    {
        temp->val = arr[i];
        temp = temp->next;
    }
}

struct Node* merging(struct Node *head1, struct Node *head2, struct Node *final)
{
    final = createNode(0);
    struct Node *temp = final;
    struct Node *temp1 = head1;
    while (head1 && head2)
    {
        if (head1->val < head2->val)
        {
            final->next = createNode(head1->val);
            final = final->next;
            head1 = head1->next;
        }
        else
        {
            final->next = createNode(head2->val);
            final = final->next;
            head2 = head2->next;
        }
    }
    while (head1)
    {
        final->next = createNode(head1->val);
        final = final->next;
        head1 = head1->next;
    }
    while (head2)
    {
        final->next = createNode(head2->val);
        final = final->next;
        head2 = head2->next;
    }

    return temp->next;
}

int main()
{

    //User input not generated since question mentions to create functions.
    struct Node *head = NULL;
    insert(&head, 1, 30);
    insert(&head, 2, 20);
    insertAsSorted(&head, 15);
    // struct Node*head1;
    // struct Node*head2;
    // FrontBackSplit(head, 3, &head1, &head2);
    // printf("%d", head2->val);
    sortLinkedList(head, 3);

    struct Node *head2 = NULL;
    insert(&head2, 1, 5);
    insert(&head2, 2, 6);
    insertAsSorted(&head2, 7);
    // struct Node*head1;
    // struct Node*head2;
    // FrontBackSplit(head, 3, &head1, &head2);
    // printf("%d", head2->val);
    sortLinkedList(head2, 3);

    struct Node*final;
    final=merging(head, head2, final);
    printf("%d", final->next->next->next->val);

    // printf("%d", head->val);
    return 0;
}