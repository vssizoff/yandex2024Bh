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
    return color; // count of components
}
```

### Condensation graph

#### С кратными рёбрами

```cpp
auto components = condensation(graph, colors);
Vector<Vector<int>> condensationGraph(components);
for (int from = 0; from < n; ++from) {
    for (auto to : graph[from]) {
        if (colors[from] != colors[to]) condensationGraph[colors[from]].push_back(colors[to]);
    }
}
```

#### Без кратных рёбер

```cpp
auto components = condensation(graph, colors);
Vector<Set<int>> condensationGraph(components);
for (int from = 0; from < n; ++from) {
    for (auto to : graph[from]) {
        if (colors[from] != colors[to]) condensationGraph[colors[from]].insert(colors[to]);
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
void dfs(int vertex, int parent, const Vector<Vector<int>>& graph, Vector<Pair<int>>& bridges, Vector<int>& height, Vector<int>& upHeight) {
    upHeight[vertex] = height[vertex];
    for (auto to : graph[vertex]) {
        if (to == parent) continue;
        if (height[to] != -1) {
            upHeight[vertex] = std::min(upHeight[vertex], height[to]);
        } else {
            height[to] = height[vertex] + 1;
            dfs(to, vertex, graph, bridges, height, upHeight);
            upHeight[vertex] = std::min(upHeight[vertex], upHeight[to]);
            if (upHeight[to] > height[vertex]) {
                bridges.emplace_back(std::min(vertex, to), std::max(to, vertex)); // bridge
            }
        }
    }
}

void findBridges(const Vector<Vector<int>>& graph, Vector<Pair<int>>& bridges) {
    Vector<int> height(graph.size(), -1), upHeight(graph.size());
    bridges.clear();
    for (int i = 0; i < graph.size(); ++i) {
        if (height[i] == -1) {
            height[i] = 0;
            dfs(i, -1, graph, bridges, height, upHeight);
        }
    }
}
```

## Cut points

```cpp
void dfs(int vertex, int parent, int root, const Vector<Vector<int>>& graph, Set<int>& cutPoints, Vector<int>& height, Vector<int>& upHeight) {
    int children = 0;
    upHeight[vertex] = height[vertex];
    for (auto to : graph[vertex]) {
        if (to == parent) continue;
        if (height[to] != -1) {
            upHeight[vertex] = std::min(upHeight[vertex], height[to]);
        } else {
            height[to] = height[vertex] + 1;
            dfs(to, vertex, root, graph, cutPoints, height, upHeight);
            children++;
            upHeight[vertex] = std::min(upHeight[vertex], upHeight[to]);
            if (upHeight[to] >= height[vertex] && vertex != root) {
                cutPoints.insert(vertex); // cut point
            }
        }
    }
    if (vertex == root && children > 1) {
        cutPoints.insert(vertex); // root is cut point
    }
}

void findCutPoints(const Vector<Vector<int>>& graph, Set<int>& cutPoints) {
    Vector<int> height(graph.size(), -1), upHeight(graph.size());
    cutPoints.clear();
    for (int i = 0; i < graph.size(); ++i) {
        if (height[i] == -1) {
            height[i] = 0;
            dfs(i, -1, i, graph, cutPoints, height, upHeight);
        }
    }
}
```
