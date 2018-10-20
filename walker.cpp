#include "walker.hpp"
#include <ctime>
#include <random>
#include <vector>
#include <iostream>


/*
 *
 * initialize the sampler for given probabilities.
 *
 */
WalkerSampler::WalkerSampler(std::vector<double> ws) {
    // initialize seed and size
    seed = std::mt19937(static_cast<unsigned int>(time(nullptr)));
    size = int(ws.size());

    // create two work lists
    std::vector<int> small, large;

    for (int i = 0; i < size; i++) {
        ws[i] *= double(size);

        if (ws[i] < 1.0) {
            small.push_back(i);
        } else {
            large.push_back(i);
        }
    }

    while (!small.empty()) {
        for (int i = 0; i < small.size(); i++) {
            std::cout << i << "-th small: " << small[i] << std::endl;
        }

        for (int i = 0; i < large.size(); i++) {
            std::cout << i << "-th large: " << large[i] << std::endl;
        }

        int l = small[small.size()-1];
        small.pop_back();

        int g = large[large.size()-1];
        large.pop_back();


        probabilities[l] = ws[l];
        alias[l] = g;
        ws[g] = (ws[g] + probabilities[l]) - 1;

        if (ws[g] < 1) {
            small.push_back(g);
        } else {
            large.push_back(g);
        }

        std::cout << l <<"-th probability: " << probabilities[l] << std::endl;
        std::cout << "=======================\n";
    }


    while (!large.empty()) {
        probabilities[large[large.size()-1]] = 1.0;
        large.pop_back();
    }

    for (int i = 0; i < probabilities.size(); i++) {
        std::cout << i << "-th alias: " << alias[i] << std::endl;
        std::cout << i << "-th probabilities: " << probabilities[i] << std::endl;
    }
}


/*
 *
 * generate a random sample with O(1) complexity.
 *
 */
int WalkerSampler::getSample() {
    std::uniform_int_distribution<int> idist(0, size);
    std::uniform_real_distribution<> rdist(0.0, 1.0);

    // selected `bin`
    int idx = idist(seed);

    if (rdist(seed) < probabilities[idx]) {
        return idx;
    } else {
        return alias[idx];
    }
}