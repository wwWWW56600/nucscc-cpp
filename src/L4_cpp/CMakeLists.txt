cmake_minimum_required(VERSION 3.16)
project(recruit_stats LANGUAGES CXX)

set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_STANDARD_REQUIRED ON)

# 必须列出全部实现文件：main.cpp + stats.cpp + format.cpp
# 漏掉 format.cpp 会报 undefined reference: print_report
add_executable(main main.cpp stats.cpp format.cpp)
