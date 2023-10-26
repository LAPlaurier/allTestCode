/*
C++11特性 - 模板参数包
*/

#include <iostream>

template<typename... T>
void print(T... args) {
    // 展开参数包并打印
        << '\n'; // C++17 折叠表达式
}


// 递归模板展开, C++11, C++14中,通常用递归技术来展开参数包
template<typename T>
void print(T t) {
    std::cout << t << '\n';
}

template<typename T, typename... Args>
void print(T t, Args... args) {
    std::cout << t << ' ';
    print(args...); // 递归调用,直到参数包为空
}


// 类模板中的参数包
template<typename... Values>
class Tuple;

template<>
class Tuple<> {};

template<typename Head, typename... Tail>
class Tuple<Head, Tail...> : public Tuple<Tail...> {
    Head head;
};


// 参数包的大小 - 可以用sizeof... 运算符获取参数包中的参数数量
template<typename... Args>
void foo(Args... args) {
    std::cout << sizeof...(Args) << '\n';   // 打印类型参数的数量
    std::cout << sizeof...(args) << '\n';   // 打印函数参数的数量
}
