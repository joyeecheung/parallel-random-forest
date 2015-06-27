#include "Config.cpp"
#include "DecisionTree.h"
#include <fstream>
#include <sstream>
#include <cstdlib>

class RandomForest {
public:
    RandomForest(size_t numOfTrees, size_t maxValues, size_t numLabels,
                 double sampleCoeff);
    void fit();
    Indices sample(const Indices &ids);
    MutLabels predict(Values &X);
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
};