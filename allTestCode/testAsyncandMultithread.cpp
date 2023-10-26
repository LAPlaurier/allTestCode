/*
 * thread - 想获得线程函数结果/线程函数中某个值，需要 promise & future 结合使用
 * async - 不用关注线程创建的内部细节，通过 future 能方便的获取异步执行的状态结果。还能指定线程创建策略
 *
 * 
*/


#include <iostream> // std::cout
#include <thread>   // std::thread
#include <atomic>   // std::atomic_int
#include <chrono>
#include <mutex>
#include <memory>
#include <functional>
#include <future>


// 辅助计算时间
typedef std::chrono::steady_clock               STEADY_LOCK;
typedef std::chrono::steady_clock::time_point   TIME_POINT;

void print_diff_time(const TIME_POINT& t1, const TIME_POINT& t2) {
    std::chrono::duration<double, std::milli> dTimeSpan = std::chrono::duration<double, std::milli>(t2-t1);
    std::cout << "time span: " << dTimeSpan.count() << "ms\n";
}


/* --- 原始程序，未引入多线程 --- */

// 计算A函数
int calculateA() {
    // 延迟 1 ms
    std::this_thread::sleep_for(std::chrono::milliseconds(1));
    return 1;
}

// 计算B函数
int calculateB() {
    // 延迟2ms
    std::this_thread::sleep_for(std::chrono::milliseconds(2));
    return 2;
}

// 计算C函数
int calculateC() {
    std::this_thread::sleep_for(std::chrono::milliseconds(3));
    return 3;
}

// 统计三者的和
void test_common_time() {
    TIME_POINT t1 = STEADY_LOCK::now();

    int c = calculateA() + (calculateB() + calculateC());

    TIME_POINT t2 = STEADY_LOCK::now();

    std::cout << "test_common_time result is: " << c << ", ";
    print_diff_time(t1, t2);
}


/* --- 引入多线程计算 --- */
std::mutex g_mtx;

void calA(int& num) {
    std::this_thread::sleep_for(std::chrono::milliseconds(1));
    // 多线程加锁保护
    std::lock_guard<std::mutex> lock(g_mtx);
    num += 1;
}

void calB(int& num) {
    std::this_thread::sleep_for(std::chrono::milliseconds(2));
    std::lock_guard<std::mutex> lock(g_mtx);
    num += 2;
}

void calC(int& num) {
    std::this_thread::sleep_for(std::chrono::milliseconds(3));
    std::lock_guard<std::mutex> lock(g_mtx);
    num += 3;
}

// 使用原子数据
void calAwithoutLock(std::atomic_int& num) {
    std::this_thread::sleep_for(std::chrono::milliseconds(1));
    num += 1;
}

void calBwithoutLock(std::atomic_int& num) {
    std::this_thread::sleep_for(std::chrono::milliseconds(2));
    num += 2;
}

void calCwithoutLock(std::atomic_int& num) {
    std::this_thread::sleep_for(std::chrono::milliseconds(3));
    num += 3;
}

void test_threads_time() {
    int num = 0;
    TIME_POINT time_1 = STEADY_LOCK::now();
    // 启动三个线程进行计算
    std::thread t1(calA, std::ref(num));
    std::thread t2(calB, std::ref(num));
    std::thread t3(calC, std::ref(num));

    t1.join();
    t2.join();
    t3.join();

    TIME_POINT time_2 = STEADY_LOCK::now();
    std::cout << "test_threads_time result is: " << num << ", ";
    print_diff_time(time_1, time_2);

    std::atomic_int a_num(0);
    time_1 = STEADY_LOCK::now();
    // 无锁的原子操作
    std::thread t11(calAwithoutLock, std::ref(a_num));
    std::thread t12(calBwithoutLock, std::ref(a_num));
    std::thread t13(calCwithoutLock, std::ref(a_num));

    t11.join();
    t12.join();
    t13.join();

    time_2 = STEADY_LOCK::now();
    std::cout << "test_threads_time with atomic result is: " << num << ", ";
    print_diff_time(time_1, time_2);
}


/* --- 异步调用 --- */
// C++11 引入 async 异步调用函数，其封装了异步（多线程）实现的复杂过程，将计算结果保存在future<>中，通过 get() 获取每个对象的最终结果
/*
async异步调用方式的程序更简洁，没有明显引入线程、锁、缓冲区等概念。
async异步调用函数通过启动一个新线程 or 复用一个它认为合适的已有线程。 async是语义上的并发即可，并关心具体的调用策略。
“简单性” 是 async/future 设计中最重视的一个方面； future一般也可以和线程一起使用。
不要使用async()来启动类似 IO操作，操作互斥体(mutex)，多任务交互操作等复杂任务。
*/
void test_future_time() {
    int sum = 0;

    TIME_POINT t1 = STEADY_LOCK::now();

    // 异步调用
    std::future<int> f1 = std::async(calculateA);
    std::future<int> f2 = std::async(calculateB);
    std::future<int> f3 = std::async(calculateC);
    // get() 函数会阻塞，直到结果返回
    sum = f1.get() + f2.get() + f3.get();

    TIME_POINT t2 = STEADY_LOCK::now();

    std::cout << "test_future_time result is: " << sum << ", ";
    print_diff_time(t1, t2);
}

int main() {
    // 普通调用
    test_common_time();
    // 多线程
    test_threads_time();
    // 异步调用
    test_future_time();

    return 0;
}