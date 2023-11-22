#include <coroutine>
#include <fmt/core.h>

struct promise
{
    struct promise_type {
        promise get_return_object() {
            return {std::coroutine_handle<promise_type>::from_promise(*this)};
        }
        std::suspend_never initial_suspend() noexcept {
            return {};
        }
        std::suspend_always final_suspend() noexcept {
            return {};
        }
        void return_void() {}
        void unhandled_exception() {}
    };

    std::coroutine_handle<promise_type> _h;
    /* data */
};

struct Input{
    bool await_ready() {
        return false;
    }
    void await_suspend(std::coroutine_handle<>h) { 
        fmt::println("coroutine has been stopped");
    }
    void await_resume() {}
};

int main() {
    auto lambda = []()->promise {
        Input t;
        fmt::println("笑");
        co_await t;
        fmt::println("协程执行完毕");
    };
    promise result = lambda();
    fmt::println("main");
    result._h.resume();
}



