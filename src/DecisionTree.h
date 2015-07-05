#ifndef DECISION_TREE_H
#define DECISION_TREE_H

#include "Config.h"

#include <chrono>
#include <random>
class Counter {
public:
    Counter(Labels &y, const Indices &ids) {
        for (auto &id : ids) {
            if (data.find(y[id]) != data.end()) {
                data[y[id]] += 1;
            } else {
                data[y[id]] = 1;
            }
        }
    }

    Counter(Labels &y) {
        for (auto &label : y) {
            if (data.find(label) != data.end()) {
                data[label] += 1;
            } else {
                data[label] = 1;
            }
        }
    }

    int getMostFrequent() const {
        std::vector<pair<int, int>> pairs(data.begin(), data.end());
        std::sort(pairs.begin(), pairs.end(), [=](const pair<int, int>& a, const pair<int, int>& b) {
                return a.second > b.second;
            }
        );
        return pairs.begin()->first;
    }

    void print(int indent = 0) {
        for (int i = 0; i < indent; ++i) printf(" ");
        for (auto &kv : data) {
            printf("%d: %d, ", kv.first, kv.second);
        }
        printf("\n");
    }

    map<int, int> data;
};

class DecisionTree {

public:
    DecisionTree() : left(nullptr), right(nullptr), leaf(nullptr) {}
    // rules of three

    DecisionTree(const DecisionTree &other) {
        this->left = other.left;
        this->right = other.right;
        this->leaf = other.leaf;
        this->attr = other.attr;
        this->threshold = other.threshold;
        this->count = other.count;
    }

    void swap(DecisionTree &other) {
        std::swap(this->left, other.left);
        std::swap(this->right, other.right);
        std::swap(this->leaf, other.leaf);
        std::swap(this->attr, other.attr);
        std::swap(this->threshold, other.threshold);
        std::swap(this->count, other.count);
    }

    DecisionTree &operator=(const DecisionTree &other) {
        DecisionTree temp(other);
        temp.swap(*this);
        return *this;
    }

    ~DecisionTree() {
        // all automatically recycled
    }

    void print(int indent = 2);

    void fit(Values &X, Labels &y, const Indices &ids,
             const size_t &maxValues);

    void _fit(Values &X, Labels &y,
              const Indices &ids, const IndicesSet &features);

    MutLabels predict(Values &X);
    int predict(Row &x);
private:
    double gini(Labels &y, const Indices &ids);
    double gain(Values &X, Labels &y, const Indices &ids,
                const Indices &set1, const Indices &set2, double initial);
    IndicesSet chooseValues(size_t numValues, size_t maxValues);
    Indices argsort(Values &X, const Indices &ids, size_t attr);
    bool split(Values &X, const Indices &sorted_idx,
               Indices &set1, Indices &set2, size_t attr);

    std::shared_ptr<DecisionTree> left;
    std::shared_ptr<DecisionTree> right;

    size_t attr;
    double threshold;
    size_t count;

    std::shared_ptr<Counter> leaf;
};

#endif
