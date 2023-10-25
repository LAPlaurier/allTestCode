/*
 * std::function 作用：
 * 1. 简化调用：对C++中各种可调用实体（函数、仿函数、lambda）的封装，形成一个新的可调用的 function 对象。
 * 2. 给现有的可调用实体一种类型安全的包裹（如函数指针是类型不安全的可调用实体）
 * 
 * 
*/

#include <iostream>
#include <functional>   // std::bind()


/* ----- std::function ----- */
// ref: https://blog.csdn.net/qq_38410730/article/details/103637778
// 函数指针
int fun(int x, int y) { // 被调用的函数
    std::cout << x + y << std::endl;
    return x+y;
}

int fun1(int (*fp)(int, int), int x, int y) {   // 形参为函数指针
    return fp(x, y);
}

typedef int (*Ftype)(int, int);     // 定义一个函数指针类型Ftype

int fun2(Ftype fp, int x, int y) {
    return fp(x, y);
}

// lambada
auto mod = [](int a, int b){return a % b;};

// 函数对象（仿函数）
struct divide {
    int operator() (int denominator, int divisor) {
        return denominator/divisor;
    }
};

// std::function<函数类型>
typedef std::function<int(int, int)> comfun;



/* ----- std::bind ----- */
// ref: https://blog.51cto.com/u_13999641/3057536
// std::bind 是一个函数适配器，接受一个可调用对象，生成一个新的可调用对象来“适应”原对象的参数列表

// 1. 绑定普通函数
int bindNormalFucn(int x, int y, int z) {
    std::cout << "x: " << x << " ";
    std::cout << "y: " << y << " ";
    std::cout << "z: " << z << std::endl;
    return x+y+z;
}

// 2. 绑定一个成员函数
class testBindMemberFunc {
public:
    int memberFunc(int x, int y, int z) {
        std::cout << "m_data: " << m_data << std::endl;

        std::cout << "x: " << x << " ";
        std::cout << "y: " << y << " ";
        std::cout << "z: " << z << std::endl;
        return x+y+z;
    }

    testBindMemberFunc() = default;
    testBindMemberFunc(int n) : m_data(n) {}

    int m_data;
};

int main() {
    /* -- std::function -- */
    // 一般函数名即为函数指针，所以调用时有无&都可
    fun1(&fun, 100, 100);
    fun2(fun, 200, 200);

    // function 可取代函数指针的作用，且比函数指针更灵活（可指向仿函数、lambda）
    comfun a = fun;
    comfun b = mod;
    comfun c = divide();

    std::cout << "a: " << a(5, 3) << std::endl;
    std::cout << "b: " << b(5, 3) << std::endl;
    std::cout << "c: " << c(5, 3) << std::endl;
    std::cout << " --------------------------- \n" << std::endl;


    /* -- std::bind -- */
    // bind 的第一个参数是函数名。 std::placeholders 表示占位符
    auto testBind1 = std::bind(bindNormalFucn, 2, std::placeholders::_1, 3);
    std::cout << "std::bind 绑定普通函数: " << testBind1(10) << std::endl;

    // bind 绑定类成员函数时，第一个参数是对象的成员函数的指针，必须显式指定，因为编译器不会将对象的成员函数隐式转换成函数指针。
    // 第二个参数是对象的地址，因为类成员函数隐含一个参数*this，所以要传入对象地址
    testBindMemberFunc tbmf_a(1);
    testBindMemberFunc tbmf_b(2);
    auto testBind2 = std::bind(&testBindMemberFunc::memberFunc, &tbmf_b, std::placeholders::_2, 100, std::placeholders::_1);
    std::cout << "std::bind 绑定成员函数: " << testBind2(20, 21) << std::endl;

    return 0;
}