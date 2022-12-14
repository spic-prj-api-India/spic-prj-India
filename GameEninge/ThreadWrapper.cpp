#include "ThreadWrapper.hpp"

using namespace spic;

// Move Constructor
ThreadWrapper::ThreadWrapper(ThreadWrapper&& obj) : threadHandler(std::move(obj.threadHandler))
{
}
//Move Assignment Operator
ThreadWrapper& ThreadWrapper::operator=(ThreadWrapper&& obj)
{
    if (threadHandler.joinable())
        threadHandler.join();
    threadHandler = std::move(obj.threadHandler);
    return *this;
}
// Destructor
ThreadWrapper::~ThreadWrapper()
{
    if (threadHandler.joinable())
        threadHandler.join();
}