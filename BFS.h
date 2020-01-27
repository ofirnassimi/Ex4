//
// Created by ofir on 26/01/2020.
//

#ifndef EX4_BFS_H
#define EX4_BFS_H

#include "State.h"
#include <set>
#include "Searchable.h"
#include <list>
#include <queue>
#include <iostream>
#include "Searchable.h"
#include "Searcher.h"

//problem: Matrix, solution: string
template <typename P, typename S>
class BFS : public Searcher<P,S> {
private:
    int counterSteps = 0;
    list<State<pair<int, int>>> visited;
    list<State<pair<int, int>>> queue;
    list<State<pair<int, int>>> way;
public:
    BFS() {}

    S search(P &s) {
        this->evaluatedNodes = 0;
        this->visited.clear();
        this->queue.clear();
        this->way.clear();
        bool enter = false;
        State<pair<int, int>> v = s.getInitialState();
        queue.push_back(v);
        while (!queue.empty()) {
            this->evaluatedNodes++;
            State<pair<int, int>> v2 = queue.front();
            way.push_front(v2);
            if(s.isGoalState(v2)) {
                return this->way;
            }
            this->visited.push_back(v2);
            for (State<pair<int, int>> r : s.getAllPossibleState(v2)) {
                for (auto visit : this->visited) {
                    if(visit.equals(r)) {
                        enter = true;
                    }
                }
                if (!enter) {
                    this->queue.push_front(r);
                }
                enter = false;
            }
        }

        return "";
    }


    int getNumberOfNodesEvaluated() {
        return counterSteps;
    }
};

#endif //EX4_BFS_H