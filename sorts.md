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

($n - 1$)-th iteration:

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
