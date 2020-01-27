//
// Created by ofir on 23/01/2020.
//

#ifndef EX4_SEARCHER_H
#define EX4_SEARCHER_H

#include <string>
#include "Searchable.h"

using namespace std;

template <class P, class S>
class Searcher {
public:
    virtual S search(P &s) = 0;
    //virtual S search(Searchable<P>* s) = 0;
    virtual int getNumberOfNodesEvaluated() = 0;
};

#endif //EX4_SEARCHER_H
