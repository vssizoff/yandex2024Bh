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
Vector<Vector<int>> graph, reversedGraph;
Vector<int> order, colors;
Vector<bool> used;

void topSort(int vertex) {
    used[vertex] = true;
    for (auto to : graph[vertex]) {
        if (!used[to]) topSort(to);
    }
    order.push_back(vertex);
}

void dfs(int vertex, int color) {
    used[vertex] = true;
    colors[vertex] = color;
    for (auto to : reversedGraph[vertex]) {
        if (!used[to]) dfs(to, color);
    }
}

void condensation() {
    for (int i = 0; i < graph.size(); ++i) {
        if (!used[i]) topSort(i);
    }
    std::ranges::reverse(order);
    used.assign(order.size(), false);
    int color = 0;
    for (auto vertex : order) {
        if (!used[vertex]) dfs(vertex, color++);
    }
}

int n, m; cin >> n >> m;
graph.resize(n);
reversedGraph.resize(n);
used.resize(n);
colors.resize(n);
for (int i = 0; i < m; i++) {
    int from, to; cin >> from >> to;
    graph[from].push_back(to);
    reversedGraph[to].push_back(from);
}
condensation();
for (auto color : colors) cout << color << ' ';
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
    for (auto to : graph[vertex]) {
        if (to == parent) continue;
        if (height[to] != -1) {
            upHeight[vertex] = std::min(upHeight[vertex], height[to]);
        } else {
            height[to] = height[vertex] + 1;
            dfs(to, vertex);
            upHeight[vertex] = std::min(upHeight[vertex], upHeight[to]);
            if (upHeight[to] > height[vertex]) {
                bridges.emplace_back(vertex, to); // мост
            }
        }
    }
}


int n, m; cin >> n >> m;
graph.resize(n);
height.resize(n, -1);
upHeight.resize(n, std::numeric_limits<int>::max());
for (int i = 0; i < m; i++) {
    int from, to; cin >> from >> to;
    graph[from].push_back(to);
}
for (int i = 0; i < n; ++i) {
    if (height[i] == -1) dfs(i, -1);
}
for (auto [from, to] : bridges) {
    cout << from << ' ' << to << '\n';
}
```
