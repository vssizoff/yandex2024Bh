# Fenvic's tree

1-indexation

$$
k(n) = 2^l \quad l - max \quad n \vdots 2^l
$$

$$
fen_i = \sum^i_{j = i - k(i) + 1} a_i
$$

## Building

$$
pref_i = \sum^{i}_{j = 0} a_j
$$

$$
fen_{i + 1} = pref_i - pref_{i - k(i)}
$$

## Getting

### On prefix:

$$
\sum^l_{i = 1} a_i = fen_l + \sum^{l - k}_{i = 1}
$$

```cpp
int pref = 0;
for (; l > 0; l -= l&(-l)) {
    pref += fen[l];
}
```

### On $[l, r]$

```cpp
pref(r) - pref(l - 1);
```

## Setting

```cpp
for (; l <= n; l += l & (-l) {
    fen[n] += difference;
}
```

## Finding $k(n)$

$$
k(n) = n \& (-n)
$$

## Code

```cpp

```

# 2D Fenvic's tree

$$
fen[i][j] = \sum^i_{I = i - k(i) + 1} \sum^i_{J = j - k(j) + 1} a[I][J]
$$

## Getting

### On prefix

```cpp
int s = 0;
for (int i = x; i > 0; i -= i & (-i)) {
    for (int j = y; j > 0; j -= j & (-j)) {
        s += fen[i][j];
    }
}
```

### On $[(x_0, y_0), (x_1, y_1)]$

$$
pref(x_1, y_1) - pref(x_1, y_0 - 1) - pref(x_0 - 1, y_1) + pref(x_0 - 1, y_0 - 1)
$$

## Setting

```cpp
for (int i = x; i < n; i += i & (-i)) {
    for (int j = y; j < m; j += j & (-j)) {
        fen[x][y] += difference;
    }
}
```


