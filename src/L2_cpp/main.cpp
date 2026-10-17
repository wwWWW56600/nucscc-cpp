#include <iostream>
#include <string>

struct Totals {
    int count = 0;
    int hours = 0;
};

// 类型名与固定输出顺序一致：下标 0=printer,1=scanner,2=router,3=server
const char* NAMES[4] = {"printer", "scanner", "router", "server"};

int typeIndex(const std::string& type) {
    for (int i = 0; i < 4; ++i)
        if (type == NAMES[i]) return i;
    return -1;
}

int main() {
    int n;
    if (!(std::cin >> n)) return 1;

    Totals byType[4];

    for (int i = 0; i < n; ++i) {
        std::string type, status;
        int hours;
        if (!(std::cin >> type >> status >> hours)) return 1;
        int idx = typeIndex(type);
        if (idx < 0) return 1;
        byType[idx].count++;
        byType[idx].hours += hours;   // 本题所有工时均计入，status 不影响统计
    }

    for (int i = 0; i < 4; ++i)
        std::cout << NAMES[i] << " " << byType[i].count << " " << byType[i].hours << "\n";

    int best = 0;                      // 并列时保留较小下标（固定顺序靠前）
    for (int i = 1; i < 4; ++i)
        if (byType[i].hours > byType[best].hours) best = i;

    std::cout << "busiest " << NAMES[best] << "\n";
    return 0;
}
