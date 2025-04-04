# BinUp
```cpp
class BinUp {
    Vector<Vector<int>> binUpArray;

 public:
    const int l;

    explicit BinUp(const Vector<int>& parents, int root = 0): l(std::__lg(parents.size()) + 1) {
        int n = parents.size();
        // l = log2(n) + 1;
        binUpArray.assign(n, Vector<int>(l));
        binUpArray[root][0] = -1;
        for (int i = 0; i < n; ++i) {
            if (parents[i] == -1) continue;
            binUpArray[i][0] = parents[i];
        }
        for (int j = 1; j < l; ++j) {
            for (int i = 0; i < n; ++i) {
                if (binUpArray[i][j - 1] != -1) {
                    binUpArray[i][j] = binUpArray[binUpArray[i][j - 1]][j - 1];
                } else {
                    binUpArray[i][j] = -1;
                }
            }
        }
    }

    [[nodiscard]] int binUp(int vertex, int count) const {
        if (binUpArray[vertex][count] == -1) return 0;
        return binUpArray[vertex][count];
    }
};
```

## LCA
```cpp
class LCA : protected BinUp {
    Vector<int> depth;

    void initDepth(const Vector<Vector<int>>& graph, int vertex = 0, int current = 0) {
        depth[vertex] = current;
        for (auto to : graph[vertex]) initDepth(graph, to, current + 1);
    }

 public:
    explicit LCA(const Vector<int>& parents, int root = 0): BinUp(parents, root) {
        Vector<Vector<int>> graph(parents.size());
        for (int i = 0; i < parents.size(); ++i) {
            if (parents[i] == -1) continue;
            graph[parents[i]].push_back(i);
        }
        depth.resize(parents.size());
        initDepth(graph, root);
    }

    int operator()(int vertex, int vertex0) const {
        if (depth[vertex] < depth[vertex0]) std::swap(vertex, vertex0);
        for (int j = l - 1; j >= 0; --j) {
            if (depth[vertex] - (1 << j) >= depth[vertex0]) {
                vertex = binUp(vertex, j);
            }
        }
        if (vertex == vertex0) {
            return vertex;
        }
        for (int j = l - 1; j >= 0; --j) {
            if (binUp(vertex, j) != binUp(vertex0, j)) {
                vertex = binUp(vertex, j);
                vertex0 = binUp(vertex0, j);
            }
        }
        return binUp(vertex, 0);
    }
};
```