#include "gtest/gtest.h"
#include "walker.hpp"
#include <vector>

const double threshold = 10e-4;
const int sampleNum = 1000000;

void verifySamples(std::vector<double> counts, std::vector<double> data) {
    for (auto i = 0; i < counts.size(); ++i ) {
        double diff = (counts[i] / double(sampleNum)) - data[i];
        if (diff < 0) {
            diff = - diff;
        }
        EXPECT_EQ(true, diff < threshold);
    }
}

TEST(WalkerTest, TestGetSampler1) {
    std::vector<double> data = {0.1, 0.1, 0.8};
    std::vector<double> counts = {0, 0, 0};

    WalkerSampler sampler (data);
    for (auto i = 0; i< sampleNum; ++i) {
        size_t res = sampler.getSample();
        counts[res]++;
    }
    verifySamples(counts, data);
}


TEST(WalkerTest, TestGetSampler2) {
    std::vector<double> data = {0.2, 0.2, 0.4, 0.2};
    std::vector<double> counts = {0, 0, 0, 0};

    WalkerSampler sampler (data);
    for (auto i = 0; i< sampleNum; ++i) {
        size_t res = sampler.getSample();
        counts[res]++;
    }
    verifySamples(counts, data);
}


TEST(WalkerTest, TestGetSampler3) {
    std::vector<double> data = {0.1, 0.1, 0.05, 0.05, 0.7};
    std::vector<double> counts = {0, 0, 0, 0, 0};

    WalkerSampler sampler (data);
    for (auto i = 0; i< sampleNum; ++i) {
        size_t res = sampler.getSample();
        counts[res]++;
    }
    verifySamples(counts, data);
}

