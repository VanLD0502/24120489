#include <iostream>
#include <vector>
#include <fstream>
#include <algorithm>
#include <stack>
#include <climits>
using namespace std;

vector<vector<int>> convertMatrixToList(const string &filename)
{

    ifstream in(filename);
    vector<vector<int>> adj;
    if (!in)
    {
        cout << "Khong ton tai " << filename << '\n';
        return {};
    }
    int n;
    in >> n;
    adj.resize(n);
    for (int i = 0; i < n; i++)
    {
        for (int j = 0; j < n; j++)
        {
            int x;
            in >> x;
            if (x)
                adj[i].push_back(j);
        }
    }

    return adj;
}

vector<vector<int>> convertListToMatrix(const string &filename)
{
    ifstream in(filename);

    if (!in)
    {
        cout << "Loi khong mo file";
        return vector<vector<int>>();
    }

    int n;
    in >> n;
    vector<vector<int>> matrix(n);
    for (int i = 0; i < n; i++)
    {
        int m;
        in >> m;
        matrix[i].resize(n);
        for (int j = 0; j < m; j++)
        {
            int x;
            in >> x;
            matrix[i][x] = 1;
        }
    }

    return matrix;
}

bool isDirected(const vector<vector<int>> &adjMatrix)
{
    int n = adjMatrix.size();
    for (int i = 0; i < n; i++)
    {
        for (int j = 0; j < n; j++)
        {
            if (adjMatrix[i][j] != adjMatrix[j][i])
                return true;
        }
    }

    return false;
}

int countVertices(const vector<vector<int>> &adjMatrix)
{
    return adjMatrix.size();
}

int countEdges(const vector<vector<int>> &adjMatrix)
{
    int n = adjMatrix.size();
    int cnt = 0;
    for (int i = 0; i < n; i++)
    {
        for (int j = 0; j < n; j++)
        {
            if (adjMatrix[i][j] == 1)
                cnt++;
        }
    }
    if (!isDirected(adjMatrix))
        return cnt / 2;
    return cnt;
}

vector<int> getIsolatedVertices(const vector<vector<int>> &adjMatrix)
{
    vector<int> v;
    for (int i = 0; i < adjMatrix.size(); i++)
    {
        bool ok = true;
        for (int j = 0; j < adjMatrix.size(); j++)
        {
            if (adjMatrix[i][j] || adjMatrix[j][i])
            {
                ok = false;
                break;
            }
        }
        if (ok)
        {
            v.push_back(i);
        }
    }

    return v;
}

bool isCompleteGraph(const vector<vector<int>> &adjMatrix)
{
    int n = adjMatrix.size();

    for (int i = 0; i < n; i++)
    {
        for (int j = 0; j < n; j++)
        {
            if (i == j) continue;
            if (adjMatrix[i][j] == 0)
                return false;
        }
    }

    return true;
}

vector<int> color;

bool dfsBipartite(int u, int parent, const vector<vector<int>>& A) {
    int n = A.size();
    for (int v = 0; v < n; ++v) {
        if (!A[u][v] || v == parent) continue; 
        if (color[v] == 0) {
            color[v] = 3 - color[u];
            if (!dfsBipartite(v, u, A)) return false;
        }
        else if (color[v] == color[u]) {
            return false;
        }
    }
    return true;
}

bool isBipartite(const vector<vector<int>>& A) {
    int n = A.size();
    color.assign(n, 0);
    for (int i = 0; i < n; ++i) {
        if (color[i] == 0) {
            color[i] = 1;
            if (!dfsBipartite(i, -1, A))
                return false;
        }
    }
    return true;
}


bool isCompleteBipartite(const vector<vector<int>>& A) {
    if (!isBipartite(A)) return false;
    int n = A.size();
    vector<int> p1, p2;
    for (int i = 0; i < n; ++i)
        (color[i]==1 ? p1 : p2).push_back(i);
    for (int u : p1)
        for (int v : p2)
            if (!A[u][v]) return false;
    return true;
}

vector<vector<int>> convertToUndirectedGraph(const vector<vector<int>>& adjMatrix) {
    vector<vector<int>> v = adjMatrix;
    int n = adjMatrix.size();
    for (int i = 0; i < n; i ++) {
        for (int j = i + 1; j < n; j ++) {
            if (adjMatrix[i][j] == 1 || adjMatrix[j][i] == 1) {
                v[i][j] = v[j][i] = 1;
            }
        }
    }

    return v;
}

vector<vector<int>> getComplementGraph(const vector<vector<int>>& adjMatrix) {
    vector<vector<int>> v = adjMatrix;

    int n = adjMatrix.size();
    for (int i = 0; i < n; i ++) {
        for (int j = 0; j < n; j ++) {
            if (i == j) continue;
            v[i][j] = v[j][i] = (adjMatrix[i][j] == 1) ? 0 : 1;
        }
    }
    return v;
}

// Chu trình mà đi qua mỗi cạnh đúng một lần. và kết thúc tại điểm bắt đầu.
//Có chu trình euler nếu :
// Các đỉnh bậc khác 0 của đồ thị liên thông với nhau.
//Tất cả các đỉnh của đồ thị có bậc chẵn.
vector<int> findEulerCycle(const vector<vector<int>>& adjMatrix) {
    int n = adjMatrix.size();
    bool directed = isDirected(adjMatrix);

    // Kiểm tra bậc
    if (directed) {
        for (int i = 0; i < n; ++i) {
            int outDeg = 0, inDeg = 0;
            for (int j = 0; j < n; ++j) {
                outDeg += adjMatrix[i][j];
                inDeg  += adjMatrix[j][i];
            }
            if (inDeg != outDeg) return {};
        }
    } else {
        for (int i = 0; i < n; ++i) {
            int deg = 0;
            for (int j = 0; j < n; ++j)
                deg += adjMatrix[i][j];
            if (deg % 2 != 0) return {};
        }
    }

    // Chọn đỉnh bắt đầu
    int start = -1;
    for (int i = 0; i < n; ++i) {
        int deg = 0;
        for (int j = 0; j < n; ++j)
            deg += adjMatrix[i][j];
        if (deg > 0) {
            start = i;
            break;
        }
    }
    if (start == -1) return {};


    vector<vector<int>> graph = adjMatrix;
    stack<int> s;
    vector<int> res;
    s.push(start);

  
    while (!s.empty()) {
        int u = s.top();
        bool found = false;
        for (int v = 0; v < n; ++v) {
            if (graph[u][v] > 0) {
                s.push(v);
                graph[u][v]--;
                if (!directed)
                    graph[v][u]--;
                found = true;
                break;
            }
        }
        if (!found) {
            res.push_back(u);
            s.pop();
        }
    }

    
    for (int i = 0; i < n; ++i)
        for (int j = 0; j < n; ++j)
            if (graph[i][j] > 0)
                return {};

 
    reverse(res.begin(), res.end());
    return res;
}


//Đường đi Euler là một đường đi qua mỗi cạnh đúng 1 lần (không nhất thiết phải quay lại điểm bắt đầu).
/* 
    Các đỉnh có bật khác 0 của đồ thị liên thông với nhau.
    Đồ thị có 0 hoặc 2 đỉnh có bậc lẻ, truong trường hợp có 2 đỉnh bậc lẻ thì đường đi sẽ bắt đầu từ đỉnh thứ nhất đến đỉnh thứ hai.
*/

/*
    Đồ thị có hướng 
    - Các đỉnh có bậc khác 0 cùng thuộc 1 thành phần liên thông.

    - Mọi đỉnh của đồ thị đều có bán bậc ra bằng bán bậc vào.

    Đường đi
    -Các đỉnh có bậc khác 0 cùng thuộc 1 thành phần liên thông.
    - TỒN TẠI U deg+(u) - deg-(u) = 1 và deg-(v) - deg+(v) = 1, mọi đỉnh còn lại đều có bán bậc vào bằng bán bậc ra. Đường đi bắt đầu từ u->v;
*/

void dfs(int u, const vector<vector<int>>& adjMatrix, vector<vector<int> > & tree, vector<bool>& visited) {
    visited[u] = 1;

    for (int v = 0; v < adjMatrix.size(); v ++) {
        if (adjMatrix[u][v] && !visited[v]) {
            tree[u][v] = tree[v][u] = 1;
            dfs(v, adjMatrix, tree, visited);
        }
    }
}

vector<vector<int>> dfsSpanningTree(const vector<vector<int>>& adjMatrix, int start) {
    int n = adjMatrix.size();
    vector<vector<int>> tree(n, vector<int>(n, 0));
    vector<bool> visited(n, 0);
    dfs(start, adjMatrix, tree, visited);

    return tree;
}
#include <queue>
vector<vector<int>> bfsSpanningTree(const vector<vector<int>>& adjMatrix, int start) {
    int n = adjMatrix.size();
    vector<vector<int>> tree(n, vector<int>(n, 0));
    vector<bool> visited(n, 0);

    queue<int> q;
    q.push(start);
    visited[start] = 1;
    while (!q.empty()) {
        int u = q.front();
        q.pop();

        for (int v = 0; v < adjMatrix.size(); v ++) {
            if (adjMatrix[u][v] && !visited[v]) {
                visited[v] = 1;
                tree[u][v] = tree[v][u] = 1;
                q.push(v);
            }
        }
    }

    return tree;
}

void dfsConnected(int u, vector<bool>& visited, const vector<vector<int>>& adjMatrix) {
    visited[u] = 1;

    for (int v = 0; v < adjMatrix.size(); v ++) {
        if (adjMatrix[u][v] && !visited[v]) {
            dfsConnected(v, visited, adjMatrix);
        }
    }
}

bool isConnected(int u, int v, const vector<vector<int>>& adjMatrix) {
    vector<bool> visited(adjMatrix.size(), 0);
    dfsConnected(u, visited, adjMatrix);
    bool tmp1 = visited[v];
    for (int i = 0; i < adjMatrix.size(); i ++) visited[i] = 0;
    dfsConnected(v, visited, adjMatrix);
    return tmp1 && visited[u];
}

vector<int> dijkstra(int start, int end, const vector<vector<int>>& adjMatrix) {
    int n = adjMatrix.size();
    vector<int> d(n, INT_MAX);
    priority_queue<pair<int, int>, vector<pair<int,int> >, greater<pair<int, int> > >  q;
    q.push({0, start});
    d[start] = 0;
    vector<int> parent(n, -1);
    while (!q.empty()) {
        int u = q.top().second;
        int w = q.top().first;

        q.pop();
        if (w > d[u]) continue;

        if (u == end) break;
        for (int v = 0; v < n; v ++) {
            if (adjMatrix[u][v] && d[v] > d[u] + adjMatrix[u][v]) {
                d[v] = d[u] + adjMatrix[u][v];
                parent[v] = u;
                q.push({d[v], v});
            }
        }
    }

    if (d[end] == INT_MAX) {
        return {};
    }


    vector<int> res;
    for (int tmp = end; tmp != -1; tmp = parent[tmp]) {
        res.push_back(tmp);
    }
    reverse(res.begin(), res.end());
    return res;
}

// vector<int> bellmanFord(int start, int end, const vector<vector<int>>& adjMatrix) {
    
//     int n = adjMatrix.size();

//     vector<vector<int>> d(n, vector<int>(n, INT_MAX));


//     for (int i = 0; i < n; i ++) {
//         d[i][i] = 0;
//     }

//     vector<int> par(n, -1);
//     for (int i = 0; i < n; i ++) {
//         for (int j = i + 1; j < n; j ++) {
//             for (int k = 0; k < n; k ++) {
//                 if (d[i][j] > d[i][k] + d[k][j]) {
//                     d[i][j] = d[i][k] + d[k][j];

//                     par[j] = i;
//                 }
//             }
//         }
//     }

//     vector<int> res;
//     for (int tmp = end; tmp != -1; tmp = par[tmp]) {
//         res.push_back(tmp);
//     }

//     reverse(res.begin(), res.end());

//     return res;

// }

vector<int> bellmanFord(int start, int end, const vector<vector<int>>& adjMatrix) {

    int n = adjMatrix.size();
    vector<int> d(n,INT_MAX);
    d[start] = 0;
    vector<int> par(n, -1);
    for (int times = 0; times < n - 1; times ++) {
        for (int u = 0; u < n; u ++) {
            for (int v = 0; v < n; v ++) {
                if (adjMatrix[u][v] != 0 && d[u] != INT_MAX && d[v] > d[u] + adjMatrix[u][v]) {
                    d[v] = d[u] + adjMatrix[u][v];
                    par[v] = u;
                }
            }
        }
    }


    for (int u = 0; u < n; u ++) {
        for (int v = 0; v < n; v ++) {
            if (adjMatrix[u][v] != 0 && d[u] != INT_MAX && d[v] > d[u] + adjMatrix[u][v]) {
                return {};
            }
        }
    }

    if (d[end] == INT_MAX) {
        return {};
    }
    
    vector<int> res;
    for (int tmp = end; tmp != -1; tmp = par[tmp]) {
        res.push_back(tmp);
    }
    reverse(res.begin(), res.end());    
    
    return res;
}
