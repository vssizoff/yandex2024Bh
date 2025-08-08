# BinUp
```cpp
class BinUp {
 public:
    static const int MAX_H_LG = 20;

 private:
    Vector<Vector<int>> binup_;

    void build(int vertex, int parent, const Vector<Vector<int>>& graph) {
        if (parent == -1) {
            binup_[vertex][0] = vertex;
        } else {
            binup_[vertex][0] = parent;
        }
        for (int i = 1; i < binup_[vertex].size(); ++i) {
            binup_[vertex][i] = binup_[binup_[vertex][i - 1]][i - 1];
        }
        for (auto to : graph[vertex]) {
            if (to != parent) build(to, vertex, graph);
        }
    }

 public:
    void build(const Vector<Vector<int>>& graph, int root = 0) {
        binup_.assign(graph.size(), Vector<int>(MAX_H_LG));
        build(root, -1, graph);
    }

    BinUp() = default;

    explicit BinUp(const Vector<Vector<int>>& graph, int root = 0) {
        build(graph, root);
    }

    [[nodiscard]] int binup(int vertex, int up) const {
        return binup_[vertex][up];
    }
};
```

## LCA
```cpp
class LCA: public BinUp {
    Vector<int> tin, tout;

    void getTInOut(int vertex, int parent, const Vector<Vector<int>>& graph, int& time) {
        tin[vertex] = time++;
        for (auto to : graph[vertex]) {
            if (to == parent) continue;
            getTInOut(to, vertex, graph, time);
        }
        tout[vertex] = time++;
    }

    void getTInOut(const Vector<Vector<int>>& graph, int root) {
        int time = 0;
        getTInOut(root, -1, graph, time);
    }

 public:
    [[nodiscard]] bool isParent(int vertex, int parent) const {
        return tin[parent] <= tin[vertex] && tout[parent] >= tout[vertex];
    }

    void build(const Vector<Vector<int>>& graph, int root = 0) {
        BinUp::build(graph, root);
        tin.assign(graph.size(), 0);
        tout.assign(graph.size(), 0);
        getTInOut(graph, root);
    }

    explicit LCA(const Vector<Vector<int>>& graph, int root = 0) {
        build(graph, root);
    }

    [[nodiscard]] int lca(int v, int u) const {
        if (isParent(v, u)) return u;
        if (isParent(u, v)) return v;
        for (int i = MAX_H_LG - 1; i >= 0; --i) {
            int next = binup(v, i);
            if (!isParent(u, next)) v = next;
        }
        return binup(v, 0);
    }
};
```