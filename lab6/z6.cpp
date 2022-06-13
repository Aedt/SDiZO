#include <iostream>
#include <fstream>
#include <vector>
#include <math.h> 
#include <time.h>
#include <string>

using namespace std;

#define NN 10
// BST
struct BSTreeNode
{
    int key;
    struct BSTreeNode *left{};
    struct BSTreeNode *right{};
};

void insertNode(BSTreeNode *&root, const int &k)
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
        if (k < (root->key))
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

void deleteNode(BSTreeNode *&root, const int &k)
{
    // base case: the key is not found in the tree
    if (root == nullptr)
    {
        return;
    }

    // if the given key is less than the root node, recur for the left subtree
    if (k < (root->key))
    {
        deleteNode(root->left, k);
    }

    // if the given key is more than the root node, recur for the right subtree
    else if (k > (root->key))
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
        fprintf(outFile, "%d\n", n->key);
        saveTreeBST(n->right, outFile);
    }
}

void saveBST(BSTreeNode *n)
{
    FILE *outFile = fopen("out_BST.txt", "w");
    saveTreeBST(n, outFile);
    fclose(outFile);
}

int saveTime(int in, float procent, double czasTworzenia, double czasUsuwania){
    in++;
    FILE *file;
    char* buff;
    file = fopen("czasy.ini", "a");
    if (file==NULL)
    {
        cout << "Blad pliku 'czasy.txt'" << endl;
        return 1;
    }

    string tekst;
    tekst = "Wielkosc drzewa: " + to_string(in) + "; usuniety procent: " 
            + to_string(procent) + "; czas tworzenia drzewa: " + to_string(czasTworzenia) 
            + "; czas usuwania: " + to_string(czasUsuwania) + "\n";
    cout << tekst << endl;
    buff = &tekst[0];
    fputs(buff, file);
    fclose(file);

}


int main()
{
    clock_t t,t2;
    vector<int> words;
    ifstream file;
    int in;
    float procent;
    


    file.open("liczby_shuf.txt");
    if (!file.is_open())
    {
        cout << "Blad pliku z danymi" << endl;
        return 1;
    }
    int word;
    while (file >> word)
        words.push_back(word);

    BSTreeNode *root = nullptr;

    cout << "wielkosc drzewa (max 500 000): ";
    cin >> in;
    in--;
    cout << "procent drzewa do usuniecia(0-1): ";
    cin >> procent;

    t = clock();
    for (int i = 0; i < in; i++)
    {
        insertNode(root, words.at(i));
    }
    t = clock() - t;
    double czasTworzenia = ((double)t) / CLOCKS_PER_SEC;
    // for (const auto &item : words)
    // {
    //     insertNode(root, item);
    // }

    // printTreeBST(root);
    t2 = clock();
    for (int i = in; i >= (in - floor(in*procent)); i--)
    {
        deleteNode(root, words.at(i));
    }
    t2 = clock() - t2;
    double czasUsuwania = ((double)t2) / CLOCKS_PER_SEC;

    saveBST(root);
    saveTime(in, procent, czasTworzenia, czasUsuwania);
    getchar();
    getchar();
    return 0;
}
