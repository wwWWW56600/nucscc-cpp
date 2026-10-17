#include "stats.h"

Statistics compute(const long long* data, int n) {
    Statistics s;
    s.count = n;
    s.sum = 0;
    s.min = data[0];
    s.max = data[0];
    for (int i = 0; i < n; ++i) {
        if (data[i] < s.min) s.min = data[i];
        if (data[i] > s.max) s.max = data[i];
        s.sum += data[i];
    }
    return s;
}
