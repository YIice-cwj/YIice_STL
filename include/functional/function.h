#pragma once
#include <stdexcept>  // 用于 std::runtime_error
#include "../memory/unique_ptr.h"
#include "../type_traits/decay.h"
#include "../utility/forward.h"

namespace stl {

// 自定义异常类
class bad_function_call : public std::runtime_error {
   public:
    bad_function_call() : std::runtime_error("错误调用函数!!!") {}
};

template <typename T>
class function {};

/**
 * @brief 函数对象
 */
template <typename R, typename... Args>
class function<R(Args...)> {
    using return_type = R;  // 返回类型

   private:
    struct call_base {
        virtual ~call_base() = default;

        /**
         * @brief 调用可调用对象
         * @param args 可调用对象参数
         */
        virtual return_type call(Args... args) = 0;

        virtual call_base* clone() const = 0;
    };

    template <typename F>
    struct call_derived : call_base {
        using function_type = F;
        function_type function_;

        call_derived(const function_type& f) : function_(f) {}

        call_derived(function_type&& f)
            : function_(forward<function_type>(f)) {}

        /**
         * @brief 调用可调用对象
         * @param args 可调用对象参数
         */
        virtual return_type call(Args... args) override {
            return function_(forward<Args>(args)...);
        }

        virtual call_base* clone() const override {
            return new call_derived(*this);
        }
    };

    unique_ptr<call_base> call_;  // 存储可调用对象

   public:
    function() : call_(nullptr) {}

    template <typename Func>
    function(Func&& func)
        : call_(make_unique<call_derived<decay_t<Func>>>(forward<Func>(func))) {
    }

    function(const function& other) {
        if (other.call_) {
            call_.reset(other.call_->clone());
        }
    }

    function(function&& other) noexcept : call_(move(other.call_)) {}

    function& operator=(const function& other) {
        if (this != &other) {
            if (other.call_) {
                call_.reset(other.call_->clone());
            } else {
                call_.reset();
            }
        }
        return *this;
    }

    function& operator=(function&& other) noexcept {
        if (this != &other) {
            call_ = move(other.call_);
        }
        return *this;
    }

    explicit operator bool() const { return call_ != nullptr; }

    return_type operator()(Args&&... args) {
        if (!call_) {
            throw bad_function_call();
        }
        return call_->call(forward<Args>(args)...);
    }
};

}  // namespace stl