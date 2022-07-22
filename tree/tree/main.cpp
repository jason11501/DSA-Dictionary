//
//  main.cpp
//  19127517
//
//  Created by jason on 15/07/2022.
//

#include <iostream>
#include<fstream>
#define num 176011
using namespace std;
#include <time.h>

struct Node
{
    string key;
    Node *left;
    Node *right;
    int height;
};

Node* createNode(string key)
{
    Node* node = new Node();
    node->key = key;
    node->left = NULL;
    node->right = NULL;
    node->height = 1; // new node is initially
                      // added at leaf
    return(node);
}

struct Array
{
    string* arr;
    int size;

    Array()
    {
        arr = nullptr;
        size = 0;
    }

    Array(int newSize)
    {
        size = newSize;
        arr = new string[size];
    }

    string& operator[](const int& index)
    {
        return arr[index];
    }
    ~Array()
    {
        if (arr)
            delete[] arr;
    }
};

void LNR(Node* &pRoot)
{
    if(pRoot == NULL)
        return;
    else
    {
        cout<<pRoot->key<<'\n';
        LNR(pRoot->left);
        
        LNR(pRoot->right);
    }
}

void DeleteTree(Node* &root)
{
    if (root)
    {
        DeleteTree(root->left);
        DeleteTree(root->right);
        delete root;
    }
}

int height(Node *N)
{
    if (N == NULL)
        return 0;
    return N->height;
}

Node* rightRotate(Node *&y)
{
    Node *x = y->left;
    Node *T2 = x->right;
 
    // Perform rotation
    x->right = y;
    y->left = T2;
 
    // Update heights
    y->height = max(height(y->left),
                    height(y->right)) + 1;
    x->height = max(height(x->left),
                    height(x->right)) + 1;
 
    // Return new root
    return x;
}
 
// A utility function to left
// rotate subtree rooted with x
// See the diagram given above.
Node* leftRotate(Node *&x)
{
    Node *y = x->right;
    Node *T2 = y->left;
 
    // Perform rotation
    y->left = x;
    x->right = T2;
 
    // Update heights
    x->height = max(height(x->left),
                    height(x->right)) + 1;
    y->height = max(height(y->left),
                    height(y->right)) + 1;
 
    // Return new root
    return y;
}
 
// Get Balance factor of node N
int getBalance(Node *N)
{
    if (N == NULL)
        return 0;
    return height(N->left) - height(N->right);
}
 
// Recursive function to insert a key in the subtree rooted with node and returns the new root of the subtree.
Node* insert(Node*& node, string key)
{
    /* 1. Perform the normal BST insertion */
    if (node == NULL)
    {
        return createNode(key);
    }
 
    if (key < node->key)
        node->left = insert(node->left, key);
    else if (key > node->key)
        node->right = insert(node->right, key);
    else // Equal keys are not allowed in BST
        return node;
 
    /* 2. Update height of this ancestor node */
    node->height = 1 + max(height(node->left),
                        height(node->right));
 
    /* 3. Get the balance factor of this ancestor
        node to check whether this node became
        unbalanced */
    int balance = getBalance(node);
 
    // If this node becomes unbalanced, then there are 4 cases
 
    // Left Left Case
    if (balance > 1 && key < node->left->key)
        return rightRotate(node);
 
    // Right Right Case
    if (balance < -1 && key > node->right->key)
        return leftRotate(node);
 
    // Left Right Case
    if (balance > 1 && key > node->left->key)
    {
        node->left = leftRotate(node->left);
        return rightRotate(node);
    }
 
    // Right Left Case
    if (balance < -1 && key < node->right->key)
    {
        node->right = rightRotate(node->right);
        return leftRotate(node);
    }
 
    /* return the (unchanged) node pointer */
    return node;
}

string searchNode(Node* pRoot, string wordLookUp)
{
    if(pRoot == NULL)
        return "";
    
    string pKey = pRoot->key.substr(0, pRoot->key.find(','));
    if(pKey == wordLookUp)
    {
        string temp = pRoot->key;
        string word = temp.substr(0, temp.find(','));
        temp = temp.erase(0, word.length() + 1);
        string count = temp.substr(0, temp.find(','));
        temp = temp.erase(0, count.length() + 1);
        string POS = temp.substr(0, temp.find(','));
        temp = temp.erase(0, POS.length() + 1);
        string definition = temp;
        return definition;
    }
    else
    {
        if(pKey > wordLookUp)
            return searchNode(pRoot->left, wordLookUp);
        return searchNode(pRoot->right, wordLookUp);
    }
    return "";
}

string Input()
{
    string input;
    cout << "Input : \n";
    cin >> input;
    
    return input;
}

void editMeaning(Node* &pRoot, string wordLookUp)
{
    if(pRoot == NULL)
        return;
    if(pRoot->key.substr(0, pRoot->key.find(',')) == wordLookUp)
    {
        pRoot->key = Input();
        return;
    }
    else
    {
        if(pRoot->key.substr(0, pRoot->key.find(',')) > wordLookUp)
            searchNode(pRoot->left, wordLookUp);
        searchNode(pRoot->right, wordLookUp);
    }
}

Node* minValueNode(Node* node)
{
    Node* current = node;
 
    /* loop down to find the leftmost leaf */
    while (current->left != NULL)
        current = current->left;
 
    return current;
}
 
// Recursive function to delete a node with given key from subtree with given root. It returns root of the modified subtree.
Node* deleteNode(Node* &root, string key)
{
     
    // STEP 1: PERFORM STANDARD BST DELETE
    if (root == NULL)
        return root;
 
    // If the key to be deleted is smaller than the root's key, then it lies in left subtree
    if ( key < root->key )
        root->left = deleteNode(root->left, key);
 
    // If the key to be deleted is greater than the root's key, then it lies in right subtree
    else if( key > root->key )
        root->right = deleteNode(root->right, key);
 
    // if key is same as root's key, then
    // This is the node to be deleted
    else
    {
        // node with only one child or no child
        if( (root->left == NULL) ||
            (root->right == NULL) )
        {
            Node *temp = root->left ?
                         root->left :
                         root->right;
 
            // No child case
            if (temp == NULL)
            {
                temp = root;
                root = NULL;
            }
            else // One child case
            *root = *temp; // Copy the contents of the non-empty child
            free(temp);
        }
        else
        {
            // node with two children: Get the inorder
            // successor (smallest in the right subtree)
            Node* temp = minValueNode(root->right);
 
            // Copy the inorder successor's
            // data to this node
            root->key = temp->key;
 
            // Delete the inorder successor
            root->right = deleteNode(root->right,
                                     temp->key);
        }
    }
 
    // If the tree had only one node
    // then return
    if (root == NULL)
    return root;
 
    // STEP 2: UPDATE HEIGHT OF THE CURRENT NODE
    root->height = 1 + max(height(root->left),
                           height(root->right));
 
    // STEP 3: GET THE BALANCE FACTOR OF
    // THIS NODE (to check whether this
    // node became unbalanced)
    int balance = getBalance(root);
 
    // If this node becomes unbalanced,
    // then there are 4 cases
 
    // Left Left Case
    if (balance > 1 && getBalance(root->left) >= 0)
        return rightRotate(root);
 
    // Left Right Case
    if (balance > 1 && getBalance(root->left) < 0)
    {
        root->left = leftRotate(root->left);
        return rightRotate(root);
    }
 
    // Right Right Case
    if (balance < -1 && getBalance(root->right) <= 0)
        return leftRotate(root);
 
    // Right Left Case
    if (balance < -1 && getBalance(root->right) > 0)
    {
        root->right = rightRotate(root->right);
        return leftRotate(root);
    }
 
    return root;
}

void OutFileFromTree(fstream &out, Node* &pRoot)
{
    if(pRoot == NULL)
        return;
    else
    {
        out << pRoot->key << '\n';
        OutFileFromTree(out, pRoot->left);
        OutFileFromTree(out, pRoot->right);
    }
}

void OutFileFromArray(fstream &out, Array &a)
{
    for (int i = 0; i < num; i++) {
        if (a[i].substr(0, a[i].find(',')) == "#NAME?")
        {
            continue;
        }
        else
            out << a[i] << ' ';
    }
}

int main() {
//  TREE
    Array arr(num);
    Node* tree;
    std::fstream in("/Users/jason/Downloads/19127517/19127517/OPTED-Dictionary.csv");
    if (in)
    {
        for (int i=0; i<num; i++)
            getline(in, arr[i], '\n');
    }in.close();

    //clean word #NAME? in old .csv
    fstream out("/Users/jason/Downloads/19127517/19127517/clean.csv");
    if (out)
        OutFileFromArray(out, arr);
    out.close();

//load content from a file
    fstream inn("/Users/jason/Downloads/19127517/19127517/clean.csv");
    if (inn)
    {
        for (int i=1; i<num; i++)
        {
            getline(inn, arr[i], '\n');
            if (i == 1) {
                tree = createNode(arr[i]);
            }
            else
                insert(tree, arr[i]);
        }
    }inn.close();

    clock_t start, end;
    start = clock();

// Look up
    string searchWord = Input();
    cout<< "Meaning:" << '\n' <<searchNode(tree, searchWord);
//Add
    string inputVocabulary = Input();
    insert(tree, inputVocabulary);

//Edit Meaning
    string wordLookUp = Input();
    editMeaning(tree, wordLookUp);

//Delete
    string wordDelete = Input();
    deleteNode(tree, wordDelete);

//Save file
    fstream outt("/Users/jason/Downloads/19127517/19127517/output.csv");
    if (outt)
        OutFileFromTree(outt, tree);
    outt.close();
    
    end = clock();
    cout<<(double(end - start) * 1000) / double(CLOCKS_PER_SEC)<<endl;
    
    DeleteTree(tree);
    
    return 0;
}
