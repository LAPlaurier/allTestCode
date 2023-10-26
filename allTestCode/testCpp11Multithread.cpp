/*
 * 测试C++11多线程
 * 
 * ref: https://blog.csdn.net/sjc_0910/article/details/118861539
 */

#include <iostream>
#include <thread>
#include <mutex>
#include <atomic>


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

// ------------------------------------------------------------------------------------
// 多个线程

int g_n = 0;
void countNum() {
    for (int i = 0; i < 10000; i++) {
        g_n++;
    }
}

std::mutex g_mtx;
void countNumWithMutex() {
    for (int i = 0; i < 10000; i++) {
        g_mtx.lock();
        g_n++;
        g_mtx.unlock();
    }
}

void countNumWithGuardLock() {
    for (int i = 0; i < 10000; i++) {
        std::lock_guard<std::mutex> lock(g_mtx);
        g_n++;
    }
}

// std::atomic_int an = 0;  // atomic的拷贝构造、拷贝赋值都被删除禁用
// std::atomic<int> an(0);
std::atomic_int an(0);
void countNumWithAtomic() {
    for (int i = 0; i < 10000; i++) {
        an++;
    }
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
        // std::cout << nums[i] << std::endl;
    }

    // -----------------------------------
    // 多线程
    for (std::thread &x : th) 
        x = std::thread(countNumWithGuardLock);
    for (std::thread &x : th) {
        x.join();
    }
    // 多线程执行顺序：并发、无序  =>  多线程同时操作同一个变量，肯定出错
    // 并发编程三要素：1.原子性 2.有序性 3.可见性
    // std::cout << g_n << std::endl;
    // 原子操作
    std::cout << an << std::endl;


    return 0;
}