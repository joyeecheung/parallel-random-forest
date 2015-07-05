# Parallel Random Forest

Parallel Random Forest Implementation in C++(with OpenMP).

## Dependencies

* C++11 support(smart pointers, range-based for loops, lambda, etc.).
* OpenMP(available in most compilers including VC++/g++/clang++)

Tested under the following environments:

1. Windows 8.1 + VS2013
2. Windows 8.1 + g++ (GCC) 4.8.1(mingw32)
3. Ubuntu 14.04 + g++ (GCC) 4.8.2
4. Ubuntu 14.04 + clang++ 3.5.2

## Predefined parameters

* Number of features: 617
* Number of labels: 26
* Minimum node size: 2

Defined in [Config.h](src/Config.h).

##Directory structure

```
.
├─ premake5.lua (premake build scripts)
├─ RandomForest.vcxproj.filters, RandomForest.vcxproj, RandomForest.sln(VS2013 project files)
├─ RandomForest.exe (executable built with VS2013)
├─ README.md (you are reading this)
├─ doc
│   └── report.pdf
├─ data (dataset and output)
│   ├── train.csv (the training set)
│   ├── 1000.csv (subset of the training set for validation)
│   ├── test.csv (the test set)
│   └── submit.csv (the output)
└─ src (source code)
    ├── Config.h, Config.cpp (configurations, common headers)
    ├── DecisionTree.h, DecisionTree.cpp (decision tree implementation)
    ├── RandomForest.h, RandomForest.cpp (random forest implementation)
    └── main.cpp (then entry file)
```

## About the executable

The executable is built for Windows with VS2013, so it needs some .dlls that come with VS2013. If you want to run the program under other environments, you need to build it from source.

### Generate output for Kaggle submission

1. Put the training set in `data/train.csv`, and test set in `data/test.csv`(the header line will be ignored)
2. Run `RandomForest`(`./RandomForest` if you are under Linux). You can pass in an optional number of trees, e.g. `RandomForest 1000` will generate 1000 trees.
3. The results will be saved in `data/submit.csv`

### Validate against the training set

Note: you need to uncomment the `VALIDATE` flag in `src/Config.h` and build the executable again.

1. Put the training set in `data/train.csv`, and the validation set in `data/1000.csv`(the header line will be ignored)
2. Run `RandomForest`(`./RandomForest` if you are under Linux). You can pass in an optional number of trees, e.g. `RandomForest 1000` will generate 1000 trees.
3. The results will be saved in `data/submit.csv`

## Build

On Windows, you can build it with VS2013(or maybe a lower version of VS), or GNU Make(Win32 port) and MinGW. Note that this program needs C++11 support, so an old compiler might not be able to build it.

On Linux, you can build it with Make and g++ or clang++.

### Windows with VS2013

Open the `RandomForest.sln` with VS and build the `RandomForest` target. Make sure that it's in Release mode or the build could be slowed down. The executable will appear under the project directory, named `RandomForest.exe`.

### Windows with Make+MinGW / older VS

Download premake5 from [here](https://premake.github.io/download.html#v5), extract the executable in the archive(e.g. `premake5.exe`), and put the path to the executable in your `PATH` environment variables. Then open cmd and run `premake5 --help` to see what project files you can generate. I've written the premake script `premake5.lua` to generate the proper project files.

For example, to generate the project files for VS2012, simply run `premake5 vs2012` under the project directory, then open `RandomForest.sln` with your VS and build the `RandomForest` target. The executable will appear under the project directory, named `RandomForest.exe`.

WARNING: make sure your compiler has enough C++11 support or the build could fail.

### Linux with Make and g++/clang++

Download premake5 from [here](https://premake.github.io/download.html#v5), extract the executable in the archive(e.g. `premake5`), and put the path to the executable in your `PATH` environment variables(e.g. extract the file to `/usr/local/bin` with root permission so you don't have to touch `PATH`). To generate the project files for make, simply run `premake5 gmake`. If you want to use g++, just run `make` to build it. If you want to use clang, run `make config=clang`(but first you need to make sure you have a symlink `clang++` to your clang++ executable). The executable will appear under the project directory, named `RandomForest`.

WARNING: make sure your compiler has enough C++11 support or the build could fail.

##About

* [Github repository](https://github.com/joyeecheung/parallel-random-forest)
* Author: Qiuyi Zhang
* Jul. 2015
