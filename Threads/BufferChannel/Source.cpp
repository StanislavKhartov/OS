#include "BufferedChannel.h"
#include <thread>

using std::thread;

int main() {
    BufferedChannel<int> channel(5);
    std::vector<std::thread> threads;
    for (int i = 0; i < 7; i++) {
        threads.push_back(thread(&BufferedChannel<int>::Send, &channel, i));
    }
    threads.push_back(thread(&BufferedChannel<int>::Recv, &channel));
    threads.push_back(thread(&BufferedChannel<int>::Close, &channel));
    for (int i = 0; i < 6; i++) {
        threads.push_back(thread(&BufferedChannel<int>::Recv, &channel));
    }

    for (auto& j : threads) {
        j.join();
    }
    return 0;
}