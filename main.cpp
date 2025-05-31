#include "point.h"
#include <assert.h>
#include <iostream>
#include <vector>

constexpr double EPSILON = 0.02;

bool almost_equal(double a, double b, double rel_eps = 1e-9, double abs_eps = EPSILON) {
    double diff = std::abs(a - b);
    double scale = std::max(std::abs(a), std::abs(b));
    return diff <= std::max(rel_eps * scale, abs_eps);
}

void run_debug_tests() {
    using arg_t = double;
    using val_t = double;

    {
        point_coll_t<arg_t, val_t> coll({1.0, 2.0, 3.0}, {10.0, 20.0, 30.0});
        assert(almost_equal(coll.interp(1.5), 15.0));
    }

    {
        point_coll_t<arg_t, val_t> coll({1.0, 2.0, 3.0}, {1.0, 4.0, 9.0});
        assert(almost_equal(coll.interp(2.5), 6.5));
    }

    {
        point_coll_t<arg_t, val_t> coll({10.0, 20.0, 30.0}, {100.0, 200.0, 300.0});
        assert(almost_equal(coll.interp(20.0), 200.0));
    }

    {
        point_coll_t<arg_t, val_t> coll({1.0, 2.0, 3.0}, {10.0, 20.0, 30.0});
        try {
            coll.interp(0.5);
            assert(false);
        } catch (const std::out_of_range&) {}
    }

    {
        point_coll_t<arg_t, val_t> coll({1.0}, {10.0});
        try {
            coll.interp(1.0);
            assert(false);
        } catch (const std::runtime_error&) {}
    }

    std::cout << "All debug tests passed.\n";
}

int main(int argc, char* argv[]) {
#ifdef DEBUG_TESTS
    run_debug_tests();
#endif

    using arg_t = double;
    using val_t = double;

    std::vector<arg_t> args;
    std::vector<val_t> vals;

    std::cout << "Enter number of points:\n";
    size_t n;
    std::cin >> n;

    std::cout << "Enter points as <arg val> pairs:\n";
    for (size_t i = 0; i < n; ++i) {
        arg_t x;
        val_t y;
        std::cin >> x >> y;
        args.push_back(x);
        vals.push_back(y);
    }

    point_coll_t<arg_t, val_t> coll(args, vals);

    std::cout << "Enter interpolation argument xa:\n";
    arg_t xa;
    std::cin >> xa;

    try {
        val_t result = coll.interp(xa);
        std::cout << "Interpolated value: " << result << "\n";
    } catch (const std::exception& ex) {
        std::cerr << "Error during interpolation: " << ex.what() << "\n";
        return 1;
    }

    return 0;
}