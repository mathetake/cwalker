#include "walker.hpp"
#include <ctime>
#include <random>
#include <vector>


/*
 * Initialize the sampler for given probabilities.
 * We implemented the algorithm in `Vose's Alias Method`
 * in http://www.keithschwarz.com/darts-dice-coins/
 */
WalkerSampler::WalkerSampler(std::vector<double> ws) {
    // initialize seed and size
    seed = std::mt19937(static_cast<unsigned int>(time(nullptr)));
    size = ws.size();

    // create two work lists
    std::vector<size_t> small, large;

    for (auto i = 0; i < size; ++i) {
        ws[i] *= double(size);

        if (ws[i] < 1.0) {
            small.push_back(i);
        } else {
            large.push_back(i);
        }
    }

    while (!(small.empty() || large.empty())) {

        size_t l = small.back();
        double pl =  ws[l];
        small.pop_back();

        size_t g = large.back();
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
size_t WalkerSampler::getSample() {
    std::uniform_int_distribution<size_t > idist(0, size - 1);
    std::uniform_real_distribution<> rdist(0.0, 1.0);

    // selected `bin`
    size_t idx = idist(seed);

    if (rdist(seed) < probabilities[idx]) {
        return idx;
    } else {
        return alias[idx];
    }
}
