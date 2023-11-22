#include <coroutine>
#include <iostream>
#include <fmt/core.h>
struct promise;
struct coroutine : std::coroutine_handle<promise>
{ using promise_type = ::promise; };
 
struct promise
{
    coroutine get_return_object(){ 
        return {coroutine::from_promise(*this)}; 
    }
    std::suspend_always initial_suspend() noexcept { return {}; }
    std::suspend_always final_suspend() noexcept { return {}; }
    void return_void() {}
    void unhandled_exception() {}
};
 
struct S
{
    int i;
    coroutine f()
    {
        std::cout << i;
        co_return;
    }
};
 
void bad1()
{
    coroutine h = S{0}.f();
    // S{0} 被销毁
    h.resume(); // 协程恢复并执行了 std::cout << i ，这释放后使用了 S::i
    h.destroy();
}
 
coroutine bad2()
{
    S s{0};
    return s.f(); // 返回的协程不能被恢复执行，否则会导致释放后使用
}
 
void bad3()
{
    coroutine h = [i = 0]() -> coroutine // 一个 lambda ，同时也是个协程
    {
        std::cout << i;
        co_return;
    }(); // 立即调用
    // lambda 被销毁
    h.resume(); // 释放后使用了 (anonymous lambda type)::i
    h.destroy();
}
 
void good()
{
    coroutine h = [](int i) -> coroutine // i 是一个协程形参
    {
        std::cout << i;
        co_return;
    }(0);
    // lambda 被销毁
    h.resume(); // 没有问题， i 已经作为按值传递的参数被复制到协程帧中
    h.destroy();
}

int main() {
    fmt::println("hello");
    good();
    // bad1();
    // auto res = bad2();
    // res.resume();
}