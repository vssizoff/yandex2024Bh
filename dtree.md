# DTree

## Search tree

```cpp
std::random_device rd;
std::mt19937 gen(rd());

class DTree {
protected:
    struct Node {
        Node* left = nullptr;
        Node* right = nullptr;
        int value;
        int priority;

        explicit Node(int val, int priority = gen()) : value(val), priority(priority) {}
    };

    Node* root = nullptr;

    static std::pair<Node*, Node*> split(Node* t, int x) {
        if (!t) return {nullptr, nullptr};
        if (t->value <= x) {
            auto [l, r] = split(t->right, x);
            t->right = l;
            return {t, r};
        }
        else {
            auto [l, r] = split(t->left, x);
            t->left = r;
            return {l, t};
        }
    }

    static Node* merge(Node* a, Node* b) {
        if (a == nullptr) {
            return b;
        }
        else if (b == nullptr) {
            return a;
        }

        if (a->priority > b->priority) {
            a->right = merge(a->right, b);
            return a;
        }
        else {
            b->left = merge(a, b->left);
            return b;
        }
    }

    static bool contains(Node* t, int x) {
        if (!t) return false;
        if (t->value == x) return true;
        return x < t->value ? contains(t->left, x) : contains(t->right, x);
    }

    static Node* min(Node* t) {
        if (!t) return nullptr;
        while (t->left) t = t->left;
        return t;
    }

public:
    int* lowerBound(int x) {
        auto [l, r] = split(root, x - 1);
        Node* candidate = min(r);
        int* res = candidate ? new int(candidate->value) : nullptr;
        root = merge(l, r);
        return res;
    }

    void add(int x) {
        if (contains(root, x)) return;
        auto [l, r] = split(root, x);
        root = merge(merge(l, new Node(x)), r);
    }

    [[nodiscard]] bool contains(int x) const {
        return contains(root, x);
    }
};
```

## Array

```cpp
std::random_device rd;
std::mt19937 gen(rd());

class DTree {
protected:
    struct Node {
        Node* left = nullptr;
        Node* right = nullptr;
        int value;
        int priority;
        int size = 1;

        explicit Node(int value, int priority = gen()): value(value), priority(priority) {}

        void updateSize() {
            size = getSize(left) + getSize(right) + 1;
        }
    };

    Node* root = nullptr;

    static int getSize(Node* node) {
        if (node == nullptr) return 0;
        return node->size;
    }

    static std::pair<Node*, Node*> split(Node* node, int k) {
        if (node == nullptr) return {nullptr, nullptr};
        if (k > getSize(node->left)) {
            auto [l, r] = split(node->right, k - getSize(node->left) - 1);
            node->right = l;
            node->updateSize();
            return {node, r};
        }
        else {
            auto [l, r] = split(node->left, k);
            node->left = r;
            node->updateSize();
            return {l, node};
        }
    }

    static Node* merge(Node* node0, Node* node1) {
        if (node0 == nullptr) return node1;
        if (node1 == nullptr) return node0;
        if (node0->priority > node1->priority) {
            node0->right = merge(node0->right, node1);
            node0->updateSize();
            return node0;
        }
        else {
            node1->left = merge(node0, node1->left);
            node1->updateSize();
            return node1;
        }
    }

    static void array(Node* node, Vector<int>& ret) {
        if (node == nullptr) return;
        array(node->left, ret);
        ret.push_back(node->value);
        array(node->right, ret);
    }

public:
    void add(int value) {
        root = merge(root, new Node(value));
    }

    explicit DTree(const Vector<int>& array) {
        for (auto elem : array) add(elem);
    }

    [[nodiscard]] Vector<int> array() const {
        Vector<int> ret;
        array(root, ret);
        return ret;
    }
};
```

## Lazy

```cpp
std::random_device rd;
std::mt19937 gen(rd());

class DTree {
protected:
    struct Node {
        Node* left = nullptr;
        Node* right = nullptr;
        int value;
        int priority;
        int size = 1;
        int min;
        bool swap = false;

        explicit Node(int value, int priority = gen()): value(value), priority(priority), min(value) {}

        void update() {
            size = getSize(left) + getSize(right) + 1;
            min = std::min({left != nullptr ? left->min : std::numeric_limits<int>::max(), right != nullptr ? right->min : std::numeric_limits<int>::max(), value});
        }

        void push() {
            if (!swap) return;
            std::swap(left, right);
            swap = false;
            if (left != nullptr) left->swap ^= true;
            if (right != nullptr) right->swap ^= true;
        }
    };

    Node* root = nullptr;

    static int getSize(Node* node) {
        if (node == nullptr) return 0;
        return node->size;
    }

    static std::pair<Node*, Node*> split(Node* node, int k) {
        if (node == nullptr) return {nullptr, nullptr};
        node->push();
        if (k > getSize(node->left)) {
            auto [l, r] = split(node->right, k - getSize(node->left) - 1);
            node->right = l;
            node->update();
            return {node, r};
        }
        else {
            auto [l, r] = split(node->left, k);
            node->left = r;
            node->update();
            return {l, node};
        }
    }

    static Node* merge(Node* node0, Node* node1) {
        if (node0 == nullptr) return node1;
        if (node1 == nullptr) return node0;
        node0->push();
        node1->push();
        if (node0->priority > node1->priority) {
            node0->right = merge(node0->right, node1);
            node0->update();
            return node0;
        }
        else {
            node1->left = merge(node0, node1->left);
            node1->update();
            return node1;
        }
    }

    static void array(Node* node, Vector<int>& ret) {
        if (node == nullptr) return;
        node->push();
        array(node->left, ret);
        ret.push_back(node->value);
        array(node->right, ret);
    }

public:
    void add(int value) {
        root = merge(root, new Node(value));
    }

    void add(int value, int index) {
        auto [l, r] = split(root, index + 1);
        root = merge(merge(l, new Node(value)), r);
    }

    explicit DTree(const Vector<int>& array) {
        for (auto elem : array) add(elem);
    }

    DTree() = default;

    int min(int l, int r) {
        auto [node0, node] = split(root, l);
        auto [node1, node2] = split(node, r - l + 1);
        auto min = node1->min;
        root = merge(merge(node0, node1), node2);
        return min;
    }

    void reverse(int l, int r) {
        auto [node0, node] = split(root, l);
        auto [node1, node2] = split(node, r - l + 1);
        node1->swap ^= true;
        root = merge(merge(node0, node1), node2);
    }

    [[nodiscard]] Vector<int> array() const {
        Vector<int> ret;
        array(root, ret);
        return ret;
    }
};
```