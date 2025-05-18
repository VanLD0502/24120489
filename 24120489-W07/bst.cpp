#include <iostream>
#include <vector>
#include <algorithm>
#include <climits>
using namespace std;

struct NODE{
    int key;
    NODE* p_left;
    NODE* p_right;
};


#include <queue>
NODE* createNode(int data) {
    NODE * tmp = new NODE;
    tmp->key = data;
    tmp->p_left = nullptr;
    tmp->p_right = nullptr;

    return tmp;
} 

void Insert(NODE* &pRoot, int x) {
    if (pRoot == nullptr) {
        pRoot = createNode(x);
        return;    
    }

    if (x > pRoot->key) {
        Insert(pRoot->p_right, x);
    }
    else 
    if (x < pRoot->key) {
        Insert(pRoot->p_left, x);
    }
    else if (x == pRoot->key) {
        std::cout << "Khong can them vi " << x << " da ton tai\n";
        return;
    }
}

NODE* Search(NODE* pRoot, int x) {
    if (pRoot == nullptr) return nullptr;

    if (pRoot->key == x) {
        return pRoot;
    }
    else
    if (x > pRoot->key)  {
        return Search(pRoot->p_right, x);
    }
    else {
        return Search(pRoot->p_left, x);
    }
}

NODE* findLastRightNode(NODE* pRoot) {
    while (pRoot) {
        if (pRoot->p_right == nullptr) {
            break;
        }
        pRoot = pRoot->p_right;
    }

    return pRoot;
}

NODE* removeNode(NODE* &pRoot, int x) {
    if (pRoot == nullptr) {
        return nullptr;
    }

    if (x > pRoot->key) {
        pRoot->p_right = removeNode(pRoot->p_right, x);
    }
    else if (x < pRoot->key) {
        pRoot->p_left = removeNode(pRoot->p_left, x);
    }
    else {
        if (pRoot->p_left == nullptr && pRoot->p_right == nullptr) {
            delete pRoot;
            return nullptr;
        }
        if (pRoot->p_left == nullptr && pRoot->p_right != nullptr) {
            NODE* tmp = pRoot->p_right;
            delete pRoot;
            return tmp;
        }
        else if (pRoot->p_right == nullptr && pRoot->p_left != nullptr) {
            NODE* tmp = pRoot->p_left;
            delete pRoot;
            return tmp;
        }
        else {
            NODE* nodeRight = findLastRightNode(pRoot->p_left);
            pRoot->key = nodeRight->key;
            pRoot->p_left = removeNode(pRoot->p_left, nodeRight->key);
        }
    }
    return pRoot;
}
void Remove(NODE*& pRoot, int x) {
    if (Search(pRoot, x) == nullptr) {
        cout << "Khong tim thay " << x << ", khong xoa duoc\n";
        return;
    }
    pRoot = removeNode(pRoot, x);
}

NODE* createTree(int a[], int n) {
    NODE* pRoot = nullptr;
    for (int i = 0; i < n; i ++) {
        Insert(pRoot, a[i]);
    }

    return pRoot;
}

void removeTree(NODE* &pRoot) {
    if (pRoot == nullptr) return;
    removeTree(pRoot->p_left);
    removeTree(pRoot->p_right);

    if (pRoot != nullptr) {
        delete pRoot;
    }
}

int Height(NODE* pRoot) {
    if (pRoot == nullptr) return -1;
    return 1 + max(Height(pRoot->p_left), Height(pRoot->p_right));
}

int countNode(NODE* pRoot) {
    if (pRoot == nullptr) return 0;
    return 1 + countNode(pRoot->p_left) + countNode(pRoot->p_right);
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



bool isFullTree(NODE* node) {
    if (node == nullptr) return true;
    if ((node->p_left == nullptr && node->p_right != nullptr) ||
        (node->p_left != nullptr && node->p_right == nullptr))
        return false;
    return isFullTree(node->p_left) && isFullTree(node->p_right);
}


bool isFullBST(NODE* pRoot) {
    return isBSTUtil(pRoot, INT_MIN, INT_MAX) && isFullTree(pRoot);
}

int countLess(NODE* pRoot, int x) {
    if (pRoot == nullptr) return 0;
    if (x > pRoot->key) {
        return countNode(pRoot->p_left) + 1 + countLess(pRoot->p_right,x);
    }
    else if (x == pRoot->key) {
        return countNode(pRoot->p_left);
    }
    else {
        return countLess(pRoot->p_left, x);
    }
}

int countGreater(NODE* pRoot, int x) {
    if (pRoot == nullptr) return 0;
    if (x > pRoot->key) {
        return countGreater(pRoot->p_right,x);
    }
    else if (x == pRoot->key) {
        return countNode(pRoot->p_right);
    }
    else {
        return countNode(pRoot->p_right) + 1 + countGreater(pRoot->p_left,x);
    }
}




void Display(vector<int> v) {
    for (int i = 0; i < v.size(); i ++) {
        cout << v[i] << ' ';
    }
    cout << '\n';
}

void PreOrder(NODE* root) {
    if (root == nullptr) return;
    cout << root->key << ' ';
    PreOrder(root->p_left);
    PreOrder(root->p_right);
}