#include "src/walker.hpp"
#include <vector>
#include <iostream>

int main() {
    // initialize sampler
    std::vector<double> d = {0.2, 0.2, 0.4, 0.2};
    WalkerSampler walkerSampler(d);

    // generate samples
    std::vector<double> count = {0, 0, 0, 0};
    int num = 1000000;
    for (int i = 0; i< num; ++i) {
        int res = walkerSampler.getSample();
        count[res]++;
    }

    // print result
    for (int i =0; i < count.size(); ++i) {
        std::cout << i << "-th observed probability: "<< count[i] / double(num) << std::endl;
    }
    return 0;
}
