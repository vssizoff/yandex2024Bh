# Yandex algo B' lectures
1. [Sorts](./sorts.md)
2. [DFS2](./dfs2.md)

# Not yandex
1. [Fenvic's tree](./fenvicTree.md)

## Headers
```cpp
#include <iostream>
#include <vector>
#include <string>
#include <bitset>
#include <map>
#include <queue>
#include <set>
#include <algorithm>
#include <fstream>
#include <functional>
#include <random>
#include <ctime>

using String = std::string;
template<typename T0, typename T1 = T0>
using Pair = std::pair<T0, T1>;
template<typename T>
using Vector = std::vector<T>;
template<typename T0, typename T1 = T0>
using Map = std::map<T0, T1>;
template<typename T>
using Set = std::set<T>;
using LL = long long;
using LD = long double;
using std::cin, std::cout, std::cerr;

template<typename Type1, typename Type2>
std::istream &operator>>(std::istream &stream, Pair<Type1, Type2> &pair) {
    stream >> pair.first >> pair.second;
    return stream;
}

template<typename Type>
std::istream &operator>>(std::istream &stream, Vector<Type> &vec) {
    for (auto &elem : vec) stream >> elem;
    return stream;
}

signed main() {
    std::ios_base::sync_with_stdio(false);
    cin.tie(nullptr);
    cout.tie(nullptr);
    cout.precision(100);

}
```
