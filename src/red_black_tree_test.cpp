#include "red_black_tree.h"
#include <iostream>
#include <chrono>
#include <random>

int main() {
    std::cout << "Test of a left-leaning red-black tree implementation\n";
    std::cout << "----------------\n";
    std::cout << "Basic check: \n";
    // prepare to fill with random data
    std::random_device dev;
    std::mt19937 rng(dev());

    {
        std::uniform_int_distribution<std::mt19937::result_type> dist_small(std::numeric_limits<int>::min()/100000,std::numeric_limits<int>::max()/100000);

        const int NUM_ELEMENTS = 16;
        std::cout << "- Fill tree with "<<NUM_ELEMENTS<<" random elements\n";
        std::cout << "- Print tree\n";
        red_black_tree<int,int> rbt;
        for(int i=0; i<NUM_ELEMENTS; ++i) {
            rbt.put(dist_small(rng), i);
        }

        std::cout << rbt;
    }


    std::cout << "----------------\n";
    std::cout << "Performance check: \n";
    std::cout << "- Execute N initial put operations with random data\n";
    std::cout << "- Calculate how fast further put operations are by executing 1000 more\n";
    std::cout << "- Multiply N by 10\n\n";

    {
        std::uniform_int_distribution<std::mt19937::result_type> dist_int(std::numeric_limits<int>::min(),
                                                                          std::numeric_limits<int>::max());

        int iter = 0;
        const int max_iter = 6; // how many times to multiply number of initial random insertions by 10
        while (iter < max_iter) {
            red_black_tree<int, int> rbt;
            auto start_time = std::chrono::high_resolution_clock::now();
            const int num_initial_puts = 1000 * static_cast<int>(pow(10, iter));
            for (int i = 0; i < num_initial_puts; ++i) {
                rbt.put(dist_int(rng), i);
            }
            std::chrono::duration<double> exec_duration = std::chrono::high_resolution_clock::now() - start_time;
            std::cout << num_initial_puts << " initial puts with random keys took " << exec_duration.count() * 1000
                      << " ms\n";

            std::cout << "1000 more puts took ";
            start_time = std::chrono::high_resolution_clock::now();
            for (int i = 0; i < 1000; ++i) {
                rbt.put(dist_int(rng), i);
            }
            exec_duration = std::chrono::high_resolution_clock::now() - start_time;
            std::cout << exec_duration.count() * 1000 << " ms (" << exec_duration.count() / 1000 * 1e6
                      << " us/put)\n---\n";

            ++iter;
        }
    }

    return 0;
}
