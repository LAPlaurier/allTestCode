/*
 * 测试C++11多线程
 * 
 * ref: https://blog.csdn.net/sjc_0910/article/details/118861539
 */

#include <iostream>
#include <thread>


// 基本使用
/*
void doit() {std::cout << "World!" << std::endl;}
int main() {
    std::thread a([](){
        std::cout << "Hello, " << std::flush;
    }), b(doit);

    a.join();
    b.join();

    return 0;
}
*/


// thread执行有参数的函数
/*
void countnumber(int id, unsigned int n) {
    for (unsigned int i = 1; i <= n; i++) {
        std::cout << "Thread " << id << " finished!" << std::endl;
    }
}

int main() {
    std::thread th[10];
    for (int i = 0; i < 10; i++) {
        th[i] = std::thread(countnumber, i, 3);
    }
    for (int i = 0; i < 10; i++) {
        th[i].join();
    }

    return 0;
}
*/


// *** thread执行带有引用参数的函数

// 线程的本质要求其参数必须是可复制或可移动的，因为线程函数可能在调用者的上下文之外执行。
// 如果线程函数直接接受一个引用，那么在新线程中使用该引用时，原始对象可能已经超出声明周期或被修改，导致未定义的行为。

// 所以，尽管thread的构造函数使用万能引用，传递左值给构造函数时模板参数被推导为左值引用，但该值仍会是被拷贝到线程内部的。
// 因此，线程函数实际得到的是这个拷贝，而不是原始对象的引用。

// 如果确实希望线程函数操作原始对象（通过引用），那么必须显式地使用 std::ref 告诉 std::thread 想传递一个引用。这样 std::thread 会保存一个引用，而不是对象的拷贝。
// （尽管 std::thread 的参数使用了万能引用。但由于线程的特性和安全性考虑，它默认进行拷贝。除非显式使用 std::ref

template<class T>
void changeValue(T& x, T val) {
    x = val;
}

int main() {
    std::thread th[10];
    int nums[10];
    for (int i = 0; i < 10; i++) {
        //   template<typename _Callable, typename... _Args, typename = _Require<__not_same<_Callable>>>
        //   explicit thread(_Callable&& __f, _Args&&... __args)
        //   {
        //      static_assert( __is_invocable<typename decay<_Callable>::type,
        // 			      typename decay<_Args>::type...>::value,
        //      "std::thread arguments must be invocable after conversion to rvalues"
        //   );
        // thread arguments must be invocable after conversion to rvalues | 转换为右值后，线程参数必须可调用
        // 报错的函数原型如上：传入的函数参数对应的形参是万能引用形式。


        // th[i] = std::thread(changeValue<int>, nums[i], i+1);
        th[i] = std::thread(changeValue<int>, std::ref(nums[i]), i+1);
    }

    for (int i = 0; i < 10; i++) {
        th[i].join();
        std::cout << nums[i] << std::endl;
    }

    return 0;
}