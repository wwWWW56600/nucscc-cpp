# L5 cpp · 读数变化观察（cpp-optional-debug）

## 编译
```bash
g++ -std=c++17 -Wall -Wextra -o main main.cpp
```

## 运行（样例文件名以 `ls samples/` 为准）
```bash
./main < samples/01-mixed.in    # count=6  sum=24  increases=2  drops=2
./main < samples/02-single.in   # count=1  sum=4   increases=0  drops=0
./main < samples/03-flat.in     # count=4  sum=36  increases=0  drops=0
```

## 输入格式
第一行 `n`（1 ≤ n ≤ 100000）；第二行 `n` 个整数，每个在 [-1000, 1000]。

## 输出格式（恰好四行）
```
count=<n>
sum=<所有读数之和>
increases=<上升次数>
drops=<下降次数>
```

## 要点（黑盒契约）
- 从**第二项**起，每一项只和紧挨的前一项比：大→`increases+1`，小→`drops+1`，相等都不变。
- **第一项没有前一项**，不能计入上升/下降（修复点：比较循环从 `i==0` 只记账、不比较）。
- `sum` 用 `long long`（可能超 32 位）。
- 本题为**可选关**（不按运行速度评分，不要求提交调试记录）。
