#ifndef __CONFIG__
#define __CONFIG__

#define JDEBUG
//#define DEBUG_TREE
#define DEBUG_FOREST

#include <cstdio>
#include <vector>
#include <array>
#include <set>
#include <map>
#include <string>
#include <memory>

using std::shared_ptr;
using std::vector;
using std::array;
using std::set;
using std::map;
using std::string;
using std::pair;

typedef vector<int> MutLabels;
typedef const vector<int> Labels;
typedef vector<size_t> Indices;
typedef set<size_t> IndicesSet;

#define FEATURE_NUM 617
#define LABLE_NUM 26

typedef array<double, FEATURE_NUM> MutRow;
typedef const array<double, FEATURE_NUM> Row;
typedef vector<array<double, FEATURE_NUM> > MutValues;
typedef const vector<array<double, FEATURE_NUM> > Values;

extern void printRow(Row row);
#endif