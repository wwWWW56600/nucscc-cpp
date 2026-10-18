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
└── .gitignore         # 忽略规则：构建产物、内部数据、报告初稿等不进仓库
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

### B. 本机建仓与 GitHub 上传（已执行）

真实流程分三步：本地初始化并提交 → 网页端建空仓 → 关联远端并推送。以下均为实际生效的命令与提交。

```bash
# —— 第 1 步：本地建仓与首次提交 ——
git init                                          # 在工作区初始化本地仓库
git add README.md src .gitignore 上传说明.md upload.bat   # 显式暂存交付文件（不用 add .，防带入杂物）
git commit -m "NCUSCC 招新考核：进阶 C/C++ L1-L5 通关源码 + 上传说明"
# 首次提交 ff6c8fc，共 19 个文件

# —— 第 2 步：github.com 网页端 New repository 建空仓 ——
# 选 Public，不勾选 Initialize with README / .gitignore / License（本地已有，避免冲突）

# —— 第 3 步：关联远端并首推 ——
git branch -M main                                # 主分支命名为 main
git remote add origin https://github.com/wwWWW56600/nucscc-cpp.git
git push -u origin main                           # 首推并建立分支跟踪（-u = set-upstream）
```

> **踩坑 1（网络）**：首推报 `Failed to connect to github.com:443`——浏览器走了代理而 git 命令没有。设置**进程级**代理后重推成功（只对当前终端窗口生效，关闭即失效，不改全局配置）：
>
> ```bash
> set HTTP_PROXY=http://127.0.0.1:7897     # Windows cmd；端口为本机代理软件的混合端口
> set HTTPS_PROXY=http://127.0.0.1:7897
> git push                                 # 上游已由 -u 跟踪，后续 push 免参数
> ```

> **踩坑 2（git add . 全量添加）**：首次推送到远端时脚本内使用了 `git add .`，把辅助文件（打包 zip、上传脚本、上传说明）一并带入仓库。随后用 `git rm --cached` 从版本库移除（保留本地文件），并补全 `.gitignore` 防止复发：
>
> ```bash
> git rm --cached NCUSCC_cpp_upload_package.zip upload.bat   # --cached：只删版本库记录，保留本地文件
> git rm --cached 上传说明.md
> git add .gitignore                                         # 忽略清单补上这三类
> git commit -m "remove non-code files, keep code only"      # 修正提交 823b023
> git push
> ```
>
> 概念注记：删除文件在 git 里也是一种修改，同样要走 commit + push 才会同步到远端；`--cached` 与不带 `--cached` 的区别在于是否连工作区文件一起删。

> 最终仓库内容：`src/`（L1–L5 源码 + 各关 README）+ `README.md` + `.gitignore`。技术报告与感悟报告 PDF 不混入源码仓库，单独提交。
