/**
 * C++17特性 - 折叠表达式: 简化参数包的处理, 在某些情况下避免使用递归
 * 折叠表达式有四种语法形式
 * 一元右折叠: (pack op ...) -  (E op ...)  ==>  E1 op (... op (En-1 op En))
 * 一元左折叠: (... op pack) -  (... op E)  ==>  ((E1 op E2) op ...) op En
 * 二元右折叠: (pack op ... op init) - (E op ... op I)  ==>  E1 op(... op (En-1 op (En op I)))
 * 二元左折叠: (init op ... op pack) - (I op ... op E)  ==>  (((I op E1) op E2) op ...) op En
 * 
 * ref: https://blog.csdn.net/zwvista/article/details/53981696
 */

#include <iostream>

using namespace std;

// 一个能接受一个及以上参数的求和函数

// C++17 之前
template <typename First>
First sum1(First&& value) {
    return value;
}

template <typename First, typename Second, typename... Rest>
First sum1(First&& first, Second&& second, Rest&&... rest) {
    return sum1(first+second, forward<Rest>(rest)...);
}


// C++17 折叠表达式
template <typename First, typename... Rest>
First sum2(First&& first, Rest&&... rest) {
    return (first + ... + rest);
}


int main() {
    cout << sum1(1) << sum1(1, 2) << sum1(1, 2, 3) << endl;
    cout << sum2(1) << sum2(1, 2) << sum2(1, 2, 3) << endl;
    return 0;
}