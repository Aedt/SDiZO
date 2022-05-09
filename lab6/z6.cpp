#include <iostream>
#include <fstream>
#include <vector>
#include <string>

using namespace std;

#define N 10

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
        if (k < root->key)
            insertNode(root->left, k);
        else
            insertNode(root->right, k);
    }
}

void printTree(BSTreeNode *n)
{
    if (n != nullptr)
    {
        cout << endl;
        printTree(n->left);
        cout << n->key << "; ";
        printTree(n->right);
    }
    
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
    
    for (int i = 0; i < N; i++)
    {
        insertNode(root, words.at(i));
    }

    printTree(root);

    return 0;
}
