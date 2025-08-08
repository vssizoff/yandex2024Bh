# Sparce tables

st[n][ceil(log n)]

$$
st[i][j]=\sum^i_{I=i-2+1} a_I
$$

```cpp
template<typename T = LL>
class SparseTable {
public:
    static constexpr int MAX_SIZE_LG = 20;

private:
    Vector<Vector<T>> sparce;
    std::function<T(T, T)> operation;

public:
    void build(const Vector<T>& array) {
        sparce.assign(array.size(), Vector<T>(MAX_SIZE_LG));
        for (int i = 0; i < array.size(); ++i) sparce[i].front() = array[i];
        for (int i = 1; i < MAX_SIZE_LG; ++i) {
            for (int j = 0; j < static_cast<int>(array.size()) - (1 << i) + 1; ++j) {
                sparce[j][i] = operation(sparce[j][i - 1], sparce[j + (1 << (i - 1))][i - 1]);
            }
        }
    }

    explicit SparseTable(const Vector<T>& array, std::function<T(T, T)> operation = [](LL a, LL b) {return std::min(a, b);}): operation(std::move(operation)) {
        build(array);
    }

    T operator()(int l, int r) const {
        int lg = std::__lg(r - l + 1);
        return operation(sparce[l][lg], sparce[r - (1 << lg) + 1][lg]);
    }
};
```