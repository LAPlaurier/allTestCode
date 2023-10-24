/*
 * 测试Redis-plus-plus库
 * 编译时：
 * 使用静态库 g++ -std=c++17 -o app app.cpp /path/to/libredis++.a /path/to/libhiredis.a -pthread
 * 使用动态库 g++ -std=c++17 -o app app.cpp -lredis++ -lhiredis -pthread
 *
 * 
 * link: https://github.com/sewenew/redis-plus-plus#run-tests-optional
 */


#include <iostream>
#include <exception>
#include <sw/redis++/redis++.h>

using namespace sw::redis;



int main() {
    // std::cout << "test" << std::endl;
    try {
        // Create an Redis object, which is movable but NOT copyable.
        // 创建的Redis object的操作是在本地的redis上进行的。所有在terminal用redis-cli可以查看所有更改
        Redis redis("tcp://127.0.0.1:6379");

        // ***** STRING commands *****
        redis.set("key2", "val1");
        auto val = redis.get("key");
        if (val) {
            std::cout << *val << std::endl;
        } else {
            throw std::runtime_error("key doesn't exist.");
        }
    } catch (const std::runtime_error &e) {
        std::cerr << "ERROR: " << e.what() << std::endl;
    }
    return 0;
}