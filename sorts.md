# Sorts

## $O(n^2)$

### Bubble  sort

First iteration:

5 1 4 3 6 1 2

1 5 4 3 6 1 2

1 4 5 3 6 1 2

1 4 3 5 6 1 2

1 4 3 5 6 1 2

1 4 3 5 1 6 2

1 4 3 5 1 2 6

$(n - 1)^{th}$ iteration:

1 1 2 3 4 5 6

```cpp
void bubbleSort(std::vector<int>& array) {
    for (int epoch = 0; epoch < array.size() - 1; ++epoch) {
        for (int i = 0; i < array.size() - epoch - 1; ++i) {
            if (array[i] > array[i + 1]) std::swap(array[i], array[i + 1]);
        }
    }
}
```

### Paste sort

```cpp
void pasteSort(std::vector<int>& array) {
    for (int i = 1; i < array.size(); ++i) {
        int j = i;
        while (j > 0 && array[j - 1] > array[j]) {
            std::swap(array[j], array[j - 1]);
            j--;
        }
    }
}
```

### Selection sort

```cpp
void selectionSort(std::vector<int>& array) {
    for (int i = 0; i < array.size() - 1; ++i) {
        int minIndex = std::ranges::min_element(array.begin() + i, array.end()) - array.begin();
        std::swap(array[i], array[minIndex]);
    }
}
```

## $O(n \cdot \log n)$

### Merge sort

```cpp
void _merge(std::vector<int>& a, std::vector<int>& b, std::vector<int>& array) {
    int i = 0, j = 0;
    for (int k = 0; k < array.size(); ++k) {
        if (i < a.size() && j < b.size()) {
            if (array[i] < array[j]) array[k] = a[i++];
            else array[k] = b[j++];
        }
        else if (j == b.size()) array[k] = a[i++];
        else array[k] = b[j++];
    }
}

void mergeSort(std::vector<int>& array) {
    if (array.size() == 1) return;
    std::vector<int> a(array.size() / 2 + array.size() % 2), b(array.size() / 2);
    for (int i = 0; i < array.size() / 2 + array.size() % 2; ++i) a[i] = array[i];
    for (int i = 0; i < array.size() / 2; ++i) b[i] = array[i + array.size() / 2];
    mergeSort(a);
    mergeSort(b);
    _merge(a, b, array);
}
```

### Quick sort

```cpp
std::random_device rd;
std::mt19937 gen(rd());

int partition(std::vector<int>& array, int l = 0, int r = array.size()) {
    std::uniform_int_distribution dis(l, r);
    int pos = dis(gen), L = l, R = r - 1;
    while (L <= R) {
        while (array[L] < array[pos]) ++L;
        while (array[R] > array[pos]) --R;
        if (L >= R) break;
        std::swap(array[L], array[R]);
    }
    return R - 1;
}

void quickSort(std::vector<int>& array, int l = 0, int r = array.size()) {
    if (l >= r) return;
    int k = partition(array, l, r);
    quickSort(array, l, k);
    quickSort(array, k + 1, r);
}
```

### k-порядковая статистика (k-элемент в массиве по возрастанию) $O(n)$

```cpp
std::random_device rd;
std::mt19937 gen(rd());

int partition(std::vector<int>& array, int l = 0, int r = array.size()) {
    std::uniform_int_distribution dis(l, r);
    int pos = dis(gen), L = l, R = r - 1;
    while (L <= R) {
        while (array[L] < array[pos]) ++L;
        while (array[R] > array[pos]) --R;
        if (L >= R) break;
        std::swap(array[L], array[R]);
    }
    return R - 1;
}

int k_thElem(std::vector<int>& array, int l, int r, int k) {
    if (l + 1 == r) return array[l];
    int pos = partition(array, l, r), cnt = pos - l;
    if (cnt >= k) return k_thElem(array, l, pos, k);
    return k_thElem(array, pos + 1, r, k - cnt);
}
```

## Count sort $O(n + C)$ $C = max(array) - min(array)$

```cpp
void countSort(std::vector<int>& array, int min = std::ranges::min(array), int max = std::ranges::max(array)) {
    std::vector<int> count(max - min);
    for (auto elem: array) count[elem - min]++;
    int pos = 0;
    for (int i = min; i <= max; ++i) {
        for (int j = 0; j < array[i - min]; ++j) {
            array[pos] = i;
            pos++;
        }
    }
}
```
