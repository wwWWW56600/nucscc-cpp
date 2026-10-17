# L4 · 多文件统计工具（cpp-multifile-build，CMake 构建）

将统计功能拆成三个模块：`main`（入口）、`stats`（计算）、`format`（格式化）。通过 CMake 把三个 `.cpp` 一起构建为 `build/main`。

## 构建

```bash
cd src/L4_cpp
rm -rf build              # 干净构建，删除旧缓存
cmake -S . -B build       # 配置：读 CMakeLists.txt 生成构建系统
cmake --build build       # 编译 + 链接，产出 build/main
```

## 运行

```bash
./build/main
```

**输入**：第一行整数 `n`（`1 ≤ n ≤ 10000`）；第二行 `n` 个整数（每个 `[-1000000000, 1000000000]`）。
**输出**：恰好四行 `count=` / `sum=` / `min=` / `max=`。`sum` 为 64 位整数。

## 样例

输入：

```
5
1000000000 1000000000 1000000000 1000000000 1000000000
```

输出：

```
count=5
sum=5000000000
min=1000000000
max=1000000000
```

（`sum=5000000000` 超过 32 位整数范围，必须用 `long long`。）

## 要点

- `CMakeLists.txt` 的 `add_executable` 必须列全 `main.cpp stats.cpp format.cpp`，漏 `format.cpp` 会报 `undefined reference`。
- `format.cpp` 中 `print_report` 的签名必须与 `format.h` 声明一致（参数顺序 `count, total, smallest, largest`，类型以声明/调用方为准）。
- **不要提交 `build/` 目录**：评测自行重新构建，预编译产物不生效。
