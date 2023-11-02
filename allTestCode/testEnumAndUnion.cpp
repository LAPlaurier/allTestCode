/*
枚举类型enum
联合体union
*/

/*
使用枚举的优点：
1. 增加代码的可读性和可维护性
2. 和 define 定义的宏相比，枚举变量有类型检查
3. 便于调试（宏 无法调试）
4. 防止了命名污染，将类型相同的变量放在一起
5. 使用方便，一次可以定义多个常量
*/

/*
联合体特点：联合体内部成员共用同一块内存地址，联合变量大小至少是最大成员大小
联合体大小计算:
1. 联合的大小至少是最大成员的大小
2. 最大成员大小不是最大对齐数的整数倍时, 就要对其到最大对齐数的整数倍
*/


#include <iostream>
using namespace std;
enum Color {
    RED = 3,
    GREEN,
    BLUE
};

union Un{
    char c;
    int i;
};

union Un1{
    char c[5];
    int i;
};

union Un2{
    short c[7];
    int i;
};

int main() {
    Color c = Color::GREEN;
    cout << c << endl;

    union Un un;
    cout << "union 变量成员共用同一地址空间" << endl;
    cout << (unsigned long)&un << endl;
    cout << (unsigned long)&un.c << endl;
    cout << (unsigned long)&un.i << endl;


    cout << sizeof(union Un1) << endl;
    cout << sizeof(union Un2) << endl;

    return 0;
}