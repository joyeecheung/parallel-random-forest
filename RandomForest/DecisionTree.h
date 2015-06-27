#include "Config.cpp"

#include <chrono>
#include <random>
class Counter {
public:
    Counter(Labels &y, const Indices &ids) {
        for (auto &id : ids) {
            if (data.find(y[id]) != data.end()) {
                data[y[id]] += 1;
            } else {
                data[y[id]] = 0;
            }
        }
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
        this->value = other.value;
        this->count = other.count;
    }

    void swap(DecisionTree &other) {
        std::swap(this->left, other.left);
        std::swap(this->right, other.right);
        std::swap(this->leaf, other.leaf);
        std::swap(this->attr, other.attr);
        std::swap(this->value, other.value);
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


    void fit(Values &X, Labels &y, const Indices &ids,
             const size_t maxValues) {
        const IndicesSet features = chooseValues(FEATURE_NUM, maxValues);
        _fit(X, y, ids, features);
    }

    void _fit(Values &X, Labels &y,
              const Indices &ids, const IndicesSet &features);

    MutLabels predict(Values &X);
private:
    double gini(Labels &y, const Indices &ids);
    double gain(Values &X, Labels &y, const Indices &ids,
                const Indices &set1, const Indices &set2, double initial);
    IndicesSet chooseValues(size_t numValues, size_t maxValues);
    Indices argsort(Values &X, const Indices &ids, size_t attr);
    bool split(Values &X, const Indices &sorted_idx, size_t id_count,
               Indices &set1, Indices &set2);

    std::shared_ptr<DecisionTree> left;
    std::shared_ptr<DecisionTree> right;

    size_t attr;
    double value;
    size_t count;

    std::shared_ptr<Counter> leaf;
};