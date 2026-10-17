# NCUSCC 招新考核 · 进阶 C/C++ 通关代码

南昌大学超算俱乐部（NCUSCC）2026 秋季招新考核 —— 进阶 C/C++ 方向已通关关卡源码。

> 本仓库只放**源码与说明**，技术报告与感悟报告见 `技术报告_感悟报告.pdf`（另行提交）。代码与报告分离：正文分析在报告里，源码在此处，互不混杂。

## 环境

- 编译器：`g++`（C++17）
- 构建工具：CMake ≥ 3.16（仅 L4 多文件工程需要）
- 系统：Linux 容器 / 本机 MinGW-w64 均可

## 目录结构

```
.
├── README.md          # 本文件：项目说明 + 目录结构 + 命令行清单
├── src/               # 全部源码，按关分目录；每关目录内含独立 README.md（构建/运行指令）
│   ├── L1_cpp/        # 读数统计
│   │   ├── main.cpp
│   │   └── README.md  # 编译/运行/输入格式/样例
│   ├── L2_cpp/        # 设备巡检记录
│   │   ├── main.cpp
│   │   └── README.md
│   ├── L3_cpp/        # 固定容量读数窗口（环形缓冲）
│   │   ├── main.cpp
│   │   └── README.md
│   ├── L4_cpp/        # 多文件统计工具（CMake 多文件构建）
│   │   ├── CMakeLists.txt
│   │   ├── main.cpp
│   │   ├── stats.h / stats.cpp    # 统计模块
│   │   ├── format.h / format.cpp  # 格式化模块
│   │   └── README.md              # CMake 构建流程 + 样例
│   └── L5_cpp/        # 读数变化观察（可选 debug 关）
│       ├── main.cpp
│       └── README.md             # 缺陷定位 + 编译/运行 + 样例
└── 技术报告_感悟报告.pdf   # 技术报告 + 感悟报告（另附，不进仓库代码）
```

> 每个 `src/Lx_cpp/` 目录下都自带 `README.md`，单独 clone 任一目录也能照着编译运行——源码与指令不分离。

## 关于基础关（L1–L3 基础）

基础关是考核平台网页 IDE 内的 `exam` 脚本操作（Python XOR 加解密、两段信号拼接、读日志修复输入），属于平台内置验证流程，**没有本地原创源码工程**，因此不进入本仓库的 `src/` 目录。相关过程（黑盒建模、命令表、踩坑与修复）统一写入 `技术报告_感悟报告.pdf` 的叙述章节，在仓库中不留源码——仓库只承载进阶 C/C++ 方向你自己写的工程代码。

## 各关构建与运行

**L1 / L2 / L3（单文件）**

```bash
cd src/Lx_cpp
g++ -std=c++17 -o main main.cpp
./main < samples/xxx.in      # 或直接键盘输入
```

**L4（多文件，CMake）**

```bash
cd src/L4_cpp
rm -rf build
cmake -S . -B build
cmake --build build
./build/main < samples/xxx.in
```



> 注：各关 `samples/` 由考核平台工作区提供，仓库不含样例数据；提交时只提交源码，不要提交 `build/` 或本地编译产物。

## 各关要点速查

| 关  | 考点                    | 关键修复 / 实现                                                 |
| -- | --------------------- | --------------------------------------------------------- |
| L1 | 基本 I/O、极值初始化          | min/max 用首个值初始化，不能用 0 兜底                                  |
| L2 | 结构体数组、固定顺序输出          | 4 类固定全输出（含 0 0）；busiest 并列取靠前下标                           |
| L3 | 环形缓冲（circular buffer） | `window[i%8]` 回绕写入 + kept 封顶 8 + 绕回后 oldest=`window[n%8]` |
| L4 | CMake 收齐源 + 声明/定义签名一致 | `add_executable` 列全三文件；`print_report` 签名与声明对齐；sum 用 64 位  |

---

## 命令行操作清单（供技术报告引用）

以下为终端 shell 中实际操作的命令记录，报告里可直接引用这一段。

### A. 平台工作区实操（考核网页 IDE 终端，已执行）

```bash
# —— 侦察与探索 ——
ls -la /workspace/                 # 列根目录入口文件，确认是否需删 C 模板
cat CMakeLists.txt                 # 读构建入口，确认 add_executable 是否漏源文件
cat format.h                       # 读声明，作为修复 print_report 签名的依据
cat format.cpp                     # 读实现，对比声明找签名不一致

# —— 写/覆写源码（cat > 进入等待态，粘贴后回车 + Ctrl+D 结束）——
cat > /workspace/main.cpp          # L1/L2/L3 单文件：粘贴代码后 Ctrl+D
cat > /workspace/format.cpp        # L4：粘贴对齐签名后的实现后 Ctrl+D
cat > /workspace/CMakeLists.txt    # L4：粘贴补齐全源 + 设 C++17 的构建文件后 Ctrl+D

# —— 构建与运行 ——
g++ -std=c++17 -o main main.cpp                       # 单文件编译
rm -rf build                                         # L4：删旧构建目录，干净重建
cmake -S . -B build                                  # L4：配置
cmake --build build                                  # L4：编译+链接，产出 build/main
./main < samples/01-wide.in                          # 喂样例输入运行（单文件）
./build/main < samples/02-overflow.in                # L4 喂样例（重点验 64 位求和）
diff <(./build/main < "$f") "${f%.in}.out" && echo OK  # 与官方期望输出逐字符比对
```

> ⚠️ `cat >` 等待态中**不要按方向键**（会注入 `ESC[B` 导致 `stray '\33'` 编译错误），写大文件建议逐行粘贴；断线后先 `cat 文件名` 检查完整性再重写覆盖。

### B. 本机仓库与 GitHub 上传（⚠️ 待执行：下述命令在你本地真正 push 到 GitHub 时才发生）

> **重要（诚实记录原则）**：以下**不是已执行的记录**，而是「届时照做的步骤模板」。评分重点考察**真实的 git 操作**（本地/远程分支、同步过程、用了哪些指令），所以这部分**不能提前编造**。等你本地真正执行 git 上传那一步，把你终端**实际敲的**命令（含真实提交信息、真实远端地址脱敏）回填到这里，并同步写进技术报告的 git 章节。

```bash
# —— 在你本地准备好仓库目录后（命令按你实际用的来）——
git init                                          # 若尚未建仓（或 git clone <你的仓库URL>）
# mkdir ncuscc-cpp && cd ncuscc-cpp               # 按需建目录并进入
# vim README.md / code 编辑器                      # 用你习惯的方式写/改说明与代码

git add README.md src/                            # 只加说明与源码，不加 build/ 等产物
git commit -m "..."                               # 提交信息按你实际写的来（建议带关卡进度）
git remote add origin <你的仓库URL>               # 关联远端（若 clone 则已存在，可跳过）
git push -u origin main                           # 推送到 main 分支（分支名按你实际来）
```

> 上传前确认：仓库根目录含 `README.md` + `src/`，**不含 `build/`**；技术/感悟报告 `xxx.pdf` 单独提交或另附，不混入源码。push 完成后，把上面**实际生效**的命令回填本段与报告——未真正执行过的步骤一律不写。
