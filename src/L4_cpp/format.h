#ifndef FORMAT_H
#define FORMAT_H

// 声明：参数顺序固定为 count, total, smallest, largest
// 实现文件的定义必须与这一签名完全一致，否则 C++ 视为重载 ->
// main 调用的签名没有定义 -> 链接期 undefined reference
void print_report(long long count, long long total,
                  long long smallest, long long largest);

#endif
