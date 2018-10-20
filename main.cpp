#include "walker.hpp"
#include <vector>
#include <iostream>

int main() {
    std::vector<double> d = {0.4, 0.2, 0.2, 0.2};
    WalkerSampler walkerSampler(d);

    std::vector<double> count = {0, 0, 0};


    int num = 1000000;
    for (int i = 0; i< num; i++) {
        int res = walkerSampler.getSample();
        count[res]++;
    }

    std::cout << "=================" << "\n";

    std::cout << "0-th ratio: "<< count[0] / double(num) << std::endl;
    std::cout << "1-th ratio: "<< count[1] / double(num) << std::endl;
    std::cout << "2-th ratio: "<< count[2] / double(num) << std::endl;
    std::cout << "3-th ratio: "<< count[3] / double(num) << std::endl;

    return 0;
}
