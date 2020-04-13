#include <bits/stdc++.h>

using namespace std;


class fibonacciHeap
{
public:
    int max_deg;
    struct node
    {
        int val;
        int degree;
        bool marked;
        node* left;
        node *right;
        node *child;
        node *parent;
    };
node* minNode;
    fibonacciHeap()
    {
        max_deg = 0;
        minNode = nullptr;
    }
    void insertElement(int val)
    {
        max_deg = max(max_deg, 1);
        node* temp = new node;
        temp->val = val;
        temp->right = temp;
        temp -> left = temp;
        temp->degree = 0;
        temp->marked = false;
        temp->child = nullptr;
        temp->parent = nullptr;
        if (minNode == nullptr)
            minNode = temp;
        else
        {
            temp->right = minNode -> right;
            minNode->right = temp;
            temp->left = minNode;
            temp -> right -> left = temp;
            if (temp->val < minNode -> val)
                minNode = temp;
        }
        
    }
    void unionHeap(fibonacciHeap oth)
    {
        max_deg = max(max_deg, oth.max_deg);
        node* temp1;
        node* temp2;
        temp1 = minNode ->right;
        temp2 = oth.minNode -> left;
        minNode -> right = oth.minNode;
        temp2 -> right = temp1;
        temp1 -> left = temp2;
        oth.minNode -> left = minNode;
        //oth.~fibonacciHeap();
    }

    node* uniteTree(node* node1, node* node2)
    {
        if (node1 -> val > node2 -> val)
            swap(node1, node2);
        node1 -> degree ++ ;
        max_deg = max(max_deg, node1->degree);

        //disconnecting tree 2 from the root list;
        node2 -> right -> left = node2 -> left;
        node2 -> left -> right = node2 -> right;
        //put the parent of node2 to node1 
        node2->parent = node1;
        
        //we put them togheter
        if (node1 -> child == nullptr)
        {
            node1 -> child = node2;
            node2 ->left = node2;
            node2 ->right = node2;
        }
        else
        {
            node* temp = node1 -> child;
            node2 -> right = temp-> right;
            temp -> right -> left = node2;
            node2 -> left = temp;
            temp -> right = node2; 
        }
        return node1;
    }
    
    void deleteNode(node* nod)
    {

        node* minTemp;
        node* temp;
        //a single element left
        if (nod -> right == nod and nod->child == nullptr)
        {
            minNode = nullptr;
            delete nod;
            return;
        }
        //there is a single tree but it haves chlidren, put the minimum there
        if (nod -> right == nod)
        {
            minTemp = nod->child;
        }
        else
        {
        //find the minimum on the other trees
            temp = nod->right;
            minTemp = temp;
             //cout<<"yolo";
            while (temp != nod)
            {
                if (temp->val < minTemp ->val)
                    minTemp = temp;
                temp = temp->right;
            }
             //cout<<"yolo";
        }
        
        if (nod -> child == nullptr)
        {
            nod ->left -> right = nod ->right;
            nod ->right -> left = nod -> left;
            minNode = minTemp;
            delete nod;
            return;
        }
        else
        {
            //deleting the parent for each child
            
            temp = nod -> child -> right;
            if (minTemp -> val > nod->child->val)
                minTemp = nod->child;
            //taking care of the min also.
            //cout<<"yolo";
            while (temp != nod->child)
            {
                if (minTemp -> val > temp ->val)
                    minTemp = temp;
                temp ->parent = nullptr;
                temp = temp->right;
            }
            
            nod->child ->parent = nullptr;
            minNode = minTemp;
           
            if (nod -> right == nod)
            {
                delete nod;
                return;
            }
            //deleting the node
            nod ->left -> right = nod ->right;
            nod ->right -> left = nod -> left;
            temp = nod ->right;
            //puting the other nodes on the root list;
            node* aux = nod->child;
            node* temp1;
            node* temp2;
            temp1 = temp ->right;
            temp2 = aux -> left;
            temp -> right = aux;
            temp2 -> right = temp1;
            temp1 -> left = temp2;
            aux -> left = temp;
            delete nod;
        }
    }

    void consolidate()
    {
        node* lista [max_deg + 10];
        node* aux;
        for (int i = 0; i <= max_deg + 1; i++)
            lista[i] = nullptr;
        node* temp = minNode->right;
        lista[minNode->degree] = minNode;
        while (temp != minNode)
        {
            aux = temp;
            temp = temp->right;
            while (lista[aux->degree] != nullptr)
            {

            }
        }
    }

    void display()
    {
        if (minNode != nullptr)
            cout << minNode->val<<" ";
        else
        {
            cout<<"gol io";
            return;
        }
        node* temp = minNode -> right;
        while (temp != minNode)
        {
            cout << temp->val <<" ";
            temp = temp->right;
        }
        
    }
};


int main()
{
    fibonacciHeap h1;
    h1.insertElement(5);
    h1.insertElement(3);
    h1.insertElement(4);
    h1.insertElement(1);
    h1.uniteTree(h1.minNode, h1.minNode->right);
    h1.uniteTree(h1.minNode ->right, h1.minNode->right->right);
    h1.uniteTree(h1.minNode, h1.minNode->right);
    h1.deleteNode(h1.minNode);
    h1.deleteNode(h1.minNode);
    h1.deleteNode(h1.minNode);
    h1.deleteNode(h1.minNode);
    h1.display();

    return 0;
}