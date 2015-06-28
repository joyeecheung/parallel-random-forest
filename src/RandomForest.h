#ifndef RANDOM_FOREST_H
#define RANDOM_FOREST_H
#include "Config.h"
#include "DecisionTree.h"

#include <fstream>
#include <sstream>
#include <cstdlib>

bool csv2data(const char* filename, MutValues &X, MutLabels &y,
              Indices &ids, int idIdx, int labelIdx = -1);

class RandomForest {
public:
    RandomForest(size_t numOfTrees, size_t maxValues, size_t numLabels,
                 double sampleCoeff);
    void fit(Values &X, Labels &y, const Indices &ids);
    Indices sample(const Indices &ids);
    MutLabels predict(Values &X);
    int predict(Row &x);
    bool loadDataSet(const char* filename, size_t idIdx, size_t labelIdx);
private:
    vector<DecisionTree> forest;
    MutValues X;
    MutLabels y;
    Indices ids;
    size_t numOfTrees;
    size_t maxValues;  // usually sqrt(FEATURE_NUM)
    size_t numLabels;
    double sampleCoeff;  // 1 would be good
    Indices bootstrap;  // bootstrap sample
};

#endif