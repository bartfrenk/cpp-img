
#include <cstddef>
#include <functional>
#include <type_traits>

template <typename A, typename P>
class Stored {
public:
    using coord_t = A;
    using pixel_t = P;
};

template <typename I, typename F>
class Exp {
public:
    Exp(const F &fn, const I &base) : fn_(fn), base_(base) {};
    using pixel_t = std::result_of<F(typename I::pixel_t)>;
    using coord_t = typename I::coord_t;
private:
    const F fn_;
    const I base_;
};

template <typename F, typename I>
Exp<I, F> exp(const F &fn, const I &base) {
    return Exp<I, F>(fn, base);
}

int main() {
    Stored<size_t, int> stored;
    auto result = exp([](int x) { return x + 1; }, stored);
    return 1;
}
