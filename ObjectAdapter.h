//
// Created by ofir on 23/01/2020.
//

#ifndef EX4_OBJECTADAPTER_H
#define EX4_OBJECTADAPTER_H

#include "Solver.h"
#include "Matrix.h"
#include "Searcher.h"
#include "BFS.h"
#include "DFS.h"
#include "BestFirstSearch.h"
#include "SearchAlgos.h"

using namespace std;

class ObjectAdapter : public Solver<Matrix, string> {

public:
    string solve(Matrix m) {
//        Searcher<Matrix, string>* bestSearch = new BFS<Matrix, string>(m.getMat(), m.getInitialState()->getState(),
//                m.getGoalState()->getState());
//        string solution = bestSearch->search(m);
        string solution = astar(m.getMat(), m.getInitialState()->getState(), m.getGoalState()->getState());
        return solution;
    }
};

#endif //EX4_OBJECTADAPTER_H