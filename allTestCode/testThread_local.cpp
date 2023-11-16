#include <iostream>
#include <thread>
#include <mutex>

/* thread_local 使用实例 */


// 1. 全局thread_local
// 可以看出全局的thread_local变量在每个线程里分别自加，互不干扰
/*
std::mutex cout_mutex;  // 方便多线程打印

thread_local int x = 1;

void thread_func(const std::string& thread_name) {
    for (int i = 0; i < 3; ++i) {
        x++;
        std::lock_guard<std::mutex> lock(cout_mutex);
        std::cout << "thread[" << thread_name << "]: x = " << x << std::endl;
    }
    return ;
}

int main() {
    std::thread t1(thread_func, "t1");
    std::thread t2(thread_func, "t2");

    t1.join();
    t2.join();
    return 0;
}
*/



// 2. 局部thread_local
// （1）印证thread_local变量默认是static的。可以看出虽然x是局部变量，但是在线程的for循环中，始终是在同一个x上自加。
// （2）thread_local改变了变量的存储周期，但没有改变变量的使用周期/作用域。即在for循环外不能使用变量x，否则编译出错。
/*
std::mutex cout_mutex;

void thread_func(const std::string& thread_name) {
    for (int i = 0; i < 3; ++i) {
        thread_local int x = 1; // 局部thread_local
        x++;
        std::lock_guard<std::mutex> lock(cout_mutex);
        std::cout << "thread[" << thread_name << "]: x = " << x << std::endl;
    }
    // x++;     // 'x' was not declared in this scope
    return ;
}

int main() {
    std::thread t1(thread_func, "t1");
    std::thread t2(thread_func, "t2");

    t1.join();
    t2.join();
}
*/


// 3. 类对象
// 类对象的使用和创建与内部类型类似，不会创建多个。这种情况在函数间或通过函数返回实例也是一样。
// thread_local变量只会在每个线程最开始被调用的时候进行初始化，且只会被初始化一次。
/*
std::mutex cout_mutex;

// 定义类
class A {
public:
    A() {
        std::lock_guard<std::mutex> lock(cout_mutex);
        std::cout << "create A" << std::endl;
    }

    ~A() {
        std::lock_guard<std::mutex> lock(cout_mutex);
        std::cout << "destroy A" << std::endl;
    }

    int counter = 0;
    int get_value() {
        return counter++;
    }
};

// 通过函数返回实例
A* createA() {
    return new A();
}

void loopin_func(const std::string& thread_name) {
    // createA() 看上去被调用了多次，实际上只被调用了一次，因为thread_local变量只会在每个线程最开始被调用的时候进行初始化，且只会被初始化一次。
    // thread_local A* a = createA();

    // 如果改为赋值，则情况不同
    thread_local A* a;
    a = createA();
    std::lock_guard<std::mutex> lock(cout_mutex);
    std::cout << "thread[" << thread_name << "]: a.counter: " << a->get_value() << std::endl;
}

void thread_func(const std::string& thread_name) {
    for (int i = 0; i < 3; ++i) {
        // thread_local A* a = new A();
        // std::lock_guard<std::mutex> lock(cout_mutex);
        // std::cout << "thread[" << thread_name << "]: a.counter: " << a->get_value() << std::endl;
        loopin_func(thread_name);
    }
    return;
}

int main() {
    std::thread t1(thread_func, "t1");
    std::thread t2(thread_func, "t2");

    // thread_func("t1");

    t1.join();
    t2.join();
    return 0;
}
*/


// 4. 类成员变量
// 规定：thread_local作为类成员变量时，必须是static的。必须显式声明thread_local的类成员变量是static的。

std::mutex cout_mutex;

class B {
public:
    B() {
        std::lock_guard<std::mutex> lock(cout_mutex);
        std::cout << "create B" << std::endl;
    }
    ~B() {}
    thread_local static int b_key;  // thread_local的static，每个线程中有一个
    // thread_local int b_key;
    int b_value = 24;
    static int b_static;    // 真正的static，全局只有一个，所有线程共享这个变量
};

thread_local int B::b_key = 12;
int B::b_static = 36;

void thread_func(const std::string& thread_name) {
    B b;
    for (int i = 0; i < 3; ++i) {
        b.b_key--;
        b.b_value--;
        b.b_static--;
        std::lock_guard<std::mutex> lock(cout_mutex);
        std::cout << "thread[" << thread_name << "]: b_key:" << b.b_key << ", b_value:" << b.b_value << ", b_static:" << b.b_static << std::endl;
        std::cout << "thread[" << thread_name << "]: B::key:" << B::b_key << ", b_value:" << b.b_value << ", B::b_static: " << B::b_static << std::endl;
    }
    return;
}

int main() {
    std::thread t1(thread_func, "t1");
    std::thread t2(thread_func, "t2");

    t1.join();
    t2.join();
    return 0;
}