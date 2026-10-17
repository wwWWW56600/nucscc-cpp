#include <iostream>

// 进阶 L1 cpp · 读数统计
// 读 n 个整数，输出 count / sum / min / max（四行，与题面契约一致）
int main() {
    int n;
    if (!(std::cin >> n)) return 1;

    long long sum = 0;
    int count = 0;
    int mn = 0, mx = 0;
    bool have = false;

    for (int i = 0; i < n; ++i) {
        int v;
        if (!(std::cin >> v)) return 1;
        if (!have) { mn = v; mx = v; have = true; }  // 用首个值初始化 min/max，不能用 0 兜底
        if (v < mn) mn = v;
        if (v > mx) mx = v;
        sum += v;
        ++count;
    }

    std::cout << "count=" << count << "\n";
    std::cout << "sum="   << sum   << "\n";
    std::cout << "min="   << mn    << "\n";
    std::cout << "max="   << mx    << "\n";
    return 0;
}
