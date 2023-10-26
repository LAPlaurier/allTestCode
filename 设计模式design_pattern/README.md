参考：
1. [CS-Notes][ref1]
2. [《设计模式精解-GoF 23 种设计模式解析附 C++实现源码》][ref2]

-------------------------------------------------------------------
设计模式主要三大类：
* 创建型
* 行为型
* 结构型


## 创建型

#### [单例模式][Singleton]
* Intent: 确保一个类只有一个实例，并提供该类的全局访问点
* Class Diagram: 
使用一个私有构造函数、一个私有静态变量、一个共有静态函数实现。
私有构造函数保证外部无法通过ctor创建实例，只能通过公有静态函数返回唯一的私有静态变量。
* Implementation: 
1. 懒汉式 - 线程不安全
2. 饿汉式 - 线程安全
3. 懒汉式 - 线程安全 （对getUniqueInstance()方法加锁，一个时间点只有一个线程能进入该方法。不推荐使用，因为没拿到锁的线程*必须等待*，即使uniqueInstance已经被实例化。
4. 双重校验锁 - 线程安全



## 行为型



## 结构型






---------------------------------------------------------------

[ref1]:https://github.com/CyC2018/CS-Notes/blob/master/notes/%E8%AE%BE%E8%AE%A1%E6%A8%A1%E5%BC%8F%20-%20%E7%9B%AE%E5%BD%95.md

[ref2]:https://github.com/fifilyu/the-23-gang-of-four-design-patterns-with-cplusplus/tree/master

[Singleton]:https://github.com/CyC2018/CS-Notes/blob/master/notes/%E8%AE%BE%E8%AE%A1%E6%A8%A1%E5%BC%8F%20%20-%20%E5%8D%95%E4%BE%8B.md