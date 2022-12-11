#pragma once
#include <thread>
#include <functional>

namespace spic
{
    class ThreadWrapper
    {
        // std::thread object
        std::thread  threadHandler;
    public:
        //Delete the copy constructor
        ThreadWrapper(const ThreadWrapper&) = delete;
        //Delete the Assignment opeartor
        ThreadWrapper& operator=(const ThreadWrapper&) = delete;
        // Parameterized Constructor

        template<typename T>
        ThreadWrapper(T func) : threadHandler(func)
        {
        }

        template<typename T, typename T2>
        ThreadWrapper(T func, T2 value) : threadHandler(func, value)
        {
        }

        template<typename T, typename T2, typename T3>
        ThreadWrapper(T func, T2 value1, T3 value2) : threadHandler(func, value1, value2)
        {
        }

        // Move Constructor
        ThreadWrapper(ThreadWrapper&& obj);
        //Move Assignment Operator
        ThreadWrapper& operator=(ThreadWrapper&& obj);
        //Destructor
        ~ThreadWrapper();
    };
}
