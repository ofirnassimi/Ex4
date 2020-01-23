//
// Created by ofir on 21/01/2020.
//

#ifndef EX4_SEARCHABLE_H
#define EX4_SEARCHABLE_H

#include "State.h"
#include <list>

using namespace std;

template <typename T>
class Searchable {
public:
    virtual State<T>* getInitialState() = 0;
    virtual bool isGoalState(State<T> &s) = 0;
    virtual list<State<T>*> getAllPossibleStates(State<T> &s) = 0;
};

#endif //EX4_SEARCHABLE_H
