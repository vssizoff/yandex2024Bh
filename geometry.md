```cpp
class Point {
protected:
    LD x, y;

public:
    explicit Point(LD x, LD y) : x(x), y(y) {}

    Point(const Point& a, const Point& b) {
        x = b.x - a.x;
        y = b.y - a.y;
    }

    Point operator+(const Point& other) const {return Point(x + other.x, y + other.y);}
    Point operator-(const Point& other) const {return Point(x - other.x, y - other.y);}
    Point operator*(const LD scalar) const {return Point(x * scalar, y * scalar);}
    Point operator/(const LD scalar) const {return Point(x / scalar, y / scalar);}

    LD operator*(const Point &other) const {return x * other.x + y * other.y;}
    LD operator^(const Point &other) const {return x * other.y - y * other.x;}

    [[nodiscard]] LD length() const {return std::sqrt(x * x + y * y);}
    [[nodiscard]] LD distance(const Point &other) const {return Point(*this, other).length();}
    [[nodiscard]] LD angle(const Point &other) const {return std::atan2(*this ^ other, *this * other);}
};
```