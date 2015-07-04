# Parallel Random Forest

Parallel Random Forest Implementation in C++(with OpenMP).

## Dependencies

* C++11 support(smart pointers, range-based for loops, etc.).
* OpenMP(only effective under Release)

Currently built with VS2013, will be ported to other platform.

## Predefined parameters

* Number of features: 617
* Number of labels: 26
* Minimum node size: 2

Defined in [Config.h](src/Config.h).

## Usage

1. Configure the parameters
2. Built the Release
3. Put the data in `data/train.csv` and `data/test.csv`(the header line will be ignored)
4. Run `RandomForest <num of trees>`
5. Result is saved in `data/submit.csv`