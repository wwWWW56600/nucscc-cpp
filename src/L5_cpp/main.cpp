#include <iostream>
int main() {
    int n; if (!(std::cin >> n)) return 1;
    long long sum = 0;            // 64 位：sum 可能超 32 位 int
    int increases = 0, drops = 0;
    int prev = 0;                // 前一项值，用于相邻比较
    for (int i = 0; i < n; ++i) {
        int v; if (!(std::cin >> v)) return 1;
        if (i == 0) {            // FIX：第一项没有"前一项"，只记账、不参与比较
            prev = v;
            sum = v;
            continue;
        }
        sum += v;
        if (v > prev) ++increases;       // 比前一项大 → 上升
        else if (v < prev) ++drops;      // 比前一项小 → 下降
        // 相等：两个计数都不变
        prev = v;                        // 更新前一项，供下次比较
    }
    std::cout << "count=" << n << "\n";
    std::cout << "sum=" << sum << "\n";
    std::cout << "increases=" << increases << "\n";
    std::cout << "drops=" << drops << "\n";
    return 0;
}
