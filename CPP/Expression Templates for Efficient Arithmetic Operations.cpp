#include <iostream>

template <typename T>
struct Expr {
    const T& derived() const { return static_cast<const T&>(*this); }

    template <typename U>
    auto operator+(const Expr<U>& rhs) const {
        return Add<T, U>(derived(), rhs.derived());
    }

    template <typename U>
    auto operator-(const Expr<U>& rhs) const {
        return Sub<T, U>(derived(), rhs.derived());
    }

    template <typename U>
    auto operator*(const Expr<U>& rhs) const {
        return Mul<T, U>(derived(), rhs.derived());
    }
};

template <typename T, typename U>
struct Add : Expr<Add<T, U>> {
    const T& lhs;
    const U& rhs;

    Add(const T& lhs, const U& rhs) : lhs(lhs), rhs(rhs) {}

    double eval() const {
        return lhs.eval() + rhs.eval();
    }
};

template <typename T, typename U>
struct Sub : Expr<Sub<T, U>> {
    const T& lhs;
    const U& rhs;

    Sub(const T& lhs, const U& rhs) : lhs(lhs), rhs(rhs) {}

    double eval() const {
        return lhs.eval() - rhs.eval();
    }
};

template <typename T, typename U>
struct Mul : Expr<Mul<T, U>> {
    const T& lhs;
    const U& rhs;

    Mul(const T& lhs, const U& rhs) : lhs(lhs), rhs(rhs) {}

    double eval() const {
        return lhs.eval() * rhs.eval();
    }
};

struct Value : Expr<Value> {
    double val;

    Value(double v) : val(v) {}

    double eval() const {
        return val;
    }
};

int main() {
    Value x(5.0), y(3.0), z(2.0);
    auto result = (x + y) * z;
    std::cout << "Result: " << result.eval() << std::endl;
    return 0;
}
