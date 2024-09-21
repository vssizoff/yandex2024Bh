# Sorts

## O($n^2$)

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
