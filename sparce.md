# Sparce
```cpp
template<typename Type, typename Operator>
class Sparce {
protected:
    Vector<Vector<Type>> sparce;
    Operator op;

public:
    explicit Sparce(const Vector<Type>& array, Operator op = std::min): op(op) {
        sparce.resize(array.size(), Vector<Type>(std::__lg(array.size()) + 1));
        for (int i = 0; i < array.size(); ++i) sparce[i].front() = array[i];
        for (int p = 1; p <= std::__lg(array.size()); ++p) {
            for (int i = 0; i + (1 << p) <= array.size(); ++i) {
                sparce[i][p] = op(sparce[i][p - 1], sparce[i + (1 << p - 1)][p - 1]);
            }
        }
    }

    Type operator()(int l, int r) const {
        auto p = std::__lg(r - l + 1);
        return op(sparce[l][p], sparce[r - (1 << p) + 1][p]);
    }
};
```