#include <barrier>
#include <algorithm>
#include <iostream>
#include <vector>
#include <thread>
#include <mutex>

#include "LychrelData.h"

struct Record {
    Number n;
    Number palindrome;
};
using Records = std::vector<Record>;

const size_t MaxIterations = 7500;
const size_t MaxThreads = 10;

int main() {
    LychrelData data;
    std::cerr << "Processing " << data.size() << " values ...\n";

    size_t maxIter = 0;
    Records records;

    std::barrier barrier{ MaxThreads };
    std::mutex mutex;

    // Create and launch threads to process data chunks in parallel
    std::vector<std::thread> threads;
    size_t chunkSize = (data.size() + MaxThreads - 1) / MaxThreads; // Calculate chunk size

    for (int id = 0; id < MaxThreads; ++id) {
        threads.emplace_back([&data, &records, &mutex, &maxIter, &barrier, id, chunkSize]() {
            auto start = id * chunkSize;
            auto end = std::min(data.size(), start + chunkSize);

            for (size_t i = start; i < end; ++i) {
                size_t iter = 0;
                Number number = data[i];
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
                            if (carry) { v -= 10; }
                            return v;
                        }
                    );

                    if (carry) { sum.push_front(1); }

                    n = sum;
                }

                {
                    std::lock_guard lock(mutex);
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

            barrier.arrive_and_wait();
        });
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