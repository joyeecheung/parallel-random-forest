#ifndef __CONFIG__
#define __CONFIG__

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

typedef vector<int> MutLabels;
typedef const vector<int> Labels;
typedef vector<size_t> Indices;
typedef set<size_t> IndicesSet;

#define FEATURE_NUM 60
typedef vector<array<double, FEATURE_NUM> > MutValues;
typedef array<double, FEATURE_NUM> Row;
typedef const vector<array<double, FEATURE_NUM> > Values;

#endif