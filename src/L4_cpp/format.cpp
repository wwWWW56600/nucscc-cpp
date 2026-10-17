#include "format.h"
#include <iostream>

void print_report(long long count, long long total,
                  long long smallest, long long largest) {
    std::cout << "count=" << count << "\n";
    std::cout << "sum=" << total << "\n";
    std::cout << "min=" << smallest << "\n";
    std::cout << "max=" << largest << "\n";
}
