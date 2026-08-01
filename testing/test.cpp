#include <iostream>
using namespace std;

struct Node {
    int data;
    Node* left;
    Node* right;
};

class BST
{
    BST() : root(nullptr) {}

    Node* getNewNode(int x)
    {
        Node* temp = new Node();
        temp->data = x;
        temp->left = nullptr;
        temp->right = nullptr;

        return temp;
    }

    void insert(Node** node, int x)
    {
        while(*node){
            if(x <= (*node)->data){
                node = &((*node)->left);
            }
            else{
                node = &((*node)->right);
            }
        }
        *node = getNewNode(x);     
    }

 
private:
    Node* root;
};


int main()
{

}