#ifndef STATS_H
#define STATS_H

// 统计结果：全部用 64 位整数，sum 可能超过 32 位范围
struct Statistics {
    long long count;
    long long sum;
    long long min;
    long long max;
};

// 计算 n 个数的 count / sum / min / max
Statistics compute(const long long* data, int n);

#endif
