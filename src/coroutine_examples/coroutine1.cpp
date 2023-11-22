#include <iostream>
#include <coroutine>
#include <fmt/core.h>

struct SimpleCoroutine {
    struct promise_type {
        SimpleCoroutine get_return_object() {
            return SimpleCoroutine(std::coroutine_handle<promise_type>::from_promise(*this));
        }

        std::suspend_never initial_suspend() {
            return {};
        }

        std::suspend_never final_suspend() noexcept {
            return {};
        }

        void return_void() {}

        void unhandled_exception() {
            std::terminate();
        }
    };

    std::coroutine_handle<promise_type> coroutine;

    explicit SimpleCoroutine(std::coroutine_handle<promise_type> coro) : coroutine(coro) {}

    ~SimpleCoroutine() {
        if (coroutine)
            coroutine.destroy();
    }
};

SimpleCoroutine simpleCoroutine() {
    fmt::print("Coroutine Started\n");
    co_await std::suspend_always{};
    fmt::print("Coroutine Resumed\n");
}

int main() {
    {
        SimpleCoroutine coro = simpleCoroutine();
        fmt::print("Main Function\n");
        coro.coroutine.resume();
        fmt::print("Main Function After Resuming Coroutine\n");
    } // 协程对象在这里离开作用域，会调用其析构函数

    return 0;
}
