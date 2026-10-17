#include "stats.h"
#include "format.h"
#include <iostream>
#include <vector>

int main() {
    int n = 0;
    if (!(std::cin >> n)) return 1;
    std::vector<long long> data(static_cast<size_t>(n));
    for (int i = 0; i < n; ++i) {
        if (!(std::cin >> data[i])) return 1;
    }
    Statistics s = compute(data.data(), n);
    // print_report 语义固定：count, total, smallest, largest
    print_report(s.count, s.sum, s.min, s.max);
    return 0;
}
