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
                bool  m_isThreadDetached  = false;
                bool  m_isThreadStarted   = false;

    amTHREAD() {}
   ~amTHREAD() { this->wait_till_function_returns(); }

  public:
    /** 
     * @param user_func: With templatization, any function with any parameter & return type can be called 
     * @param user_args: With templatization, any function with any parameter & return type can be called 
     */
    template <typename _CALLABLE_, typename... _ARGS_>
    void         start(_CALLABLE_&& user_func, _ARGS_&&... user_args) 
    {
        if (phoenix.joinable()) {
            REY_LOG_EX("Thread is already running. must call amTHREAD::wait_till_function_returns() first 💁‍♀️");
            return;
        }

        // ========== amTHREAD WRAPPER FUNCTION ==========
            auto wrap_func = [this, user_func = std::forward<_CALLABLE_>(user_func)](_ARGS_&&... wrap_args) {
                this->m_isFunctionRunning = true;
                    try {
                        user_func(std::forward<decltype(wrap_args)>(wrap_args)...);
                    } catch (const std::exception& e) {
                        REY_LOG_EX(std::string("Exception in thread: ") + e.what());
                    } catch (...) {
                        REY_LOG_EX("Unknown exception in thread.");
                    }
                this->m_isFunctionRunning = false;
            };
        // ========== amTHREAD WRAPPER FUNCTION ==========

        this->phoenix = std::thread(std::move(wrap_func), std::forward<_ARGS_>(user_args)...);
        m_isThreadStarted = true;
    }
    
    void wait_till_function_returns() {
        if (phoenix.joinable()) {
            phoenix.join();
        }
        else if (this->m_isThreadDetached) {
            REY_LOG_EX("Thread has been detached and is running independently. >_<");
        }
        else {
            REY_LOG_EX("Thread is not JOINABLE. Might have already been joines/detached/smth-else >_<");
        }
    }

    /**
     * Once detached:-
     *      - the thread runs independently in the background
     *      - std::thread object no longer has control over the thread
     *      - The program does not wait for the detached thread to finish before continuing or exiting
     * 
     * Advice:-
     *      - Don't use detach()
     *      - Alternative Feature to implement: Avoid detach() and Use Fire-and-Forget Threads Directly
     */
    void detach() {
        if (phoenix.joinable()) {
            phoenix.detach();
        }
        else {
            REY_LOG_EX("Thread is not JOINABLE. Can't Detach 💁‍♀️");
        }
    }
};