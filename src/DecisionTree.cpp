#include "DecisionTree.h"

void DecisionTree::fit(Values &X, Labels &y, const Indices &ids,
         const size_t &maxValues) {
    const IndicesSet features = chooseValues(FEATURE_NUM, maxValues);
#ifdef DEBUG_TREE
    printf("Chosen features: ");
    for (auto &f : features) {
        printf("%d ", f);
    }
    printf("\n");
#endif
    _fit(X, y, ids, features);
}

// ids: ids to avalable data rows
// features: ids to sampled features
void DecisionTree::_fit(Values &X, Labels &y,
                        const Indices &ids, const IndicesSet &features) {
    if (ids.size() == 0) {
        return; // leaves
    }

    // get the best feature to split
    double best_score = 0.0, best_value, score;
    size_t best_attr;
    Indices best_set1, best_set2;

    if (ids.size() > MIN_NODE_SIZE){
        double initial = gini(y, ids);
#ifdef DEBUG_TREE
        //printf("======================================\n");
        //printf("Initial gini: %f\n", initial);
#endif
        // Note: if features.size() == 0, best_score = 0.0
        for (auto &attr : features) {
            // choose the threshold
            const Indices sorted_idx = argsort(X, ids, attr);
            size_t id_count = sorted_idx.size();
            double threshold = X[sorted_idx[id_count / 2]][attr];
            // divide the data set into two sets
            Indices set1, set2;
            bool missed = split(X, sorted_idx, set1, set2, attr);
            //bool missed = split(X, sorted_idx, id_count, set1, set2);

            // get the score of this attribute
            if (missed || set1.size() == 0 || set2.size() == 0) {
                score = 0.0;
            } else {
                score = gain(X, y, ids, set1, set2, initial);
            }

            // update best score
            if (score > best_score) {
                {
                    best_score = score;
                    best_attr = attr;
                    best_value = threshold;
                    best_set1 = set1;
                    best_set2 = set2;
                }

            }
        }
    }

    if (best_score > 0.0) {  // more attributes to test
        IndicesSet new_attr = features;
        new_attr.erase(best_attr);
        this->left = shared_ptr<DecisionTree>(new DecisionTree);
        this->right = shared_ptr<DecisionTree>(new DecisionTree);
        this->left->_fit(X, y, best_set1, new_attr);
        this->right->_fit(X, y, best_set2, new_attr);

        this->attr = best_attr;
        this->threshold = best_value;
        this->count = ids.size();
#ifdef DEBUG_TREE
        printf("Select %d = %f as the split point for %d samples\n", best_attr, best_value, count);
#endif
    } else { // all attributes tested
        this->leaf = shared_ptr<Counter>(new Counter(y, ids));
#ifdef DEBUG_TREE
        printf("This is the leave\n");
        leaf->print();
#endif
        this->count = ids.size();
    }
}


MutLabels DecisionTree::predict(Values &X) {
    int total = X.size();
    MutLabels y(total);
    // TODO: parallel
    for (int i = 0; i < total; ++i) {
        y[i] = predict(X[i]);
    }
    return y;
}

int DecisionTree::predict(Row &x) {
    if (leaf != nullptr) {  // leaf
        return leaf->getMostFrequent();
    }

    double value = x[attr];
    if (value < threshold) {
        return left->predict(x);
    } else {
        return right->predict(x);
    }
}


double DecisionTree::gini(Labels &y, const Indices &ids) {
    size_t total = ids.size();
    Counter counter(y, ids);
    double imp = 0.0;
    const map<int, int> &freqs = counter.data;
    double normalized_freq;
    for (auto &freq : freqs) {
        normalized_freq = (double)freq.second / total;
        imp -= normalized_freq * normalized_freq;
    }
    return imp;
}

// TODO: infomation gain
double DecisionTree::gain(Values &X, Labels &y, const Indices &ids,
                      const Indices &set1, const Indices &set2, double initial) {
    double p = (double)set1.size() / ids.size();
    double remainder = p * gini(y, set1) + (1 - p) * gini(y, set2);
    return initial - remainder;
}

IndicesSet DecisionTree::chooseValues(size_t numValues, size_t maxValues) {
    // randomly choose maxValues numbers from [0, numValues - 1]
    Indices idx(numValues);
    unsigned seed = std::chrono::system_clock::now().time_since_epoch().count();

    for (size_t i = 0; i < numValues; ++i) idx[i] = i;
    std::shuffle(idx.begin(), idx.end(), std::default_random_engine(seed));

    return IndicesSet(idx.begin(), idx.begin() + maxValues);
}

// sort ids by values
Indices DecisionTree::argsort(Values &X, const Indices &ids, size_t attr) {
    // initialize original index locations
    Indices idx(ids.begin(), ids.end());

    // sort indexes based on comparing values in v
    sort(idx.begin(), idx.end(),
         [&X, &attr](size_t i1, size_t i2) {
        return X[i1][attr] < X[i2][attr];
    });

    return idx;
}

bool DecisionTree::split(Values &X, const Indices &sorted_idx,
           Indices &set1, Indices &set2, size_t attr) {
    // check if out of range
    int id_count = sorted_idx.size();
    double threshold = X[sorted_idx[id_count / 2]][attr];
    if (X[sorted_idx[id_count - 1]][attr] < threshold || X[sorted_idx[0]][attr] > threshold) {
        return true;
    }

    set1 = Indices(sorted_idx.begin(), sorted_idx.begin() + id_count / 2);

    if (id_count > 1) {
        set2 = Indices(sorted_idx.begin() + id_count / 2, sorted_idx.end());
    } else {
        set2 = Indices();
    }
    return false;
}

void DecisionTree::print(int indent) {
    if (leaf != nullptr) {
        leaf->print(0);
    } else {
        printf("%d < %f ? (%d)\n", attr, threshold, count);
        for (int i = 0; i < indent + 3; ++i) printf(" ");
        printf("T->");
        left->print(indent + 3);
        for (int i = 0; i < indent + 3; ++i) printf(" ");
        printf("F->");
        right->print(indent + 3);
    }
}
