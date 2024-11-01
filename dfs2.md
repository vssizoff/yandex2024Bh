# DFS 2

## Condensation

А; B - компоненты сильной связности

из A в B есть хотябы одно ребро

$$
max(tout_A) > max(tout_B)
$$

Транспанированный граф: если $v$ -> $u$ в обычном, то $u$ -> $v$

$reversedGraph$ - транспонированный

```cpp
void topSort(int vertex, const Vector<Vector<int>>& graph, Vector<bool> &used, Vector<int>& order) {
    used[vertex] = true;
    for (auto to : graph[vertex]) {
        if (!used[to]) topSort(to, graph, used, order);
    }
    order.push_back(vertex);
}

void dfs(int vertex, int color, const Vector<Vector<int>>& graph, Vector<bool>& used, Vector<int>& colors) {
    used[vertex] = true;
    colors[vertex] = color;
    for (auto to : graph[vertex]) {
        if (!used[to]) dfs(to, color, graph, used, colors);
    }
}

int condensation(const Vector<Vector<int>>& graph, Vector<int>& colors) {
    Vector<bool> used(graph.size());
    Vector<int> order;
    for (int i = 0; i < graph.size(); ++i) {
        if (!used[i]) topSort(i, graph, used, order);
    }
    std::ranges::reverse(order);
    used.assign(order.size(), false);
    Vector<Vector<int>> reversedGraph(graph.size());
    for (int from = 0; from < graph.size(); ++from) {
        for (auto to : graph[from]) {
            reversedGraph[to].push_back(from);
        }
    }
    int color = 0;
    for (auto vertex : order) {
        if (!used[vertex]) dfs(vertex, color++, reversedGraph, used, colors);
    }
    return color;
}

int n, m; cin >> n >> m;
Vector<Vector<int>> graph(n);
Vector<int> colors(n);
for (int i = 0; i < m; i++) {
    int from, to; cin >> from >> to;
    graph[from].push_back(to);
}
condensation(); // components is count of components
for (auto color : colors) cout << color << ' ';
```

### Condensation graph

```cpp
auto components = condensation(graph, colors);
Vector<Vector<int>> condensationGraph(components);
for (int from = 0; from < n; ++from) {
    for (auto to : graph[from]) {
        if (colors[from] != colors[to]) condensationGraph[colors[from]].push_back(colors[to]);
    }
}
```

## Bridges

$u$ - вершина, до которой можно добраться по обратному ребру в обходе

$to$ - вершина, до которой можно добраться по прямому ребру в обходе

$$
upH[v] = \min(h[v], \min_{\forall u} h[u], \min_{\forall to} upH[u])
$$

```cpp
Vector<Vector<int>> graph;
Vector<int> height, upHeight;
Vector<Pair<int>> bridges;

void dfs(int vertex, int parent) {
    upHeight[vertex] = height[vertex];
    for (auto to : graph[vertex]) {
        if (to == parent) continue;
        if (height[to] != -1) {
            upHeight[vertex] = std::min(upHeight[vertex], height[to]);
        } else {
            height[to] = height[vertex] + 1;
            dfs(to, vertex);
            upHeight[vertex] = std::min(upHeight[vertex], upHeight[to]);
            if (upHeight[to] > height[vertex]) {
                bridges.emplace_back(vertex, to); // bridge
            }
        }
    }
}


int n, m; cin >> n >> m;
graph.resize(n);
height.resize(n, -1);
upHeight.resize(n);
for (int i = 0; i < m; i++) {
    int from, to; cin >> from >> to;
    graph[from].push_back(to);
    graph[to].push_back(from);
}
for (int i = 0; i < n; ++i) {
    if (height[i] == -1) {
        height[i] = 0;
        dfs(i, -1);
    }
}
for (auto [from, to] : bridges) {
    cout << from << ' ' << to << '\n';
}
```

## Cut points

```cpp
Vector<Vector<int>> graph;
Vector<int> height, upHeight;
Vector<int> cutPoints;

void dfs(int vertex, int parent, int root) {
    int children = 0;
    upHeight[vertex] = height[vertex];
    for (auto to : graph[vertex]) {
        if (to == parent) continue;
        if (height[to] != -1) {
            upHeight[vertex] = std::min(upHeight[vertex], height[to]);
        } else {
            height[to] = height[vertex] + 1;
            dfs(to, vertex, root);
            children++;
            upHeight[vertex] = std::min(upHeight[vertex], upHeight[to]);
            if (upHeight[to] >= height[vertex] && vertex != root) {
                cutPoints.push_back(vertex); // cut point
            }
        }
    }
    if (vertex == root && children > 1) {
        cutPoints.push_back(vertex); // cut point
    }
}

int n, m; cin >> n >> m;
graph.resize(n);
height.resize(n, -1);
upHeight.resize(n);
for (int i = 0; i < m; i++) {
    int from, to; cin >> from >> to;
    graph[from].push_back(to);
    graph[to].push_back(from);
}
for (int i = 0; i < n; ++i) {
    if (height[i] == -1) {
        height[i] = 0;
        dfs(i, -1, i);
    }
}
for (auto vertex : cutPoints) {
    cout << vertex << ' ';
}
```
