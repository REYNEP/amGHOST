#pragma once
#include <thread>
#include <atomic>  // For std::atomic
#include <utility> // For std::forward
#include "REY_Logger.hh"

class amTHREAD {
  public:
    std::thread phoenix;                           // The std::thread
    std::atomic<bool> m_isFunctionRunning = false; // The std::Atomic flag to track function state
                bool    isFunctionRunning() const  {return this->m_isFunctionRunning.load();}

    amTHREAD() {}
   ~amTHREAD() {}

    template <typename  _USER_FUNC_, typename... _USER_ARGS_>
    void            run(_USER_FUNC_&& user_func, _USER_ARGS_&&... user_args)
    {
        if (phoenix.joinable()) {
            REY_LOG_EX("Thread is already running. must call amTHREAD::wait_till_function_returns() first 💁‍♀️");
            return;
        }

        // ========== amTHREAD WRAPPER FUNCTION ==========
            auto wrap_func = [this, user_func = std::forward<_USER_FUNC_>(user_func)](_USER_ARGS_&&... wrap_args) {
                this->m_isFunctionRunning = true;
                    try {
                        user_func(std::forward<decltype(wrap_args)>(wrap_args)...);
                    } catch (const std::exception& e) {
                        REY_LOG_EX("Exception in thread: " << e.what());
                    } catch (...) {
                        REY_LOG_EX("Unknown exception in thread.");
                    }
                this->m_isFunctionRunning = false;
            };
        // ========== amTHREAD WRAPPER FUNCTION ==========

        this->phoenix = std::thread(std::move(wrap_func), std::forward<_USER_ARGS_>(user_args)...);
    }

    /** Block the `current thread` (one that calls this function) untill this other thread (`amTHREAD::phoenix`) has completed/returned 💁‍♀️ */
    void wait_till_function_returns(void) {
        if (phoenix.joinable()) {
            phoenix.join();
        }
        else {
            REY_LOG_EX("Thread is not JOINABLE. Might have already been joined/detached/smth-else >_<");
        }
    }
};