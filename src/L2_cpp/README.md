# L2 · 设备巡检记录（cpp）

读取 n 条 `(类型 状态 工时)` 记录，按固定 4 类顺序 `printer / scanner / router / server` 汇总数量与工时，并输出工时最高的 `busiest`。

## 构建

```bash
g++ -std=c++17 -o main main.cpp
```

## 运行

```bash
./main
```

**输入**：第一行一个整数 `n`；之后 `n` 行，每行 `类型 状态 工时`（类型为上面 4 类之一，工时为整数）。
**输出**：4 行 `类型 数量 工时`（含数量为 0 0 的类别），最后一行 `busiest <类型>`。

## 样例

输入：

```
3
printer ok 2
scanner ok 1
router ok 3
```

输出：

```
printer 1 2
scanner 1 1
router 1 3
server 0 0
busiest router
```

## 要点

- 4 个类别**全部输出**，没有记录的类别也要打印 `0 0`。
- `busiest` 并列时取**下标靠前**的类别（比较时用 `>` 而非 `>=`）。
- `hours` 对所有出现过的类型无条件累加。
