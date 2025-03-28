# DTree

## Search tree

```cpp
std::random_device rd;
std::mt19937 gen(rd());

class DTreeNode {
protected:
    LL value, priority;
    DTreeNode *left = nullptr, *right = nullptr;

    static DTreeNode* merge(DTreeNode* node1, DTreeNode* node2) {
        if (node1 == nullptr && node2 == nullptr) return nullptr;
        if (node1 == nullptr) return new DTreeNode(node2);
        if (node2 == nullptr) return new DTreeNode(node1);
        if (node1->priority < node2->priority) {
            auto* result = new DTreeNode(node2->value);
            result->left = merge(node1, node2->left);
            result->right = node2->right;
            return result;
        }
        else {
            auto* result = new DTreeNode(node1->value);
            result->right = merge(node1->right, node2);
            result->left = node1->left;
            return result;
        }
    }

    Pair<DTreeNode*> split(LL x) {
        if (value > x) {
            if (this->left == nullptr) return {nullptr, new DTreeNode(this)};
            auto [left, right] = this->left->split(x);
            this->left = right;
            return {left == nullptr ? nullptr : new DTreeNode(left), new DTreeNode(this)};
        }
        else {
            if (this->right == nullptr) return {new DTreeNode(this), nullptr};
            auto [left, right] = this->right->split(x);
            this->right = left;
            return {new DTreeNode(this), right == nullptr ? nullptr :  new DTreeNode(right)};
        }
    }

    void set(DTreeNode* ptr) {
        this->left = ptr->left;
        this->right = ptr->right;
        this->value = ptr->value;
        this->priority = ptr->priority;
    }

public:
    explicit DTreeNode(LL value, LL priority = gen()): value(value), priority(priority) {}

    explicit DTreeNode(DTreeNode* node) {set(node);}

    void add(LL x) {
        auto [left, right] = this->split(x);
        auto ptr = merge(merge(left, new DTreeNode(x)), right);
        set(ptr);
    }

    void erase(LL x) {
        auto [lessEqual, greater] = this->split(x);
        if (lessEqual == nullptr) return set(greater);
        auto ptr = merge(lessEqual->split(x - 1).first, greater);
        set(ptr);
    }

    [[nodiscard]] bool contains(LL x) const {
        if (value == x) return true;
        return (left != nullptr && value <= x ? left->contains(x) : false) || (right != nullptr && value > x ? right->contains(x) : false);
    }

    [[nodiscard]] const LL* min() const {
        if (left == nullptr) return &value;
        return left->min();
    }

    const LL* upperBound(LL x) {
        auto [lessEqual, greater] = this->split(x);
        if (greater == nullptr) {
            set(merge(lessEqual, greater));
            return nullptr;
        }
        auto ret = greater->min();
        set(merge(lessEqual, greater));
        return ret;
    }

    const LL* lowerBound(LL x) {
        if (contains(x)) return new LL(x);
        return upperBound(x);
    }
};
```