#include <iostream>
#include "bits/stdc++.h"
using namespace std;

class node
{
public:
    int data;
    node *left;
    node *right;

    node(int x)
    {
        left = NULL;
        right = NULL;
        data = x;
    }
};

node *RsearchBST(node *root, int key)
{ // using tail recursion
    if (root == NULL)
        return NULL;
    if (root->data == key)
        return root;
    else if (root->data > key)
        return RsearchBST(root->left, key);
    else
        return RsearchBST(root->right, key);
}


node *IsearchBST(node *root, int key)
{ // iterative search
    while (root != NULL)
    {
        if (root->data == key)
            return root;
        else if (root->data > key)
            root = root->left;
        else
            root = root->right;
    }

    return NULL;
}

void InsertBST(node* &root, int key)
{
    
    if (root == NULL)
    {
        node *p = new node(key);
        root = p;
        return;
    }
    node *temp = root;
    node *back;
    while (temp != NULL)
    {
        if (temp->data == key)
        {
            cout << "element already present";
            return;
        }
        else if (temp->data > key)
        {
            back = temp;
            temp = temp->left;
        }
        else
        {
            back = temp;
            temp = temp->right;
        }
    }
    if (back->data > key)
    {
        back->left = new node(key);
        cout << key << " inserted on the left side of node " << back->data << endl;
    }
    else
    {
        back->right = new node(key);
        cout << key << " inserted on the right side of node " << back->data << endl;
    }
}

void inorder(node *root)
{

    if (root)
    {

        inorder(root->left);
        cout << root->data << " ";
        inorder(root->right);
    }
}


void pre(node *root)
{

    if (root)
    {
        cout << root->data << " ";
        pre(root->left);
        pre(root->right);
    }
}



//
node *inorderSucc(node *root)
{
    node *curr = root;
    while (curr && curr->left != NULL)
        curr = curr->left;

    return curr;
}

node *deleteBST(node *root, int key)
{

    // first searching the key
    if (key < root->data)
    {
        root->left = deleteBST(root->left, key);
    }
    else if (key > root->data)
    {
        root->right = deleteBST(root->right, key);
    }
    else
    {
        if (root->left == NULL)
        { // case 1 and 2 when there is 1 or 0 children
            node *temp = root->right;
            free(root);
            return temp;
        }
        else if (root->right == NULL)
        {
            node *temp = root->left;
            free(root);
            return temp;
        }
        // case 3 when 2 children present
        node *temp = inorderSucc(root->right);
        root->data = temp->data;                           // changing data value to inorder ducc value
        root->right = deleteBST(root->right, temp->data);  // deleting the last value (onordersucc)
    }
    return root;
}
//




node* constructBST(int preorder[], int* index, int key, int min, int max, int n){   //construct BST from given preorder

    if(*index>n)
        return NULL;

    node* root = NULL;
    if(key>min && key<max){
        root = new node(key);
        *index = *index + 1;
        if(*index < n){
            root->left = constructBST(preorder, index, preorder[*index], min, key, n);
        }
        if(*index<n){
            root->right = constructBST(preorder, index, preorder[*index], key, max, n);
        }
    }

    return root;
}



bool isBST(node* root, node* min=NULL, node* max=NULL){
    if(root == NULL )
        return true;

    if(min!=NULL && root->data <= min->data)
        return false;
    if(max!=NULL && root->data >= max->data)
        return false;
    
    bool leftValid = isBST(root->left, min, root);
    bool rightValid = isBST(root->right, root, max);

    return leftValid and rightValid;

}



int main()
{   
    node *root = NULL;
    InsertBST(root, 10);                            //      10
    InsertBST(root, 5);                             //    5    20      
    InsertBST(root, 20);                            //      8     30
    InsertBST(root, 8);                             //
    InsertBST(root, 30);                            //

    inorder(root);
    cout << endl;

    node *k = IsearchBST(root, 41);
    if (k != NULL)
        cout << k->data;
    else
        cout << "not found" << endl;

    InsertBST(root, 41);
    k = IsearchBST(root, 41);
    if (k != NULL)
        cout << k->data;
    else
        cout << "not found" << endl;
    root = deleteBST(root,10);
    inorder(root);
    cout<<endl;
    int preorder[] = {10, 2, 1, 13, 11};
    int n=5;
    int index = 0;
    root = constructBST(preorder, &index, preorder[0], INT_MIN, INT_MAX, n);
    pre(root);

    cout<<isBST(root, NULL, NULL);

    return 0;
}
