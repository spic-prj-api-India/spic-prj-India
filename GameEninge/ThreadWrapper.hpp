#pragma once
#include <thread>
#include <functional>

namespace spic
{
    /**
     * @brief An rai class so threads can be moved and be joined when it go's out of scope
     * @details This thread has support for threads with zero, one and two variables
    */
    class ThreadWrapper
    {
        // std::thread object
        std::thread threadHandler;
    public:
        //Delete the copy constructor
        ThreadWrapper(const ThreadWrapper&) = delete;
        //Delete the Assignment opeartor
        ThreadWrapper& operator=(const ThreadWrapper&) = delete;
        // Parameterized Constructor

        /**
         * @brief Constructor
         * @tparam T An function or lambda that the thread has to complete
         * @param func 
        */
        template<typename T>
        ThreadWrapper(T func) : threadHandler(func)
        {
        }

        /**
         * @brief Constructor
         * @tparam T An function or lambda that the thread has to complete
         * @tparam T2 An value/object
         * @param func 
         * @param value 
        */
        template<typename T, typename T2>
        ThreadWrapper(T func, T2 value) : threadHandler(func, value)
        {
        }

        /**
         * @brief Constructor
         * @tparam T An function or lambda that the thread has to complete
         * @tparam T2 An value/object
         * @tparam T3 An value/object
         * @param func 
         * @param value1 
         * @param value2 
        */
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
