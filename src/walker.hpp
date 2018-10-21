#ifndef C_WALKER
#define C_WALKER

#include <vector>
#include <map>
#include <random>

class WalkerSampler {
    std::mt19937 seed;
    size_t size;
    std::map<size_t, double> probabilities;
    std::map<size_t, size_t > alias;
public:
    explicit WalkerSampler(std::vector<double>);
    size_t getSample();
};

#endif
