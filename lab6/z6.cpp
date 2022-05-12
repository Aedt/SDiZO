#include <iostream>
#include <fstream>
#include <vector>
#include <string>

using namespace std;

#define N 10
// BST
struct BSTreeNode
{
    string key;
    struct BSTreeNode *left{};
    struct BSTreeNode *right{};
};

void insertNode(BSTreeNode *&root, const string &k)
{
    if (root == nullptr)
    {
        root = new BSTreeNode;
        root->key = k;
        root->left = nullptr;
        root->right = nullptr;
    }
    else
    {
        if (k.compare(root->key) < 0)
            insertNode(root->left, k);
        else
            insertNode(root->right, k);
    }
}

BSTreeNode *findMaximumKey(BSTreeNode *ptr)
{
    while (ptr->right != nullptr)
    {
        ptr = ptr->right;
    }
    return ptr;
}

void deleteNode(BSTreeNode *&root, const string &k)
{
    // base case: the key is not found in the tree
    if (root == nullptr)
    {
        return;
    }

    // if the given key is less than the root node, recur for the left subtree
    if (k.compare(root->key) < 0)
    {
        deleteNode(root->left, k);
    }

    // if the given key is more than the root node, recur for the right subtree
    else if (k.compare(root->key) > 0)
    {
        deleteNode(root->right, k);
    }

    // key found
    else
    {
        // Case 1: node to be deleted has no children (it is a leaf node)
        if (root->left == nullptr && root->right == nullptr)
        {
            // deallocate the memory and update root to null
            delete root;
            root = nullptr;
        }

        // Case 2: node to be deleted has two children
        else if (root->left && root->right)
        {
            // find its inorder predecessor node
            BSTreeNode *predecessor = findMaximumKey(root->left);

            // copy value of the predecessor to the current node
            root->key = predecessor->key;

            // recursively delete the predecessor. Note that the
            // predecessor will have at most one child (left child)
            deleteNode(root->left, predecessor->key);
        }

        // Case 3: node to be deleted has only one child
        else
        {
            // choose a child node
            BSTreeNode *child = (root->left) ? root->left : root->right;
            BSTreeNode *curr = root;

            root = child;

            // deallocate the memory
            delete curr;
        }
    }
}

void printTreeBST(BSTreeNode *n)
{
    if (n != nullptr)
    {

        printTreeBST(n->left);
        cout << n->key << "; ";
        printTreeBST(n->right);
    }
}

void saveTreeBST(BSTreeNode *n, FILE *outFile)
{
    if (n != nullptr)
    {
        saveTreeBST(n->left, outFile);
        fprintf(outFile, "%s\n", n->key.c_str());
        saveTreeBST(n->right, outFile);
    }
}

void saveBST(BSTreeNode *n)
{
    FILE *outFile = fopen("words_out_BST.txt", "w");
    saveTreeBST(n, outFile);
    fclose(outFile);
}


int main()
{
    vector<string> words;
    ifstream file;
    file.open("shuffled_words_alpha.txt");
    if (!file.is_open())
    {
        cout << "File error" << endl;
        return 1;
    }
    string word;
    while (file >> word)
        words.push_back(word);

    BSTreeNode *root = nullptr;

    // for (int i = 0; i < N; i++)
    // {
    //     insertNode(root, words.at(i));
    // }
    for (const auto &item : words)
    {
        insertNode(root, item);
    }

    // printTree(root);

    for (int i = 370104; i > (370104 - 17400); i--)
    {
        deleteNode(root, words.at(i));
    }
    saveBST(root);

    return 0;
}
