#include <algorithm>
#include <iostream>
#include <vector>
#include <thread>
#include <mutex>
#include <deque>
#include <condition_variable>

#include "LychrelData.h"

struct Record {
    Number n;
    Number palindrome;
};

using Records = std::vector<Record>;

const size_t MaxIterations = 7500;
const size_t MaxThreads = 10;

std::deque<size_t> taskQueue;
std::mutex taskQueueMutex;
std::condition_variable taskAvailable;

void worker(LychrelData& data, Records& records, std::mutex& resultMutex, size_t& maxIter) {
    while (true) {
        size_t index;
        {
            std::unique_lock<std::mutex> lock(taskQueueMutex);
            taskAvailable.wait(lock, [&data] { return !taskQueue.empty() || data.available() == 0; });
            if (taskQueue.empty() && data.available() == 0) {
                // No more tasks to process, exit the thread
                return;
            }
            index = taskQueue.front();
            taskQueue.pop_front();
        }

        size_t iter = 0;
        Number number = data[index];
        Number n = number;

        while (!n.is_palindrome() && ++iter < MaxIterations) {
            Number sum(n.size());
            Number r = n.reverse();
            auto rd = n.begin();
            bool carry = false;

            std::transform(n.rbegin(), n.rend(), sum.rbegin(),
                [&](auto d) {
                    auto v = d + *rd++ + carry;
                    carry = v > 9;
                    if (carry) {
                        v -= 10;
                    }
                    return v;
                }
            );

            if (carry) {
                sum.push_front(1);
            }

            n = sum;
        }

        {
            std::lock_guard lock(resultMutex);
            if (!(iter < maxIter || iter == MaxIterations)) {
                Record record{ number, n };
                if (iter > maxIter) {
                    records.clear();
                    maxIter = iter;
                }

                records.push_back(record);
            }
        }
    }
}

int main() {
    LychrelData data;
    std::cerr << "Processing " << data.size() << " values ...\n";

    size_t maxIter = 0;
    Records records;

    std::vector<std::thread> threads;
    size_t chunkSize = (data.size() + MaxThreads - 1) / MaxThreads;

    std::mutex resultMutex;

    for (int id = 0; id < MaxThreads; ++id) {
        threads.emplace_back(worker, std::ref(data), std::ref(records), std::ref(resultMutex), std::ref(maxIter));
    }

    for (size_t i = 0; i < data.size(); ++i) {
        {
            std::lock_guard lock(taskQueueMutex);
            taskQueue.push_back(i);
        }
        taskAvailable.notify_one();
    }

    for (auto& thread : threads) {
        thread.join();
    }

    std::cout << "\nmaximum number of iterations = " << maxIter << "\n";
    for (auto& [number, palindrome] : records) {
        std::cout
            << "\t" << number
            << " : [" << palindrome.size() << "] "
            << palindrome << "\n";
    }
}