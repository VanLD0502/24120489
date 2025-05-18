#include <iostream>
#include <vector>
#include <climits>
using namespace std;

struct NODE{
    int key;
    NODE* p_left;
    NODE* p_right;
    int height;
};


#include <queue>
NODE* createNode(int data) {
    NODE * tmp = new NODE;
    tmp->key = data;
    tmp->p_left = nullptr;
    tmp->p_right = nullptr;
    tmp->height = 0;
    return tmp;
} 

int Height(NODE* pRoot) {
    return pRoot ? pRoot->height : -1;
}

int getBalanced(NODE* pNode) {
    return pNode? Height(pNode->p_left) - Height(pNode->p_right) : 0;
}

void UpdateHeight(NODE* pNode) {
    pNode->height = 1 + max(Height(pNode->p_left), Height(pNode->p_right));
}

NODE* LeftRotate(NODE* pNode) {
    NODE* y = pNode->p_right;
    NODE* tmp = pNode->p_right->p_left;

    y->p_left = pNode;
    pNode->p_right = tmp;

    UpdateHeight(pNode);
    UpdateHeight(y);

    return y;
}


NODE* RightRotate(NODE* &pNode) {
    NODE* y = pNode->p_left;
    NODE* tmp = y->p_right;

    y->p_right = pNode;
    pNode->p_left = tmp;

    UpdateHeight(pNode);
    UpdateHeight(y);

    return y;
}

void Balance(NODE* &pRoot, int x) {
    UpdateHeight(pRoot);
    int balanced = getBalanced(pRoot);
    //right right
    if (balanced < -1 && x > pRoot->p_right->key) {
        pRoot = LeftRotate(pRoot);
    }
    else if (balanced > 1 && x < pRoot->p_left->key) {
        pRoot = RightRotate(pRoot);
    }
    else if (balanced < -1 &&  x < pRoot->p_right->key) {
        pRoot->p_right = RightRotate(pRoot->p_right);
        pRoot = LeftRotate(pRoot);
    }
    else if (balanced > 1 && x > pRoot->p_left->key) {
        pRoot->p_left = LeftRotate(pRoot->p_left);
        pRoot =RightRotate(pRoot);
    }
}

void Insert(NODE* &pRoot, int x) {
    if (!pRoot) {
        pRoot = createNode(x);
        return;
    }
    if (x > pRoot->key) {
        Insert(pRoot->p_right, x);
    }
    else if (x < pRoot->key) {
        Insert(pRoot->p_left, x);
    }
    else {
        return;
    }

    Balance(pRoot,x);
}

void PreOrder(NODE* root) {
    if (root == nullptr) return;

    cout << root->key << ' ';
    PreOrder(root->p_left);
    PreOrder(root->p_right);
}

NODE* FindRight(NODE* pNode) {
    while (pNode && pNode->p_right) {
        pNode = pNode->p_right;
    }

    return pNode;
}

void Remove(NODE* &pRoot, int x) {
    if (pRoot == nullptr) return;

    if (x < pRoot->key) {
        Remove(pRoot->p_left, x);
    }
    else if (x > pRoot->key) {
        Remove(pRoot->p_right, x);
    }

    else {
        if (pRoot->p_left == nullptr || pRoot->p_right == nullptr) {
            NODE* tmp = pRoot->p_left ? pRoot->p_left : pRoot->p_right;
            delete pRoot;
            pRoot = tmp;
        }
        else {
            NODE* maxRightInLeft = FindRight(pRoot->p_left);
            pRoot->key = maxRightInLeft->key;
            Remove(pRoot->p_left, maxRightInLeft->key);
        }
    }

    if (pRoot) {
        Balance(pRoot,x);
    }
}

bool isBSTUtil(NODE* node, int minVal, int maxVal) {
    if (node == nullptr) return true;

    if (node->key <= minVal || node->key >= maxVal) return false;

    return isBSTUtil(node->p_left, minVal, node->key) &&
           isBSTUtil(node->p_right, node->key, maxVal);
}

bool isBST(NODE* pRoot) {
    return isBSTUtil(pRoot, INT_MIN, INT_MAX);
}

bool checkAVL(NODE* pRoot) 
{
    if (pRoot == nullptr) return true;
    if (abs(getBalanced(pRoot)) > 1) {
        return false;
    }

    return checkAVL(pRoot->p_left) && checkAVL(pRoot->p_right);
}

bool isAVL(NODE* pRoot) {
    return isBST(pRoot) && checkAVL(pRoot);
}



int main() {
    int arr[20] = {
        50, 20, 70, 10, 30,
        60, 80, 25, 5, 15,
        27, 22, 55, 65, 75,
        85, 1, 6, 33, 90
    };
    NODE* root = nullptr;
    for (int i = 0; i < 20; i ++) {
        Insert(root, arr[i]);
    }

    // Remove(root, 20);
    // Remove(root,27);
    PreOrder(root);
    cout << '\n';
    cout << isAVL(root);
    return 0;
}