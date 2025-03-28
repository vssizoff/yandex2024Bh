# N function

```cpp
Vector<int> nFunc(const String& str) {
    int l = 0, r = 0;
    Vector<int> nf(str.size());
    nf.front() = str.size();
    for (int i = 1; i < str.size(); i++) {
        if (i < r) {
            nf[i] = std::min(nf[i - l], static_cast<int>(str.size() - i));
        }
        while (i + nf[i] < str.size() && str[i + nf[i]] == str[nf[i]]) {
            nf[i]++;
        }
        if (i + nf[i] > r) {
            l = i;
            r = i + nf[i];
        }
    }
    return nf;
}
```

# Prefix function

```cpp
Vector<LL> prefixFunc(const String& str) {
    Vector<LL> pi(str.size());
    LL j = 0;
    for (LL i = 1; i < str.size(); i++) {
        j = pi[i - 1];
        while (j > 0 && str[i] != str[j]) j = pi[j - 1];
        if (str[i] == str[j]) j++;
        pi[i] = j;
    }
    return pi;
}
```