#include <vector>
#include <cstdio>
#include <cmath>
#include <fstream>
#include "Config.h"
#include "DecisionTree.h"
#include "RandomForest.h"

const int MAX_FEATURE = (int)round(sqrt(FEATURE_NUM));
const double SAMPLE_COEFF = 1.0;

int main(int argc, char *argv[]) {
    int tree_num = 1000;
    if (argc > 1) {
        tree_num = atoi(argv[1]);
    }
#ifdef JDEBUG
    printf("=======================================\n");
    printf("Initializing forest:\nSize of forest\t%d\n", tree_num);
    printf("number of sampled feature\t%d\n", MAX_FEATURE);
    printf("number of lables\t%d\n", LABLE_NUM);
#endif
    RandomForest rf(tree_num, MAX_FEATURE, LABLE_NUM, SAMPLE_COEFF);
#ifdef JDEBUG
    printf("=======================================\n");
#endif
#ifdef JDEBUG
    printf("=======================================\n");
#endif
    MutValues X, test_X;
    MutLabels y, dummy;
    Indices ids, test_ids;

    csv2data("data/train.csv", X, y, ids, 0, FEATURE_NUM + 1);
    rf.fit(X, y, ids);
    csv2data("data/1000.csv", test_X, dummy, test_ids, 0);
    Labels yhat = rf.predict(test_X);
    size_t count = yhat.size();
    
    int errors = 0;
    for (size_t i = 0; i < count; ++i) {
        if (yhat[i] != y[i]) errors++;
        printf("(%d, %d);  ", yhat[i], y[i]);
    }
    printf("\nErrors: %d, %f\n", errors, (double)errors/count);
    //std::ofstream out("data/submit.csv");
    //out << "id,label\n";
    //for (size_t i = 0; i < count; ++i) {
    //    out << test_ids[i] << ',' << yhat[i] << '\n';
    //}
    
    return 0;
}