#include <iostream>
// 固定容量读数窗口（已修复容量缺陷）
int main() {
    const int CAPACITY = 8;
    int window[8] = {};
    int kept = 0;
    int count = 0;
    if (!(std::cin >> count)) return 1;
    for (int i = 0; i < count; ++i) {
        int value = 0;
        if (!(std::cin >> value)) return 1;
        window[i % CAPACITY] = value;   // FIX1: 写入下标按容量回绕，不再越界写 window[8..]
        if (kept < CAPACITY) ++kept;    // FIX2: 保留计数封顶 8（kept 最大为 8）
    }
    // FIX3: 输出也要按窗口语义，不能按 kept 直接下标读（kept>8 时 window[kept-1] 越界）
    // 绕回后最旧值位于"下一个即将被写入的位置" = count % CAPACITY
    int start = (count >= CAPACITY) ? (count % CAPACITY) : 0;
    long long sum = 0;
    for (int i = 0; i < kept; ++i) {
        int idx = (start + i) % CAPACITY; // 按输入顺序绕回取保留值
        sum += window[idx];
    }
    int oldest = window[start];
    int last   = window[(count - 1) % CAPACITY];
    std::cout << "kept=" << kept << "\n";
    std::cout << "oldest=" << oldest << "\n";
    std::cout << "last=" << last << "\n";
    std::cout << "sum=" << sum << "\n";
    return 0;
}
