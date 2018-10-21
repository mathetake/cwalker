#ifndef C_WALKER
#define C_WALKER

#include <vector>
#include <map>
#include <random>

class WalkerSampler {
    std::mt19937 seed;
    int size;
    std::map<int, double> probabilities;
    std::map<int, int> alias;
public:
    explicit WalkerSampler(std::vector<double>);
    int getSample();
};

#endif
