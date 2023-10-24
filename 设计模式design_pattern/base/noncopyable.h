#ifndef _SELF_BASE_NONCOPYABLE_H_
#define _SELF_BASE_NONCOPYABLE_H_

/*
 * 将 拷贝构造 和 拷贝赋值 都声明为private，这样不论何种派生，子类都无权访问，从而达到禁止拷贝的目的。
 * 也可以直接在public中显式删除 拷贝构造 和 拷贝赋值
 * 
 * 为什么构造函数声明成 protected ？
 * 1. 不能声明为private，不然无法构造子类实例。
 * 2. 如果声明为public，那么外部可创建noncopyable实例，但实例无意义。该类只有被继承后才有意义。
 * 3. 声明为protected，既保证外部无法直接构造无意义的noncopyable实例，又不影响构造子类实例。
 * 
 * 继承boost::noncopyable实现禁止拷贝 与 自己实现禁止拷贝 的区别：
 * 自己通过将拷贝构造和拷贝赋值声明为private来实现禁止拷贝，类自身成员仍可以访问到这两个函数。 ->  显式声明delete可解决
 * 
 * delete 与 私有不实现的区别：在使用模板函数时，只能采用delete特化，不能采用private特化。（因为模板特化应该被写在命名空间域(namespace scope)而不是类域(class scope)
*/

class noncopyable {
// C++11 delete关键字
public:
    noncopyable (const noncopyable&) = delete;
    noncopyable& operator= (const noncopyable&) = delete;

protected:  // 注意点
    noncopyable() = default;
    ~noncopyable() = default;

// C++98 私有不实现
// private:
    // noncopyable(const noncopyable&);
    // noncopyable& operator= (const noncopyable&);
};

#endif