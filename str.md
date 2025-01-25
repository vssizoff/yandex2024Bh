# N function

```cpp
for (int i = 1; i < n; i++) {
    if (i < r) {
        nf[i] = std::max(nf[i - l], r - i);
    }
    while (i + nf[i] < n && str[i + nf[i]] == str[nf[i]]) {
        nf[i]++;
    }
    if (i + nf[i] > n) {
        l = i;
        r = i + nf[i];
    }
}
```

# Prefix function

```cpp
for (int i = 1; i < n; i++) {
    j = pi[i - 1];
    while (j > 0 && str[i] != str[j]) j = pi[i];
    if (str[i] == str[j]) j++;
    pi[i] = j;
}
```