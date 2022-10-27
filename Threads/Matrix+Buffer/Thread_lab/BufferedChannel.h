#pragma once

#include <queue>
#include <mutex>
#include <condition_variable>

template<class T>
class BufferedChannel {
public:
    explicit BufferedChannel(int size);

    void Send(T value);

    std::pair<T, bool> Recv();

    void Close();

private:
    std::queue<T> queue_;
    int size_;
    bool isOpen_;
    std::mutex _lock;
    std::condition_variable inputCond_;
    std::condition_variable outputCond_;
};

template<class T>
inline BufferedChannel<T>::BufferedChannel(int size)
{
    size_ = size;
    isOpen_ = true;
}

template<class T>
inline void BufferedChannel<T>::Send(T value)
{
    std::unique_lock<std::mutex> uLock(_lock);
    inputCond_.wait(uLock, [this]{return size_ < queue_.size();});
    if (isOpen_) {
        queue_.push(value);
        inputCond_.notify_one();
        uLock.unlock();
    }
    else {
        throw new std::runtime_error("Channel has been already locked!");
    }
}

template<class T>
inline std::pair<T, bool> BufferedChannel<T>::Recv()
{
    std::unique_lock<std::mutex> uLock(_lock);
    outputCond_.wait(uLock, [this]{return queue_.size() != 0;});
    T tmp = queue_.front();
    queue_.pop();
    outputCond_.notify_one();
    uLock.unlock();
    return std::pair<T, bool>(tmp, isOpen_);
}

template<class T>
inline void BufferedChannel<T>::Close()
{
    std::unique_lock<std::mutex> uLock(_lock);
    isOpen_ = false;
    uLock.unlock();
}