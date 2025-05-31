#include <set>
#include <vector>
#include <cmath>
#include <cassert>
#include <stdexcept>

template<typename arg_t, typename val_t> 
struct point_t {
    arg_t arg;
    val_t val;

    bool operator<(const point_t& a) const {
        // как выяснилось, нельзя использовать EPSILON, результат сломает контейнер std::set
        return arg < a.arg;
    }
};

template<typename arg_t, typename val_t>
class point_coll_t {
    std::set<point_t<arg_t, val_t>> points;

public:
    point_coll_t() = default;

    point_coll_t(const std::vector<arg_t>& arguments, const std::vector<val_t>& values) {
        assert(arguments.size() == values.size());
        for (size_t i = 0; i < arguments.size(); ++i) {
            points.insert({arguments[i], values[i]});
        }
    }

    val_t interp(const arg_t& xa) const {
        if (points.size() < 2)
            throw std::runtime_error("Too few points for interpolation");

        auto it_upper = points.lower_bound({xa, val_t{}});
        if (it_upper == points.begin() || it_upper == points.end())
            throw std::out_of_range("xa is out of interpolation range");

        auto it_lower = std::prev(it_upper);

        const auto& [x1, y1] = *it_lower;
        const auto& [x2, y2] = *it_upper;

        return y1 + ((y2 - y1) / (x2 - x1)) * (xa - x1);
    }
};
