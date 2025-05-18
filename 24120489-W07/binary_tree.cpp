#include <iostream>
#include <vector>

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



void PreOrder(NODE* pRoot, vector<int>& v) {
    if (pRoot == nullptr) {
        return;
    }

    v.push_back(pRoot->key);
    PreOrder(pRoot->p_left, v);
    PreOrder(pRoot->p_right, v);
}

void InOrder(NODE* pRoot, vector<int> & v) {
    if (pRoot == nullptr) {
        return;
    }

    InOrder(pRoot->p_left, v);
    v.push_back(pRoot->key);
    InOrder(pRoot->p_right, v);
}

void PostOrder(NODE* pRoot, vector<int>& v) {
    if (pRoot == nullptr) {
        return;
    }

    PostOrder(pRoot->p_left, v);
    PostOrder(pRoot->p_right, v);
    v.push_back(pRoot->key);
}

vector<int> NLR(NODE* pRoot) {
    vector<int> v;
    PreOrder(pRoot, v);
    return v;
}
vector<int> LNR(NODE* pRoot) {
    vector<int> v;
    InOrder(pRoot, v);
    return v;
}
vector<int> LRN(NODE* pRoot) {
    vector<int> v;
    PostOrder(pRoot, v);
    return v;
}

struct NodeInfo {
    NODE* node;
    int level;
    NodeInfo(NODE* _node, int _level) : node(_node), level(_level) {} 
};

vector<vector<int>> LevelOrder(NODE* pRoot) 
{
    vector<vector<int>> res;
    if (pRoot == nullptr) return res;
    queue<NodeInfo> q;
    q.push(NodeInfo(pRoot, 0));
    while (!q.empty()) {
        NODE* u = q.front().node;
        auto curLevel = q.front().level;
        if (res.size() <= curLevel) {
             res.resize(curLevel + 1);
        }
        res[curLevel].push_back(u->key);
        q.pop();
        if (u->p_left) {
            NodeInfo tmp(u->p_left, curLevel + 1);
            q.push(tmp);
        }

        if (u->p_right) {
            NodeInfo tmp(u->p_right, curLevel + 1);
            q.push(tmp);
        }
    }

    return res;
}

int countNode(NODE* pRoot) {
    if (pRoot == nullptr) return 0;
    return 1 + countNode(pRoot->p_left) + countNode(pRoot->p_right);
}

int sumNode(NODE* pRoot) {
    if (pRoot == nullptr) return 0;
    return pRoot->key + sumNode(pRoot->p_left) + sumNode(pRoot->p_right);
}



NODE* findNode(NODE* pRoot, int value){
    if (pRoot == nullptr) return nullptr;

    if (pRoot->key == value) {
        return pRoot;
    }

    NODE* findL = findNode(pRoot->p_left, value);
    NODE* findR = findNode(pRoot->p_right, value);

    if (findL) return findL;
    if (findR) return findR;
    return nullptr;
}

int cntHeight(NODE* pRoot) {
    if (pRoot == nullptr) return -1;
    return 1 + max(cntHeight(pRoot->p_left), cntHeight(pRoot->p_right));
}

int heightNode(NODE* pRoot, int value) {
    NODE* nodeNeedFine = findNode(pRoot, value);
    return cntHeight(nodeNeedFine);
}

int CntLevel(NODE* pRoot, NODE* p, int level) {
    if (pRoot == nullptr) return -1;
    if (pRoot == p) {
        return level;
    }

    int l = CntLevel(pRoot->p_left, p, level + 1);
    
    if (l != -1) {
        return  l;
    }

    int r = CntLevel(pRoot->p_right, p, level + 1);

    if (r != -1) {
        return r;
    }

    return -1;
    
}

int Level(NODE* pRoot, NODE* p) {
    return CntLevel(pRoot, p, 0);
}

int countLeaf(NODE* pRoot) {
    if (pRoot == nullptr) return 0;

    if (pRoot->p_left == nullptr && pRoot->p_right == nullptr) return 1;

    return countLeaf(pRoot->p_left) + countLeaf(pRoot->p_right);
}

void Display(vector<int> v) {
    for (int i = 0; i < v.size(); i ++) {
        cout << v[i] << ' ';
    }
    cout << '\n';
}

int main() {
    NODE* root = createNode(10);
    root->p_left = createNode(5);
    root->p_left->p_left = createNode(2);
    root->p_left->p_left->p_left = createNode(1);

    root->p_right = createNode(15);
    root->p_right->p_left = createNode(12);
    root->p_right->p_right = createNode(20);
    root->p_right->p_right->p_left = createNode(18);
    vector<int> v = NLR(root);
    Display(v);
    vector<int>v2 = LNR(root);
    Display(v2);
    vector<int> v3 = LRN(root);
    Display(v3);
    auto res = LevelOrder(root);

    for (int i = 0; i < res.size(); i ++) {
        for (auto x : res[i]) {
            cout << x << ' ';
        }
        cout << '\n';
    }
    cout << countNode(root) << '\n';
    cout << sumNode(root) << '\n';
    cout << heightNode(root, 2) << '\n';
    cout << Level(root, root->p_right->p_right->p_left) << '\n';
    cout << countLeaf(root) << '\n';
    return 0;
}