#include "RandomForest.h"
#include <cmath>

RandomForest::RandomForest(size_t numOfTrees, size_t maxValues, size_t numLabels,
             double sampleCoeff) {
    this->numOfTrees = numOfTrees;
    this->maxValues = maxValues;
    this->numLabels = numLabels;
    this->sampleCoeff = sampleCoeff;
};

void RandomForest::fit() {
    // draw a random sample from X and y
    Indices bootstrap = sample(ids);
#pragma omp parallel for
    for (int i = 0; i < numOfTrees; ++i) {
        DecisionTree tree;
        // train a tree with the sample
        tree.fit(X, y, bootstrap, maxValues);
        // put it into the forest
        forest.push_back(tree);
    }
}

Indices RandomForest::sample(const Indices &ids) {
    size_t data_size = X.size();
    size_t sample_size = (int)(sampleCoeff * data_size);
    Indices idx;
    for (size_t i = 0; i < sample_size; ++i) {
        size_t next = rand() % data_size;
        idx.push_back(next);
    }
    return idx;
}

MutLabels RandomForest::predict(Values &X) {
    int total = X.size();
    MutLabels y(total);
    // TODO: parallel
    for (int i = 0; i < total; ++i) {
        y[i] = predict(X[i]);
    }
    return y;
}

// TODO: predictions
int RandomForest::predict(Row &x) {
    // get the prediction from all tress
    vector<int> results(numOfTrees);
    int sum;
    // TODO: parallel
    for (int i = 0; i < numOfTrees; ++i) {
        results[i] = forest[i].predict(x);
        sum += results[i];
    }
    // average
    return round((double)sum / numOfTrees);
}

bool RandomForest::loadDataSet(const char* filename, size_t idIdx, size_t labelIdx) {
    char buffer[1024];
    std::ifstream file(filename);

    if (!file) {
        return false;
    }

    string line;
    string value;
    std::getline(file, line); // first line

    // for each line
    size_t row = 0;
    while (std::getline(file, line)) {
        MutRow temp;
        std::istringstream ss(line);
        // split by commas
        size_t col = 0;
        for (size_t i = 0; i < FEATURE_NUM; ++i) {
            std::getline(ss, value, ',');
            if (i == idIdx) {  // id
                //ids.push_back(std::stoi(value));
                ids.push_back(row);
            } else if (i == labelIdx) {  // label
                y.push_back(std::stoi(value));
            } else { // value
                temp[col] = std::stod(value);
                col++;
            }
        }
        X.push_back(temp);
        row++;
    }

    return true;
}