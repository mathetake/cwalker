#include "walker.hpp"
#include <ctime>
#include <random>
#include <vector>
#include <iostream>


/*
 *
 * Initialize the sampler for given probabilities.
 * We implemented the algorithm in `Vose's Alias Method`
 * in http://www.keithschwarz.com/darts-dice-coins/
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

    while (small.empty() || large.empty()) {
        for (int i = 0; i < small.size(); i++) {
            std::cout << i << "-th small: " << small[i] << std::endl;
        }

        for (int i = 0; i < large.size(); i++) {
            std::cout << i << "-th large: " << large[i] << std::endl;
        }

        int l = small[small.size()-1];
        double pl =  ws[l];
        small.pop_back();

        int g = large[large.size()-1];
        double pg = ws[g];
        large.pop_back();


        probabilities[l] = pl;
        alias[l] = g;
        ws[g] = (pg + pl) - 1;

        if (ws[g] < 1) {
            small.push_back(g);
        } else {
            large.push_back(g);
        }
    }


    while (!large.empty()) {
        probabilities[large[large.size()-1]] = 1.0;
        large.pop_back();
    }

    while (!small.empty()) {
        probabilities[small[small.size()-1]] = 1.0;
        small.pop_back();
    }
}


/*
 * generate a random sample with O(1) complexity.
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